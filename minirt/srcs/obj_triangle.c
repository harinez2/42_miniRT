/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_triangle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonishi <yonishi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 17:39:38 by yonishi           #+#    #+#             */
/*   Updated: 2022/06/18 17:39:39 by yonishi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"main.h"

void	ft_init_triangle(t_triangle *tt)
{
	t_vec	n;

	n = ft_veccrossprod(ft_vecsub(tt->second, tt->first),
			ft_vecsub(tt->third, tt->first));
	tt->plane.normal = ft_vecnormalize(n);
	tt->plane.position = tt->first;
	tt->plane.rgb = tt->rgb;
}

static void	calc_triangle_crossprod(
	t_multivec *mv, t_vec v_tpos, t_triangle *tt)
{
	mv->a = ft_veccrossprod(
			ft_vecsub(tt->second, tt->first), ft_vecsub(v_tpos, tt->second));
	mv->b = ft_veccrossprod(
			ft_vecsub(tt->third, tt->second), ft_vecsub(v_tpos, tt->third));
	mv->c = ft_veccrossprod(
			ft_vecsub(tt->first, tt->third), ft_vecsub(v_tpos, tt->first));
}

//tpos	across point of eyevec and plane surface(pi)
double	get_distance_to_triangle(
	t_vec v_from, t_vec v_to, t_map *m, t_triangle *tt)
{
	double			t;
	t_vec			v_de;
	t_vec			v_tpos;
	t_multivec		mv;
	t_multdouble	mv_innprod;

	t = get_distance_to_plane(v_from, v_to, m, &tt->plane);
	if (t > 0)
	{
		v_de = ft_vecnormalize(ft_vecsub(v_to, v_from));
		v_tpos = ft_vecadd(v_from, ft_vecmult(v_de, t));
		calc_triangle_crossprod(&mv, v_tpos, tt);
		mv_innprod.a = ft_vecinnerprod(mv.a, mv.b);
		mv_innprod.b = ft_vecinnerprod(mv.b, mv.c);
		mv_innprod.c = ft_vecinnerprod(mv.c, mv.a);
		if (mv_innprod.a >= 0 && mv_innprod.b >= 0 && mv_innprod.c >= 0)
			;
		else if (mv_innprod.a < 0 && mv_innprod.b < 0 && mv_innprod.c < 0)
			;
		else
			t = -1;
	}
	return (t);
}

t_color	get_color_by_rt_triangle(t_map *m, int hit_i, t_triangle *tt)
{
	return (get_color_by_rt_plane(m, hit_i, &tt->plane));
}
