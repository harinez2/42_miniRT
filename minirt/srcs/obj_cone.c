#include	"main.h"

//(1) ambient light (kankyo kou)
void	calc_cone_ambient_reflection(
	t_map *m, t_color *color, t_cone *tc)
{
	set_ambient_reflection_color(m, color, &tc->rgb);
}

static t_vec	get_normal_vector_at_tpos(t_map *m, t_cone *tc)
{
	t_vec	v_p0_p;
	double	t;
	t_vec	v_n;

	v_p0_p.x = m->camdir.v_tpos.x - tc->vertex.x;
	v_p0_p.y = m->camdir.v_tpos.y - tc->vertex.y;
	v_p0_p.z = m->camdir.v_tpos.z - tc->vertex.z;
	t = (v_p0_p.x * tc->normal.x + v_p0_p.y * tc->normal.y
		+ v_p0_p.z * tc->normal.z)
		/ (v_p0_p.x * v_p0_p.x + v_p0_p.y * v_p0_p.y + v_p0_p.z * v_p0_p.z);
	v_n.x = t * m->camdir.v_tpos.x - t * tc->vertex.x - tc->normal.x;
	v_n.y = t * m->camdir.v_tpos.y - t * tc->vertex.y - tc->normal.y;
	v_n.z = t * m->camdir.v_tpos.z - t * tc->vertex.z - tc->normal.z;
	return (v_n);
}

// (2) calc diffuse reflection (kakusan hansya kou)
double	calc_cone_diffuse_reflection(
	t_map *m, t_color *color, int i, t_cone *tc)
{
	t_vec	v_lightDir;
	t_vec	v_nornal;
	double	innprod_lit_n;
	t_color	add_color;

	v_lightDir = ft_vecnormalize(ft_vecsub(m->lit[i].pos, m->camdir.v_tpos));
	v_nornal = ft_vecnormalize(get_normal_vector_at_tpos(m, tc));
	innprod_lit_n = ft_vecinnerprod(v_nornal, v_lightDir);
	if (innprod_lit_n < 0)
		innprod_lit_n = 0;
	add_color = adjust_color_level(&tc->rgb, innprod_lit_n);
	add_diffuse_reflection_color(m, i, color, &add_color);
	return (innprod_lit_n);
}

// (3) calc specular reflection (kyomen hansya kou)
void	calc_cone_reflection(
	t_map *m, t_color *color, int i, t_cone *tc)
{
	t_calc_light	cl;

	cl.v_lightDir = ft_vecnormalize(ft_vecsub(m->lit[i].pos, m->camdir.v_tpos));
	cl.v_n = get_normal_vector_at_tpos(m, tc);
	cl.naiseki = ft_vecinnerprod(ft_vecnormalize(cl.v_n), cl.v_lightDir);
	cl.refDir = ft_vecnormalize(ft_vecsub(ft_vecmult(
					ft_vecnormalize(cl.v_n), 2 * cl.naiseki), cl.v_lightDir));
	cl.invEyeDir = ft_vecnormalize(ft_vecmult(m->camdir.v_de, -1));
	cl.vrDot = ft_vecinnerprod(cl.invEyeDir, cl.refDir);
	if (cl.vrDot < 0)
		cl.vrDot = 0;
	cl.vrDotPow = adjust_range(pow(cl.vrDot, m->shininess),
			(t_minmax){.min = 0, .max = 1}, (t_minmax){.min = 0, .max = 255});
	color->r += m->kSpe.r * m->lit[i].itsty * m->lit[i].rgb.r
		* cl.vrDotPow * tc->rgb.r;
	color->g += m->kSpe.g * m->lit[i].itsty * m->lit[i].rgb.g
		* cl.vrDotPow * tc->rgb.g;
	color->b += m->kSpe.b * m->lit[i].itsty * m->lit[i].rgb.b
		* cl.vrDotPow * tc->rgb.b;
}

// tpos			：cross point (pi) of the v_cam and the surface of the object
// v_lightDir	: vector of incidence (l) (nyuusha vector)
// v_n			: normal vector (n) (housen vector)
t_color	get_color_by_rt_cone(t_map *m, t_cone *tc)
{
	t_color	color;
	int		i;
	double	hit_t;
	double	naiseki;

	calc_cone_ambient_reflection(m, &color, tc);
	i = 0;
	while (i < m->lit_cnt)
	{
		get_minimum_distance_to_obj(m->lit[i].pos, m, &hit_t);
		if (hit_t != -1)
		{
			i++;
			continue ;
		}
		naiseki = calc_cone_diffuse_reflection(m, &color, i, tc);
		if (naiseki > 0)
			calc_cone_reflection(m, &color, i, tc);
		i++;
	}
	return (set_rgb_inrange(color));
}
