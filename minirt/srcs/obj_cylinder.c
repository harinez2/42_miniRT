#include	"main.h"

static void	calc_ABCD(
	t_calc_crossing *cv, t_multdouble *md2, t_multdouble *md3, t_cylinder *tc)
{
	double			v;

	v = sqrt(tc->orientation.x * tc->orientation.x
			+ tc->orientation.y * tc->orientation.y
			+ tc->orientation.z * tc->orientation.z);
	cv->A = md2->a * md2->a + md2->b * md2->b + md2->c * md2->c;
	cv->B = 2 * (md2->a * md3->a + md2->b * md3->b + md2->c * md3->c);
	cv->C = md3->a * md3->a + md3->b * md3->b + md3->c * md3->c
		- v * v * tc->diameter * tc->diameter;
	cv->D = cv->B * cv->B - 4 * cv->A * cv->C;
}

static double	check_cylinder_length(
	t_map *m, t_cylinder *tc, t_calc_crossing cv)
{
	t_vec		v_tpos;
	t_vec		v_po_p;
	double		v_po_p_len;

	v_tpos = ft_vecadd(m->curr_cam.pos, ft_vecmult(cv.v_de, cv.t));
	v_po_p = ft_vecsub(v_tpos, tc->center);
	v_po_p_len = ft_vecnorm(v_po_p);
	if (tc->diameter * tc->diameter + tc->height * tc->height / 4
		< v_po_p_len * v_po_p_len)
		return (-1);
	return (0);
}

// tpos：cross point (pi) of the v_cam and the surface of the cylinder
double	get_distance_to_cylinder(t_vec v_w, t_map *m, t_cylinder *tc)
{
	t_calc_crossing	cv;
	t_multdouble	md1;
	t_multdouble	md2;
	t_multdouble	md3;

	cv.v_de = ft_vecsub(v_w, m->curr_cam.pos);
	md1.a = m->curr_cam.pos.x - tc->center.x;
	md1.b = m->curr_cam.pos.y - tc->center.y;
	md1.c = m->curr_cam.pos.z - tc->center.z;
	md2.a = tc->orientation.y * cv.v_de.z - tc->orientation.z * cv.v_de.y;
	md2.b = tc->orientation.z * cv.v_de.x - tc->orientation.x * cv.v_de.z;
	md2.c = tc->orientation.x * cv.v_de.y - tc->orientation.y * cv.v_de.x;
	md3.a = tc->orientation.y * md1.c - tc->orientation.z * md1.b;
	md3.b = tc->orientation.z * md1.a - tc->orientation.x * md1.c;
	md3.c = tc->orientation.x * md1.b - tc->orientation.y * md1.a;
	calc_ABCD(&cv, &md2, &md3, tc);
	cv.t = calc_minimum_t(cv.A, cv.B, cv.D);
	if (cv.t > 0 && check_cylinder_length(m, tc, cv) == -1)
		return (-1);
	return (cv.t);
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
	v_nornal.x = 2 * (m->camdir.v_tpos.x - tc->center.x);
	v_nornal.y = 0;
	v_nornal.z = 2 * (m->camdir.v_tpos.z - tc->center.z);
	innprod_lit_n = ft_vecinnerprod(ft_vecnormalize(v_nornal), v_lightDir);
	if (innprod_lit_n < 0)
		innprod_lit_n = 0;
	add_color = adjust_color_level(&tc->rgb, innprod_lit_n);
	add_diffuse_reflection_color(m, i, color, &add_color);
	return (innprod_lit_n);
}

// (3) calc specular reflection (kyomen hansya kou)
static void	calc_cylinder_reflection(
	t_map *m, t_color *color, int i, t_cylinder *tc)
{
	t_calc_light	cl;
	t_color			add_color;

	cl.v_lightDir = ft_vecnormalize(ft_vecsub(m->lit[i].pos, m->camdir.v_tpos));
	cl.v_n.x = 2 * (m->camdir.v_tpos.x - tc->center.x);
	cl.v_n.y = 0;
	cl.v_n.z = 2 * (m->camdir.v_tpos.z - tc->center.z);
	cl.naiseki = ft_vecinnerprod(ft_vecnormalize(cl.v_n), cl.v_lightDir);
	cl.refDir = ft_vecnormalize(ft_vecsub(ft_vecmult(
					ft_vecnormalize(cl.v_n), 2 * cl.naiseki), cl.v_lightDir));
	cl.invEyeDir = ft_vecnormalize(ft_vecmult(m->camdir.v_de, -1));
	cl.vrDot = ft_vecinnerprod(cl.invEyeDir, cl.refDir);
	if (cl.vrDot < 0)
		cl.vrDot = 0;
	add_color = adjust_color_level(&tc->rgb, pow(cl.vrDot, m->shininess));
	add_specular_reflection_color(m, i, color, &add_color);
}

// tpos			：cross point (pi) of the v_cam and the surface of the object
// v_lightDir	: vector of incidence (l) (nyuusha vector)
// v_n			: normal vector (n) (housen vector)
t_color	get_color_by_rt_cylinder(t_map *m, t_cylinder *tc)
{
	t_color	color;
	int		i;
	double	hit_t;
	double	naiseki;

	set_ambient_reflection_color(m, &color, &tc->rgb);
	i = 0;
	while (i < m->lit_cnt)
	{
		get_minimum_distance_to_obj(m->lit[i].pos, m, &hit_t);
		if (hit_t != -1)
		{
			i++;
			continue ;
		}
		naiseki = calc_cylinder_diffuse_reflection(m, &color, i, tc);
		if (naiseki > 0)
			calc_cylinder_reflection(m, &color, i, tc);
		i++;
	}set_color(&color, 255,255,255);
	return (set_rgb_inrange(color));
}
