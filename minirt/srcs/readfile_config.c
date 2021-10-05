#include	"main.h"

int	read_file_resolution(int *i, char *line, t_map *m)
{
	(*i)++;
	if (m->window_x == -1)
	{
		m->window_x = read_int(i, line);
		m->window_y = read_int(i, line);
		if (m->window_x <= 0 || m->window_y <= 0)
			print_error_exit(ERR_RD_OUTOFRANGE_SCREEN, m);
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
		m->ambItsty = read_double(i, line);
		m->kAmb = read_rgb(i, line, m);
	}
	else
		print_error_exit(ERR_RD_REDEFINED_A, m);
	return (CMD_AMBIENT);
}

int	read_file_camera(int *i, char *line, t_map *m)
{
	(*i)++;
	m->v_eye[m->eye_count] = read_xyz(i, line, m);
	if (m->eye_count == 0)
		m->v_ceye = m->v_eye[0];
	m->v_eye_orientation[m->eye_count] = read_xyz(i, line, m);
	if (m->eye_count == 0)
		m->v_corientation = m->v_eye_orientation[0];
	m->eye_fov[m->eye_count++] = read_double(i, line);
	return (CMD_CAMERA);
}

int	read_file_light(int *i, char *line, t_map *m)
{
	(*i)++;
	m->v_light[m->light_count] = read_xyz(i, line, m);
	m->litItsty[m->light_count] = read_double(i, line);
	m->light_rgb[m->light_count++] = read_rgb(i, line, m);
	return (CMD_LIGHT);
}
