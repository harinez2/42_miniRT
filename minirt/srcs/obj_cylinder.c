#include	"main.h"

static t_vec	get_normal_vector_at_tpos_cylinder(t_map *m, t_cylinder *tc)
{
	t_vec	v_p0_p;
	t_vec	v_n;

	v_p0_p = ft_vecsub(m->camdir.v_tpos, tc->center);
	v_n = ft_vecsub(v_p0_p, ft_vecnormalize(tc->orientation));
	return (v_n);
}

// (2) calc diffuse reflection (kakusan hansya kou)
static double	calc_cylinder_diffuse_reflection(
	t_map *m, t_color *color, int i, t_cylinder *tc)
{
	t_vec	v_lightDir;
	t_vec	v_nornal;
	double	innprod_lit_n;
	t_color	add_color;

	v_lightDir = ft_vecnormalize(ft_vecsub(m->lit[i].pos, m->camdir.v_tpos));
	v_nornal = ft_vecnormalize(get_normal_vector_at_tpos_cylinder(m, tc));
	innprod_lit_n = ft_vecinnerprod(v_nornal, v_lightDir);
	if (innprod_lit_n < 0)
		innprod_lit_n = 0;
	add_color = adjust_color_level(&tc->rgb, innprod_lit_n);
	add_diffuse_reflection_color(m, i, color, &add_color);
	return (innprod_lit_n);
}

// (3) calc specular reflection (kyomen hansya kou)
#ifdef BONUS

static void	calc_cylinder_specular_reflection(
	t_map *m, t_color *color, int i, t_cylinder *tc)
{
	t_calc_light	cl;
	t_color			add_color;

	cl.v_lightDir = ft_vecnormalize(ft_vecsub(m->lit[i].pos, m->camdir.v_tpos));
	cl.v_n = ft_vecnormalize(get_normal_vector_at_tpos_cylinder(m, tc));
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

static void	calc_cylinder_specular_reflection(
	t_map *m, t_color *color, int i, t_cylinder *tc)
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
t_color	get_color_by_rt_cylinder(t_map *m, t_cylinder *tc)
{
	t_color	color;
	int		i;
	double	hit_t;
	double	naiseki;

	set_ambient_reflection_color(m, &color);
	i = 0;
	while (i < m->lit_cnt)
	{
		get_minimum_distance_to_obj(m->lit[i].pos, m->camdir.v_tpos, m, &hit_t);
		if (hit_t < 0 || 1 - EPSILON < hit_t)
		{
			naiseki = calc_cylinder_diffuse_reflection(m, &color, i, tc);
			if (naiseki > 0)
				calc_cylinder_specular_reflection(m, &color, i, tc);
		}
		i++;
	}
	return (set_rgb_inrange(color));
}
