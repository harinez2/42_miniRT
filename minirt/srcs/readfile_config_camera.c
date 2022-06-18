#include	"main.h"

#ifdef BONUS

static void	check_camera_count(t_map *m)
{
	if (m->cam_cnt >= MAX_CAMERA_COUNT)
		print_error_exit(ERR_RD_TOOMUCH_CAM_SPECIFIED, m);
}

#else

static void	check_camera_count(t_map *m)
{
	if (m->cam_cnt >= 1)
		print_error_exit(ERR_RD_TOOMUCH_CAM_SPECIFIED, m);
}

#endif

int	read_file_camera(int *i, char *line, t_map *m)
{
	(*i)++;
	check_camera_count(m);
	m->cam[m->cam_cnt].pos = read_xyz(i, line, m);
	m->cam[m->cam_cnt].orien = read_xyz(i, line, m);
	if (!is_normalized(&(m->cam[m->cam_cnt].orien)))
		print_error_exit(ERR_RD_OUTOFRANGE, m);
	m->cam[m->cam_cnt].fov = read_double(i, line, m);
	if (m->cam[m->cam_cnt].fov < 0 || 180 < m->cam[m->cam_cnt].fov)
		print_error_exit(ERR_RD_OUTOFRANGE, m);
	if (m->cam_cnt == 0)
		m->curr_cam = m->cam[m->cam_cnt];
	m->cam_cnt++;
	skip_separater(i, line);
	if (!is_eol(i, line))
		print_error_exit(ERR_RD_INCORRECTFORMAT, m);
	return (CMD_CAMERA);
}
