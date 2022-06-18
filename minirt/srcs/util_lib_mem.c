/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_lib_mem.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonishi <yonishi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 17:40:23 by yonishi           #+#    #+#             */
/*   Updated: 2022/06/18 17:40:23 by yonishi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"main.h"

void	*ft_memset(void *b, int c, size_t n)
{
	size_t			i;
	unsigned char	*ss;

	ss = (unsigned char *)b;
	i = 0;
	while (i < n)
	{
		ss[i] = (unsigned char)c;
		i++;
	}
	return (b);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dd;
	unsigned char	*ss;

	if (dst == src)
		return (dst);
	dd = (unsigned char *)dst;
	ss = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		dd[i] = ss[i];
		i++;
	}
	return (dst);
}
