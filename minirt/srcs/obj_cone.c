#include	"main.h"

static t_vec	get_normal_vector_at_tpos_cone(t_map *m, t_cone *tc)
{
	t_vec	v_p0_p;
	double	orien_len;
	t_vec	v_n;

	v_p0_p = ft_vecsub(m->camdir.v_tpos, tc->vertex);
	orien_len = ft_vecnorm(v_p0_p) * cos(ft_degree_to_rad(tc->theta));
	v_n = ft_vecsub(v_p0_p, ft_vecmult(ft_vecnormalize(tc->normal), orien_len));
	return (v_n);
}

// (2) calc diffuse reflection (kakusan hansya kou)
static double	calc_cone_diffuse_reflection(
	t_map *m, t_color *color, int i, t_cone *tc)
{
	t_vec	v_lightDir;
	t_vec	v_nornal;
	double	innprod_lit_n;
	t_color	add_color;

	v_lightDir = ft_vecnormalize(ft_vecsub(m->lit[i].pos, m->camdir.v_tpos));
	v_nornal = ft_vecnormalize(get_normal_vector_at_tpos_cone(m, tc));
	innprod_lit_n = ft_vecinnerprod(v_nornal, v_lightDir);
	if (innprod_lit_n < 0)
		innprod_lit_n = 0;
	add_color = adjust_color_level(&tc->rgb, innprod_lit_n);
	add_diffuse_reflection_color(m, i, color, &add_color);
	return (innprod_lit_n);
}

// (3) calc specular reflection (kyomen hansya kou)
#ifdef BONUS

static void	calc_cone_specular_reflection(
	t_map *m, t_color *color, int i, t_cone *tc)
{
	t_calc_light	cl;
	t_color			add_color;

	cl.v_lightDir = ft_vecnormalize(ft_vecsub(m->lit[i].pos, m->camdir.v_tpos));
	cl.v_n = ft_vecnormalize(get_normal_vector_at_tpos_cone(m, tc));
	cl.naiseki = ft_vecinnerprod(cl.v_n, cl.v_lightDir);
	cl.refDir = ft_vecnormalize(
			ft_vecsub(ft_vecmult(cl.v_n, 2 * cl.naiseki), cl.v_lightDir));
	cl.invEyeDir = ft_vecnormalize(ft_vecmult(m->camdir.v_de, -1));
	cl.vrDot = ft_vecinnerprod(cl.invEyeDir, cl.refDir);
	if (cl.vrDot < 0)
		cl.vrDot = 0;
	add_color = adjust_color_level(&tc->rgb, pow(cl.vrDot, m->shininess));
	add_specular_reflection_color(m, i, color, &add_color);
}

#else

static void	calc_cone_specular_reflection(
	t_map *m, t_color *color, int i, t_cone *tc)
{
	(void)m;
	(void)color;
	(void)i;
	(void)tc;
}

#endif

// tpos			：cross point (pi) of the v_cam and the surface of the object
// v_lightDir	: vector of incidence (l) (nyuusha vector)
// v_n			: normal vector (n) (housen vector)
t_color	get_color_by_rt_cone(t_map *m, int hit_i, t_cone *tc)
{
	t_color	color;
	int		lit_i;
	int		btw_i;
	double	btw_t;
	double	naiseki;

	set_ambient_reflection_color(m, &color);
	lit_i = 0;
	while (lit_i < m->lit_cnt)
	{
		btw_i = get_minimum_distance_to_obj(
				m->lit[lit_i].pos, m->camdir.v_tpos, m, &btw_t);
		if (btw_i == hit_i)
		{
			naiseki = calc_cone_diffuse_reflection(m, &color, lit_i, tc);
			if (naiseki > 0)
				calc_cone_specular_reflection(m, &color, lit_i, tc);
		}
		lit_i++;
	}
	return (set_rgb_inrange(color));
}
