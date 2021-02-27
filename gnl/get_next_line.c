/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonishi <yonishi@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 13:26:27 by yonishi           #+#    #+#             */
/*   Updated: 2020/12/30 01:07:05 by yonishi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int		free_safely(char **v, char **w, int ret)
{
	if (v != NULL && *v != NULL)
	{
		free(*v);
		*v = NULL;
	}
	if (w != NULL && *w != NULL)
	{
		free(*w);
		*w = NULL;
	}
	return (ret);
}

static int		get_nlpos(char *s, int max)
{
	int		i;

	if (s == NULL)
		return (-1);
	i = 0;
	while (s[i] != '\0' && s[i] != '\n' && i < max)
		i++;
	return (i);
}

static int		read_and_add_line(char **buf, int fd)
{
	char		*rdata;
	char		*tmp;
	int			size;

	if (!(rdata = malloc(sizeof(char) * ((size_t)BUFFER_SIZE + 1))))
		return (free_safely(NULL, buf, STATUS_ERROR));
	size = read(fd, rdata, BUFFER_SIZE);
	if (size < 0)
		return (free_safely(&rdata, buf, size));
	else if (size == 0)
		return (free_safely(&rdata, NULL, size));
	rdata[size] = '\0';
	if (!(tmp = ft_strjoin(*buf, rdata)))
		return (free_safely(&rdata, buf, STATUS_ERROR));
	free_safely(&rdata, buf, 0);
	*buf = tmp;
	return (STATUS_READABLE);
}

int				get_next_line(int fd, char **line)
{
	static char		*buf[FD_MAX];
	long			nl;
	char			*tmp;
	int				ret;

	if (BUFFER_SIZE < 1 || fd < 0 || FD_MAX <= fd)
		return (STATUS_ERROR);
	ret = STATUS_READABLE;
	while (-1 == (nl = get_nlpos(buf[fd], ft_strlen(buf[fd]))) ||
		nl == (long)ft_strlen(buf[fd]))
	{
		ret = read_and_add_line(&(buf[fd]), fd);
		if (ret == STATUS_ERROR)
			return (free_safely(&(buf[fd]), NULL, STATUS_ERROR));
		else if (ret == STATUS_EOF)
			break ;
	}
	if (!(*line = ft_substr(buf[fd], 0, nl)))
		return (free_safely(&(buf[fd]), NULL, STATUS_ERROR));
	if (!(tmp = ft_substr(buf[fd], nl + 1, ft_strlen(buf[fd]))))
		return (free_safely(&(buf[fd]), NULL, STATUS_ERROR));
	free_safely(&(buf[fd]), NULL, 0);
	buf[fd] = tmp;
	(ret == STATUS_EOF) ? free_safely(&(buf[fd]), NULL, 0) : 0;
	return (ret);
}
