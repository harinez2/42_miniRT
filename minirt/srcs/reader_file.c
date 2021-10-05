#include	"main.h"

static void	check_params_specified(t_map *m)
{
	if (m->window_x == -1)
		print_error_exit(ERR_CHK_NO_R, m);
	if (m->ambItsty == -1)
		print_error_exit(ERR_CHK_NO_A, m);
}

static int	readCmd1(int *i, char *line, t_map *m)
{
	int	cmd;

	cmd = CMD_NONE;
	if (line[*i] == 'R')
	{
		cmd = CMD_RESOLUTION;
		(*i)++;
		if (m->window_x == -1)
		{
			m->window_x = readInt(i, line);
			m->window_y = readInt(i, line);
			if (m->window_x <= 0 || m->window_y <= 0)
				print_error_exit(ERR_RD_OUTOFRANGE_SCREEN, m);
		}
		else
			print_error_exit(ERR_RD_REDEFINED_R, m);
	}
	else if (line[*i] == 'A')
	{
		cmd = CMD_AMBIENT;
		(*i)++;
		if (m->ambItsty == -1)
		{
			m->ambItsty = readDouble(i, line);
			m->kAmb = readRgb(i, line, m);
		}
		else
			print_error_exit(ERR_RD_REDEFINED_A, m);
	}
	else if (line[*i] == 'c' && line[*i + 1] != 'y')
	{
		cmd = CMD_CAMERA;
		(*i)++;
		m->v_eye[m->eye_count] = readXyz(i, line, m);
		if (m->eye_count == 0)
			m->v_ceye = m->v_eye[0];
		m->v_eye_orientation[m->eye_count] = readXyz(i, line, m);
		if (m->eye_count == 0)
			m->v_corientation = m->v_eye_orientation[0];
		m->eye_fov[m->eye_count++] = readDouble(i, line);
	}
	else if (line[*i] == 'l')
	{
		cmd = CMD_LIGHT;
		(*i)++;
		m->v_light[m->light_count] = readXyz(i, line, m);
		m->litItsty[m->light_count] = readDouble(i, line);
		m->light_rgb[m->light_count++] = readRgb(i, line, m);
	}
	else if (line[*i] == 's' && line[*i + 1] == 'p')
	{
		cmd = CMD_SPHERE;
		(*i) += 2;
		m->obj_type[m->obj_count] = CMD_SPHERE;
		m->obj[m->obj_count] = (t_sphere *)malloc(sizeof(t_sphere));
		((t_sphere *)m->obj[m->obj_count])->center = readXyz(i, line, m);
		((t_sphere *)m->obj[m->obj_count])->diameter = readDouble(i, line);
		((t_sphere *)m->obj[m->obj_count])->rgb = readRgb(i, line, m);
		m->obj_count++;
	}
	return (cmd);
}

static int	readCmd2(int *i, char *line, t_map *m)
{
	int	cmd;

	cmd = CMD_NONE;
	if (line[*i] == 'p' && line[*i + 1] == 'l')
	{
		cmd = CMD_PLANE;
		(*i) += 2;
		m->obj_type[m->obj_count] = CMD_PLANE;
		m->obj[m->obj_count] = (t_plane *)malloc(sizeof(t_plane));
		((t_plane *)m->obj[m->obj_count])->normal = readXyz(i, line, m);
		((t_plane *)m->obj[m->obj_count])->position = readXyz(i, line, m);
		((t_plane *)m->obj[m->obj_count])->rgb = readRgb(i, line, m);
		m->obj_count++;
	}
	else if (line[*i] == 's' && line[*i + 1] == 'q')
	{
		cmd = CMD_SQUARE;
		(*i) += 2;
		m->obj_type[m->obj_count] = CMD_SQUARE;
		m->obj[m->obj_count] = (t_square *)malloc(sizeof(t_square));
		((t_square *)m->obj[m->obj_count])->center = readXyz(i, line, m);
		((t_square *)m->obj[m->obj_count])->orientation = readXyz(i, line, m);
		((t_square *)m->obj[m->obj_count])->sidesize = readDouble(i, line);
		((t_sphere *)m->obj[m->obj_count])->rgb = readRgb(i, line, m);
		ft_init_square(m->obj[m->obj_count]);
		m->obj_count++;
	}
	else if (line[*i] == 'c' && line[*i + 1] == 'y')
	{
		cmd = CMD_CYLINDER;
		(*i) += 2;
		m->obj_type[m->obj_count] = CMD_CYLINDER;
		m->obj[m->obj_count] = (t_cylinder *)malloc(sizeof(t_cylinder));
		((t_cylinder *)m->obj[m->obj_count])->center = readXyz(i, line, m);
		((t_cylinder *)m->obj[m->obj_count])->orientation = readXyz(i, line, m);
		((t_cylinder *)m->obj[m->obj_count])->diameter = readDouble(i, line);
		((t_cylinder *)m->obj[m->obj_count])->height = readDouble(i, line);
		((t_cylinder *)m->obj[m->obj_count])->rgb = readRgb(i, line, m);
		m->obj_count++;
	}
	else if (line[*i] == 't' && line[*i + 1] == 'r')
	{
		cmd = CMD_TRIANGLE;
		(*i) += 2;
		m->obj_type[m->obj_count] = CMD_TRIANGLE;
		m->obj[m->obj_count] = (t_triangle *)malloc(sizeof(t_triangle));
		((t_triangle *)m->obj[m->obj_count])->first = readXyz(i, line, m);
		((t_triangle *)m->obj[m->obj_count])->second = readXyz(i, line, m);
		((t_triangle *)m->obj[m->obj_count])->third = readXyz(i, line, m);
		((t_triangle *)m->obj[m->obj_count])->rgb = readRgb(i, line, m);
		ft_init_triangle(m->obj[m->obj_count]);
		m->obj_count++;
	}
	return (cmd);
}

static int	read_line(char *line, t_map *m)
{
	int	i;
	int	ret;

	i = 0;
	skip_separater(&i, line);
	if (line[i] == '#' || line[i] == '\0')
		return (0);
	ret = readCmd1(&i, line, m);
	if (ret == CMD_NONE)
		ret = readCmd2(&i, line, m);
	if (ret < 0)
		return (ret);
	if (m->dsp)
		printf("read: %s\n", line);
	return (0);
}

void	read_config_file(char *filename, t_map *m)
{
	int		fd;
	char	*line;
	int		i;
	int		ret;

	ret = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		print_error_exit(ERR_SYS_FILEOPEN, m);
	if (m->dsp)
		ft_putstr(">>>>> Reading config file...\n");
	while (1)
	{
		i = get_next_line(fd, &line);
		if (i < 0)
			break ;
		ret = read_line(line, m);
		free(line);
		if (ret < 0)
			print_error_exit(ERR_RD_INCORRECTFORMAT, m);
		if (i == 0)
			break ;
	}
	close(fd);
	check_params_specified(m);
}
