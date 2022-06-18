/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonishi <yonishi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 17:40:31 by yonishi           #+#    #+#             */
/*   Updated: 2022/06/18 17:40:31 by yonishi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"main.h"

double	adjust_range(double x, t_minmax from, t_minmax to)
{
	double	pos;
	double	ret;

	pos = (x - from.min) / (from.max - from.min);
	ret = pos * (to.max - to.min) + to.min;
	return (ret);
}

int	get_endian(void)
{
	int		a;
	int		local_endian;

	a = 0x11223344;
	if (((unsigned char *)&a)[0] == 0x11)
		local_endian = 1;
	else
		local_endian = 0;
	return (local_endian);
}

double	ft_degree_to_rad(double degree)
{
	return (degree * PI / 180);
}
