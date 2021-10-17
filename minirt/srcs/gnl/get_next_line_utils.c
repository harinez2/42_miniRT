/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonishi <yonishi@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 20:42:05 by yonishi           #+#    #+#             */
/*   Updated: 2020/12/27 00:50:48 by yonishi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t		i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		s1len;
	int		s2len;
	int		i;
	char	*t;

	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	t = malloc(sizeof(char) * (s1len + s2len + 1));
	if (!t)
		return (NULL);
	i = 0;
	while (i < s1len)
	{
		t[i] = s1[i];
		i++;
	}
	while (i < (s1len + s2len))
	{
		t[i] = s2[i - s1len];
		i++;
	}
	t[i] = '\0';
	return (t);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	int		srclen;
	int		dstlen;
	int		i;
	char	*t;

	srclen = ft_strlen(s);
	if ((int)start < srclen)
	{
		dstlen = len;
		if ((int)start + (int)len > srclen)
			dstlen = srclen - (int)start;
	}
	else
		dstlen = 0;
	t = malloc(sizeof(char) * (dstlen + 1));
	if (!t)
		return (NULL);
	i = 0;
	while (i < dstlen)
	{
		t[i] = s[(int)start + i];
		i++;
	}
	t[i] = '\0';
	return (t);
}
