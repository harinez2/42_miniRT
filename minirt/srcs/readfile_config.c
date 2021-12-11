#include	"main.h"

int	read_file_resolution(int *i, char *line, t_map *m)
{
	(*i)++;
	if (m->window_x == -1)
	{
		m->window_x = read_int(i, line, m);
		m->window_y = read_int(i, line, m);
		if (m->window_x <= 0 || INT_MAX < m->window_x
			|| m->window_y <= 0 || INT_MAX < m->window_y)
			print_error_exit(ERR_RD_OUTOFRANGE, m);
	}
	else
		print_error_exit(ERR_RD_REDEFINED_R, m);
	return (CMD_RESOLUTION);
}

int	read_file_ambient(int *i, char *line, t_map *m)
{
	(*i)++;
	if (m->ambItsty == -1)
	{
		m->ambItsty = read_double(i, line, m);
		if (m->ambItsty < 0.0 || 1.0 < m->ambItsty)
			print_error_exit(ERR_RD_OUTOFRANGE, m);
		m->kAmb = read_rgb(i, line, m);
	}
	else
		print_error_exit(ERR_RD_REDEFINED_A, m);
	return (CMD_AMBIENT);
}

int	read_file_camera(int *i, char *line, t_map *m)
{
	(*i)++;
	if (m->cam_cnt >= MAX_CAMERA_COUNT)
		print_error_exit(ERR_RD_TOOMUCH_CAM_SPECIFIED, m);
	m->cam[m->cam_cnt].pos = read_xyz(i, line, m);
	m->cam[m->cam_cnt].orien = read_xyz(i, line, m);
	m->cam[m->cam_cnt].fov = read_double(i, line, m);
	if (m->cam_cnt == 0)
		m->curr_cam = m->cam[m->cam_cnt];
	m->cam_cnt++;
	return (CMD_CAMERA);
}

int	read_file_light(int *i, char *line, t_map *m)
{
	(*i)++;
	if (m->lit_cnt >= MAX_LIGHT_COUNT)
		print_error_exit(ERR_RD_TOOMUCH_LIT_SPECIFIED, m);
	m->lit[m->lit_cnt].pos = read_xyz(i, line, m);
	m->lit[m->lit_cnt].itsty = read_double(i, line, m);
	m->lit[m->lit_cnt++].rgb = read_rgb(i, line, m);
	return (CMD_LIGHT);
}
