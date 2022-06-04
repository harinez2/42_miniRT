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

static t_calc_crossing	calc_cylinder_t(
	t_vec v_w, t_map *m, t_cylinder *tc)
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
	return (cv);
}

static double	check_cylinder_length(
	t_map *m, t_cylinder *tc, t_calc_crossing cv, double t)
{
	t_vec		v_tpos;
	t_vec		v_po_p;
	double		v_po_p_len;

	v_tpos = ft_vecadd(m->curr_cam.pos, ft_vecmult(cv.v_de, t));
	v_po_p = ft_vecsub(v_tpos, tc->center);
	v_po_p_len = ft_vecnorm(v_po_p);
	if (tc->diameter * tc->diameter + tc->height * tc->height / 4
		< v_po_p_len * v_po_p_len)
		return (-1);
	return (t);
}

// tpos：cross point (pi) of the v_cam and the surface of the cylinder
double	get_distance_to_cylinder(t_vec v_w, t_map *m, t_cylinder *tc)
{
	t_calc_crossing	cv;
	double			t1;
	double			t2;

	cv = calc_cylinder_t(v_w, m, tc);
	cv.t = -1;
	if (-EPSILON < cv.D && cv.D < EPSILON)
		cv.t = -cv.B / (2 * cv.A);
	else if (cv.D > 0)
	{
		t1 = (-cv.B - sqrt(cv.D)) / (2 * cv.A);
		t1 = check_cylinder_length(m, tc, cv, t1);
		t2 = (-cv.B + sqrt(cv.D)) / (2 * cv.A);
		t2 = check_cylinder_length(m, tc, cv, t2);
		if (t1 > 0 && t2 > 0)
			cv.t = fmin(t1, t2);
		else
			cv.t = fmax(t1, t2);
	}
	return (cv.t);
}
