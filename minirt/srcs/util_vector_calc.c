/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_vector_calc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonishi <yonishi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 17:40:33 by yonishi           #+#    #+#             */
/*   Updated: 2022/06/18 17:40:33 by yonishi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"main.h"

t_vec	ft_vecadd(t_vec v, t_vec w)
{
	t_vec	ret;

	ret.x = v.x + w.x;
	ret.y = v.y + w.y;
	ret.z = v.z + w.z;
	return (ret);
}

t_vec	ft_vecsub(t_vec v, t_vec w)
{
	t_vec	ret;

	ret.x = v.x - w.x;
	ret.y = v.y - w.y;
	ret.z = v.z - w.z;
	return (ret);
}

// Multiply of scalar
t_vec	ft_vecmult(t_vec v, double k)
{
	t_vec	ret;

	ret.x = v.x * k;
	ret.y = v.y * k;
	ret.z = v.z * k;
	return (ret);
}

// Divided by scalar
t_vec	ft_vecdiv(t_vec v, double k)
{
	t_vec	ret;

	ret.x = v.x / k;
	ret.y = v.y / k;
	ret.z = v.z / k;
	return (ret);
}
