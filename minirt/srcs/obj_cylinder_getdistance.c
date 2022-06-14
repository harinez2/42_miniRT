#include	"main.h"

static t_calc_crossing	calc_cylinder_t(
	t_vec v_from, t_vec v_to, t_cylinder *tc)
{
	t_calc_crossing	cv;
	t_vec			v_crossprod_d_n;
	t_vec			v_crossprod_ac_n;

	cv.v_de = ft_vecsub(v_to, v_from);
	v_crossprod_d_n = ft_veccrossprod(
		ft_vecnormalize(cv.v_de), ft_vecnormalize(tc->orientation));
	cv.A = ft_vecnormsq(v_crossprod_d_n);
	v_crossprod_ac_n = ft_veccrossprod(ft_vecsub(v_from, tc->center), tc->orientation);
	cv.B = 2 * ft_vecinnerprod(v_crossprod_d_n, v_crossprod_ac_n);
	cv.C =ft_vecnormsq(v_crossprod_ac_n) - tc->diameter * tc->diameter;
	cv.D = cv.B * cv.B - 4 * cv.A * cv.C;
	return (cv);
}

static double	check_cylinder_length(
	t_map *m, t_cylinder *tc, t_calc_crossing cv, double t)
{
	t_vec		v_tpos;
	t_vec		v_po_p;
	double		v_po_p_len;

	v_tpos = ft_vecadd(m->curr_cam.pos, ft_vecmult(ft_vecnormalize(cv.v_de), t));
	v_po_p = ft_vecsub(v_tpos, tc->center);
	if (ft_vecinnerprod(v_po_p, tc->orientation) < 0)
		return (-1);
	v_po_p_len = ft_vecnorm(v_po_p);
	if (tc->diameter * tc->diameter + tc->height * tc->height
		< v_po_p_len * v_po_p_len)
		return (-1);
	return (t);
}

// tpos：cross point (pi) of the v_cam and the surface of the cylinder
double	get_distance_to_cylinder(
	t_vec v_from, t_vec v_to, t_map *m, t_cylinder *tc)
{
	t_calc_crossing	cv;
	double			t1;
	double			t2;
	double			bigger_t;

	cv = calc_cylinder_t(v_from, v_to, tc);
	tc->secondcrosst_flg = 0;
	if (cv.A == 0 || cv.D < 0)
		cv.t = -1;
	else if (cv.D < EPSILON)
		cv.t = -cv.B / (2 * cv.A);
	else
	{
		t1 = (-cv.B - sqrt(cv.D)) / (2 * cv.A);
		t2 = (-cv.B + sqrt(cv.D)) / (2 * cv.A);
		bigger_t = fmax(t1, t2);
		t1 = check_cylinder_length(m, tc, cv, t1);
		t2 = check_cylinder_length(m, tc, cv, t2);
		if (t1 > 0 && t2 > 0)
			cv.t = fmin(t1, t2);
		else
			cv.t = fmax(t1, t2);
		if (bigger_t != -1 && cv.t == bigger_t)
			tc->secondcrosst_flg = 1;
	}
	return (cv.t);
}
