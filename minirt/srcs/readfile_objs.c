/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readfile_objs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonishi <yonishi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 17:40:01 by yonishi           #+#    #+#             */
/*   Updated: 2022/06/18 17:40:01 by yonishi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"main.h"

int	read_file_sphere(int *i, char *line, t_map *m)
{
	(*i) += 2;
	if (m->obj_count >= MAX_OBJ_COUNT)
		print_error_exit(ERR_RD_TOOMUCH_OBJ_SPECIFIED, m);
	m->obj_type[m->obj_count] = CMD_SPHERE;
	m->obj[m->obj_count] = (t_sphere *)malloc(sizeof(t_sphere));
	if (!m->obj[m->obj_count])
		print_error_exit(ERR_SYS_MALLOC, m);
	((t_sphere *)m->obj[m->obj_count])->center = read_xyz(i, line, m);
	((t_sphere *)m->obj[m->obj_count])->diameter = read_double(i, line, m);
	((t_sphere *)m->obj[m->obj_count])->rgb = read_rgb(i, line, m);
	m->obj_count++;
	return (CMD_SPHERE);
}

int	read_file_plane(int *i, char *line, t_map *m)
{
	(*i) += 2;
	if (m->obj_count >= MAX_OBJ_COUNT)
		print_error_exit(ERR_RD_TOOMUCH_OBJ_SPECIFIED, m);
	m->obj_type[m->obj_count] = CMD_PLANE;
	m->obj[m->obj_count] = (t_plane *)malloc(sizeof(t_plane));
	if (!m->obj[m->obj_count])
		print_error_exit(ERR_SYS_MALLOC, m);
	((t_plane *)m->obj[m->obj_count])->position = read_xyz(i, line, m);
	((t_plane *)m->obj[m->obj_count])->normal = read_xyz(i, line, m);
	if (!is_normalized(&(((t_plane *)m->obj[m->obj_count])->normal)))
		print_error_exit(ERR_RD_OUTOFRANGE, m);
	((t_plane *)m->obj[m->obj_count])->rgb = read_rgb(i, line, m);
	m->obj_count++;
	return (CMD_PLANE);
}

int	read_file_square(int *i, char *line, t_map *m)
{
	(*i) += 2;
	if (m->obj_count >= MAX_OBJ_COUNT)
		print_error_exit(ERR_RD_TOOMUCH_OBJ_SPECIFIED, m);
	m->obj_type[m->obj_count] = CMD_SQUARE;
	m->obj[m->obj_count] = (t_square *)malloc(sizeof(t_square));
	if (!m->obj[m->obj_count])
		print_error_exit(ERR_SYS_MALLOC, m);
	((t_square *)m->obj[m->obj_count])->centr = read_xyz(i, line, m);
	((t_square *)m->obj[m->obj_count])->orientation = read_xyz(i, line, m);
	if (!is_normalized(&(((t_square *)m->obj[m->obj_count])->orientation)))
		print_error_exit(ERR_RD_OUTOFRANGE, m);
	((t_square *)m->obj[m->obj_count])->sidesiz = read_double(i, line, m);
	((t_square *)m->obj[m->obj_count])->rgb = read_rgb(i, line, m);
	ft_init_square(m->obj[m->obj_count]);
	m->obj_count++;
	return (CMD_SQUARE);
}

int	read_file_cylinder(int *i, char *line, t_map *m)
{
	(*i) += 2;
	if (m->obj_count >= MAX_OBJ_COUNT)
		print_error_exit(ERR_RD_TOOMUCH_OBJ_SPECIFIED, m);
	m->obj_type[m->obj_count] = CMD_CYLINDER;
	m->obj[m->obj_count] = (t_cylinder *)malloc(sizeof(t_cylinder));
	if (!m->obj[m->obj_count])
		print_error_exit(ERR_SYS_MALLOC, m);
	((t_cylinder *)m->obj[m->obj_count])->center = read_xyz(i, line, m);
	((t_cylinder *)m->obj[m->obj_count])->orientation = read_xyz(i, line, m);
	if (!is_normalized(&(((t_cylinder *)m->obj[m->obj_count])->orientation)))
		print_error_exit(ERR_RD_OUTOFRANGE, m);
	((t_cylinder *)m->obj[m->obj_count])->diameter = read_double(i, line, m);
	((t_cylinder *)m->obj[m->obj_count])->height = read_double(i, line, m);
	((t_cylinder *)m->obj[m->obj_count])->rgb = read_rgb(i, line, m);
	m->obj_count++;
	return (CMD_CYLINDER);
}

int	read_file_triangle(int *i, char *line, t_map *m)
{
	(*i) += 2;
	if (m->obj_count >= MAX_OBJ_COUNT)
		print_error_exit(ERR_RD_TOOMUCH_OBJ_SPECIFIED, m);
	m->obj_type[m->obj_count] = CMD_TRIANGLE;
	m->obj[m->obj_count] = (t_triangle *)malloc(sizeof(t_triangle));
	if (!m->obj[m->obj_count])
		print_error_exit(ERR_SYS_MALLOC, m);
	((t_triangle *)m->obj[m->obj_count])->first = read_xyz(i, line, m);
	((t_triangle *)m->obj[m->obj_count])->second = read_xyz(i, line, m);
	((t_triangle *)m->obj[m->obj_count])->third = read_xyz(i, line, m);
	((t_triangle *)m->obj[m->obj_count])->rgb = read_rgb(i, line, m);
	ft_init_triangle(m->obj[m->obj_count]);
	m->obj_count++;
	return (CMD_TRIANGLE);
}
