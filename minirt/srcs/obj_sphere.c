#include	"main.h"

double	get_distance_to_sphere(
	t_vec v_from, t_vec v_to, t_map *m, t_sphere *ts)
{
	t_calc_crossing	cv;
	t_vec			v_center_cam;

	(void)m;
	cv.v_de = ft_vecnormalize(ft_vecsub(v_to, v_from));
	v_center_cam = ft_vecsub(v_from, ts->center);
	cv.A = ft_vecnormsq(cv.v_de);
	cv.B = 2 * ft_vecinnerprod(cv.v_de, v_center_cam);
	cv.C = ft_vecnormsq(v_center_cam) - ts->diameter * ts->diameter;
	cv.D = cv.B * cv.B - 4 * cv.A * cv.C;
	cv.t = calc_minimum_t(cv.A, cv.B, cv.D);
	return (cv.t);
}

// (2) calc diffuse reflection (kakusan hansya kou)
static double	calc_sphere_diffuse_reflection(
	t_map *m, t_color *color, int i, t_sphere *ts)
{
	t_vec	v_lightDir;
	t_vec	v_nornal;
	double	innprod_lit_n;
	t_color	add_color;

	v_lightDir = ft_vecnormalize(ft_vecsub(m->lit[i].pos, m->camdir.v_tpos));
	v_nornal = ft_vecnormalize(ft_vecsub(m->camdir.v_tpos, ts->center));
	innprod_lit_n = ft_vecinnerprod(v_nornal, v_lightDir);
	if (innprod_lit_n < 0)
		innprod_lit_n = 0;
	add_color = adjust_color_level(&ts->rgb, innprod_lit_n);
	add_diffuse_reflection_color(m, i, color, &add_color);
	return (innprod_lit_n);
}

// (3) calc specular reflection (kyomen hansya kou)
#ifdef BONUS

static void	calc_sphere_specular_reflection(
	t_map *m, t_color *color, int i, t_sphere *ts)
{
	t_calc_light	cl;
	t_color			add_color;

	cl.v_lightDir = ft_vecnormalize(ft_vecsub(m->lit[i].pos, m->camdir.v_tpos));
	cl.v_n = ft_vecnormalize(ft_vecsub(m->camdir.v_tpos, ts->center));
	cl.naiseki = ft_vecinnerprod(cl.v_n, cl.v_lightDir);
	cl.refDir = ft_vecsub(ft_vecmult(cl.v_n, 2 * cl.naiseki), cl.v_lightDir);
	cl.invEyeDir = ft_vecnormalize(ft_vecmult(m->camdir.v_de, -1));
	cl.vrDot = ft_vecinnerprod(cl.invEyeDir, cl.refDir);
	if (cl.vrDot < 0)
		cl.vrDot = 0;
	add_color = adjust_color_level(&ts->rgb, pow(cl.vrDot, m->shininess));
	add_specular_reflection_color(m, i, color, &add_color);
}

#else

static void	calc_sphere_specular_reflection(
	t_map *m, t_color *color, int i, t_sphere *ts)
{
	(void)m;
	(void)color;
	(void)i;
	(void)ts;
}

#endif

//tpos	across point of eyevec and sphere surface(pi)
t_color	get_color_by_rt_sphere(t_map *m, int hit_i, t_sphere *ts)
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
			naiseki = calc_sphere_diffuse_reflection(m, &color, lit_i, ts);
			if (naiseki > 0)
				calc_sphere_specular_reflection(m, &color, lit_i, ts);
		}
		lit_i++;
	}
	return (set_rgb_inrange(color));
}
