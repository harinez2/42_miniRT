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
		skip_separater(i, line);
		if (!is_eol(i, line))
			print_error_exit(ERR_RD_INCORRECTFORMAT, m);
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
		skip_separater(i, line);
		if (!is_eol(i, line))
			print_error_exit(ERR_RD_INCORRECTFORMAT, m);
	}
	else
		print_error_exit(ERR_RD_REDEFINED_A, m);
	return (CMD_AMBIENT);
}
