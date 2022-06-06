#include	"main.h"

double	get_distance_to_plane(
	t_vec v_from, t_vec v_to, t_map *m, t_plane *tp)
{
	double	t;
	t_vec	v_de;
	double	a;
	double	b;
	double	c;

	(void)m;
	if (ft_vecinnerprod(v_to, tp->normal) != 0)
	{
		v_de = ft_vecsub(v_to, v_from);
		a = ft_vecinnerprod(tp->position, tp->normal);
		b = ft_vecinnerprod(v_from, tp->normal);
		c = ft_vecinnerprod(v_de, tp->normal);
		t = (a - b) / c;
		if (t > EPSILON)
			return (t);
	}
	return (-1);
}

// (2) calc diffuse reflection (kakusan hansya kou)
static double	calc_plane_diffuse_reflection(
	t_map *m, t_color *color, int i, t_plane *tp)
{
	t_vec	v_lightDir;
	double	innprod_lit_n;
	t_color	add_color;

	v_lightDir = ft_vecnormalize(ft_vecsub(m->lit[i].pos, m->camdir.v_tpos));
	innprod_lit_n = ft_vecinnerprod(ft_vecnormalize(tp->normal), v_lightDir);
	if (innprod_lit_n < 0)
		innprod_lit_n = 0;
	add_color = adjust_color_level(&tp->rgb, innprod_lit_n);
	add_diffuse_reflection_color(m, i, color, &add_color);
	return (innprod_lit_n);
}

// (3) calc specular reflection (kyomen hansya kou)
#ifdef BONUS

static void	calc_plane_specular_reflection(
	t_map *m, t_color *color, int i, t_plane *tp)
{
	t_calc_light	cl;
	t_color			add_color;

	cl.v_lightDir = ft_vecnormalize(ft_vecsub(m->lit[i].pos, m->camdir.v_tpos));
	cl.naiseki = ft_vecinnerprod(ft_vecnormalize(tp->normal), cl.v_lightDir);
	cl.refDir
		= ft_vecsub(ft_vecmult(tp->normal, 2 * cl.naiseki), cl.v_lightDir);
	cl.invEyeDir = ft_vecnormalize(ft_vecmult(m->camdir.v_de, -1));
	cl.vrDot = ft_vecinnerprod(cl.invEyeDir, cl.refDir);
	if (cl.vrDot < 0)
		cl.vrDot = 0;
	add_color = adjust_color_level(&tp->rgb, pow(cl.vrDot, m->shininess));
	add_specular_reflection_color(m, i, color, &add_color);
}

#else

static void	calc_plane_specular_reflection(
	t_map *m, t_color *color, int i, t_plane *tp)
{
	(void)m;
	(void)color;
	(void)i;
	(void)tp;
}

#endif

t_color	get_color_by_rt_plane(t_map *m, t_plane *tp)
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
			naiseki = calc_plane_diffuse_reflection(m, &color, i, tp);
			if (naiseki > 0)
				calc_plane_specular_reflection(m, &color, i, tp);
		}
		i++;
	}
	return (set_rgb_inrange(color));
}
