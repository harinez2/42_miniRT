/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_cylinder_getdistance.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonishi <yonishi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 17:39:25 by yonishi           #+#    #+#             */
/*   Updated: 2022/06/18 19:53:40 by yonishi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"main.h"

static t_calc_crossing	calc_cylinder_t(
	t_vec v_from, t_vec v_to, t_cylinder *tc)
{
	t_calc_crossing	cv;
	t_vec			v_crossprod_d_n;
	t_vec			v_crossprod_ac_n;

	cv.v_de = ft_vecnormalize(ft_vecsub(v_to, v_from));
	v_crossprod_d_n = ft_veccrossprod(
			cv.v_de, ft_vecnormalize(tc->orientation));
	cv.A = ft_vecnormsq(v_crossprod_d_n);
	v_crossprod_ac_n = ft_veccrossprod(
			ft_vecsub(v_from, tc->center), ft_vecnormalize(tc->orientation));
	cv.B = 2 * ft_vecinnerprod(v_crossprod_d_n, v_crossprod_ac_n);
	cv.C = ft_vecnormsq(v_crossprod_ac_n) - tc->diameter * tc->diameter;
	cv.D = cv.B * cv.B - 4 * cv.A * cv.C;
	return (cv);
}

static double	check_cylinder_length(
	t_cylinder *tc, t_calc_crossing cv, double t, t_vec v_from)
{
	t_vec		v_tpos;
	t_vec		v_po_p;
	double		v_po_p_len;

	v_tpos = ft_vecadd(v_from, ft_vecmult(cv.v_de, t));
	v_po_p = ft_vecsub(v_tpos, tc->center);
	if (ft_vecinnerprod(v_po_p, ft_vecnormalize(tc->orientation)) < 0)
		return (-1);
	v_po_p_len = ft_vecnorm(v_po_p);
	if (tc->diameter * tc->diameter + tc->height * tc->height
		< v_po_p_len * v_po_p_len)
		return (-1);
	return (t);
}

static double	select_best_t(double t1, double t2)
{
	if (t1 > 0 && t2 > 0)
		return (fmin(t1, t2));
	else
		return (fmax(t1, t2));
}

// tpos：cross point (pi) of the v_cam and the surface of the cylinder
double	get_distance_to_cylinder(
	t_vec v_from, t_vec v_to, t_map *m, t_cylinder *tc)
{
	t_calc_crossing	cv;
	double			t1;
	double			t2;
	double			bigger_t;

	(void)m;
	cv = calc_cylinder_t(v_from, v_to, tc);
	tc->secondcrosst_flg = 0;
	if (cv.A == 0 || cv.D < 0)
		cv.t = -1;
	else if (cv.D == 0)
		cv.t = -cv.B / (2 * cv.A);
	else
	{
		t1 = (-cv.B - sqrt(cv.D)) / (2 * cv.A);
		t2 = (-cv.B + sqrt(cv.D)) / (2 * cv.A);
		bigger_t = fmax(t1, t2);
		t1 = check_cylinder_length(tc, cv, t1, v_from);
		t2 = check_cylinder_length(tc, cv, t2, v_from);
		cv.t = select_best_t(t1, t2);
		if (bigger_t != -1 && cv.t == bigger_t)
			tc->secondcrosst_flg = 1;
	}
	return (cv.t);
}
