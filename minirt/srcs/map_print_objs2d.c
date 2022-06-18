/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_print_objs2d.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonishi <yonishi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 17:38:49 by yonishi           #+#    #+#             */
/*   Updated: 2022/06/18 17:38:50 by yonishi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"main.h"

void	print_cone(t_cone *tc)
{
	printf("Cone  : ");
	ft_vecprint(&tc->vertex);
	printf(" / ");
	ft_vecprint(&tc->normal);
	printf(" (theta:%.2f) / ", tc->theta);
	ft_colorprint(&tc->rgb);
	printf("\n");
}
