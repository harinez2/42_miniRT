/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_cone_getdistance.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonishi <yonishi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 17:39:17 by yonishi           #+#    #+#             */
/*   Updated: 2022/06/18 17:39:19 by yonishi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"main.h"

static void	calc_ABCD(t_calc_crossing *cv, t_multdouble *md1, t_multdouble *md2)
{
	cv->A = md2->a * cv->v_de.x * cv->v_de.x + md2->b * cv->v_de.y * cv->v_de.y
		+ md2->c * cv->v_de.z * cv->v_de.z;
	cv->B = 2 * (md2->a * md1->a * cv->v_de.x + md2->b * md1->b * cv->v_de.y
			+ md2->c * md1->c * cv->v_de.z);
	cv->C = md2->a * md1->a * md1->a + md2->b * md1->b * md1->b
		+ md2->c * md1->c * md1->c;
	cv->D = cv->B * cv->B - 4 * cv->A * cv->C;
}

static double	check_cone_direction(
	t_cone *tc, t_calc_crossing cv, t_vec v_from)
{
	t_vec		v_tpos;
	t_vec		v_po_p;

	v_tpos = ft_vecadd(v_from, ft_vecmult(cv.v_de, cv.t));
	v_po_p = ft_vecsub(v_tpos, tc->vertex);
	if (ft_vecinnerprod(v_po_p, tc->normal) < 0)
		return (-1);
	return (0);
}

static double	check_cone_length(t_cone *tc, t_calc_crossing cv, t_vec v_from)
{
	t_vec		v_tpos;
	t_vec		v_po_p;
	double		v_po_p_len;

	v_tpos = ft_vecadd(v_from, ft_vecmult(cv.v_de, cv.t));
	v_po_p = ft_vecsub(v_tpos, tc->vertex);
	v_po_p_len = ft_vecnorm(v_po_p);
	if (ft_vecnorm(tc->normal) / cos(ft_degree_to_rad(tc->theta)) <= v_po_p_len)
		return (-1);
	return (0);
}

double	get_distance_to_cone(
	t_vec v_from, t_vec v_to, t_map *m, t_cone *tc)
{
	t_calc_crossing	cv;
	t_multdouble	md1;
	t_multdouble	md2;
	double			l;

	(void)m;
	cv.v_de = ft_vecnormalize(ft_vecsub(v_to, v_from));
	md1.a = v_from.x - tc->vertex.x;
	md1.b = v_from.y - tc->vertex.y;
	md1.c = v_from.z - tc->vertex.z;
	l = ft_vecnorm(tc->normal) * cos(ft_degree_to_rad(tc->theta));
	md2.a = tc->normal.x * tc->normal.x / (l * l) - 1;
	md2.b = tc->normal.y * tc->normal.y / (l * l) - 1;
	md2.c = tc->normal.z * tc->normal.z / (l * l) - 1;
	calc_ABCD(&cv, &md1, &md2);
	cv.t = calc_minimum_t(cv.A, cv.B, cv.D);
	if (cv.t > 0 && check_cone_direction(tc, cv, v_from) == -1)
		return (-1);
	else if (cv.t > 0 && check_cone_length(tc, cv, v_from) == -1)
		return (-1);
	return (cv.t);
}
