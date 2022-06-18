/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readfile_config_light.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonishi <yonishi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 17:39:54 by yonishi           #+#    #+#             */
/*   Updated: 2022/06/18 17:39:54 by yonishi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"main.h"

#ifdef BONUS

static void	check_light_count(t_map *m)
{
	if (m->lit_cnt >= MAX_LIGHT_COUNT)
		print_error_exit(ERR_RD_TOOMUCH_LIT_SPECIFIED, m);
}

#else

static void	check_light_count(t_map *m)
{
	if (m->lit_cnt >= MAX_LIGHT_COUNT)
		print_error_exit(ERR_RD_TOOMUCH_LIT_SPECIFIED, m);
	else if (m->lit_cnt >= 1)
		print_error_exit(ERR_RD_TOOMUCH_LIT_SPECIFIED, m);
}

#endif

int	read_file_light(int *i, char *line, t_map *m)
{
	(*i)++;
	check_light_count(m);
	m->lit[m->lit_cnt].pos = read_xyz(i, line, m);
	m->lit[m->lit_cnt].itsty = read_double(i, line, m);
	if (m->lit[m->lit_cnt].itsty < 0 || 1 < m->lit[m->lit_cnt].itsty)
		print_error_exit(ERR_RD_OUTOFRANGE, m);
	m->lit[m->lit_cnt++].rgb = read_rgb(i, line, m);
	skip_separater(i, line);
	if (!is_eol(i, line))
		print_error_exit(ERR_RD_INCORRECTFORMAT, m);
	return (CMD_LIGHT);
}
