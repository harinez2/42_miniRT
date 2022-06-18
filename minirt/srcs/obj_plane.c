#include	"main.h"

double	get_distance_to_plane(
	t_vec v_from, t_vec v_to, t_map *m, t_plane *tp)
{
	double	t;
	t_vec	v_de;
	double	innprod_d_n;
	double	innprod_pc_n;
	double	innprod_s_n;

	(void)m;
	v_de = ft_vecnormalize(ft_vecsub(v_to, v_from));
	innprod_d_n = ft_vecinnerprod(v_de, ft_vecnormalize(tp->normal));
	if (innprod_d_n != 0)
	{
		innprod_pc_n
			= ft_vecinnerprod(tp->position, ft_vecnormalize(tp->normal));
		innprod_s_n = ft_vecinnerprod(v_from, ft_vecnormalize(tp->normal));
		t = (innprod_pc_n - innprod_s_n) / innprod_d_n;
		if (t > 0)
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
		innprod_lit_n *= -1;
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
	if (cl.naiseki < 0)
		cl.naiseki *= -1;
	cl.refDir = ft_vecsub(
			ft_vecmult(ft_vecnormalize(tp->normal), 2 * cl.naiseki),
			cl.v_lightDir);
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

t_color	get_color_by_rt_plane(t_map *m, int hit_i, t_plane *tp)
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
			naiseki = calc_plane_diffuse_reflection(m, &color, lit_i, tp);
			if (naiseki > 0)
				calc_plane_specular_reflection(m, &color, lit_i, tp);
		}
		lit_i++;
	}
	return (set_rgb_inrange(color));
}
