#include	"main.h"

int	readCmd1(int *i, char *line, t_map *m)
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
				ft_showErrorExit(ERR_RD_OUTOFRANGE_R);
		}
		else
			ft_showErrorExit(ERR_RD_REDEFINED_R);
	}
	else if (line[*i] == 'A')
	{
		cmd = CMD_AMBIENT;
		(*i)++;
		if (m->ambItsty == -1)
		{
			m->ambItsty = readDouble(i, line);
			readRgb(i, line, &(m->kAmb));
		}
		else
			ft_showErrorExit(ERR_RD_REDEFINED_A);
	}
	else if (line[*i] == 'c' && line[*i + 1] != 'y')
	{
		cmd = CMD_CAMERA;
		(*i)++;
		readXyz(i, line, &(m->v_eye[m->eye_count]));
		readXyz(i, line, &(m->v_eye_orientation[m->eye_count]));
		m->eye_fov[m->eye_count++] = readDouble(i, line);
	}
	else if (line[*i] == 'l')
	{
		cmd = CMD_LIGHT;
		(*i)++;
		readXyz(i, line, &(m->v_light[m->light_count]));
		m->lightItsty[m->light_count] = readDouble(i, line);
		readRgb(i, line, &m->light_rgb[m->light_count++]);
	}
	else if (line[*i] == 's' && line[*i + 1] == 'p')
	{
		cmd = CMD_SPHERE;
		(*i) += 2;
		m->obj_type[m->obj_count] = CMD_SPHERE;
		m->obj[m->obj_count] = (t_sphere *)malloc(sizeof(t_sphere));
		readXyz(i, line, &((t_sphere *)m->obj[m->obj_count])->center);
		((t_sphere *)m->obj[m->obj_count])->diameter = readDouble(i, line);
		readRgb(i, line, &((t_sphere *)m->obj[m->obj_count])->rgb);
		m->obj_count++;
	}
	return (cmd);
}

int	readCmd2(int *i, char *line, t_map *m)
{
	int	cmd;
	
	cmd = CMD_NONE;
	if (line[*i] == 'p' && line[*i + 1] == 'l')
	{
		cmd = CMD_PLANE;
		(*i) += 2;
		m->obj_type[m->obj_count] = CMD_PLANE;
		m->obj[m->obj_count] = (t_plane *)malloc(sizeof(t_plane));
		readXyz(i, line, &((t_plane *)m->obj[m->obj_count])->normal);
		readXyz(i, line, &((t_plane *)m->obj[m->obj_count])->position);
		readRgb(i, line, &((t_plane *)m->obj[m->obj_count])->rgb);
		m->obj_count++;
	}
	else if (line[*i] == 's' && line[*i + 1] == 'q')
	{
		cmd = CMD_SQUARE;
		(*i) += 2;
		m->obj_type[m->obj_count] = CMD_SQUARE;
		m->obj[m->obj_count] = (t_square *)malloc(sizeof(t_square));
		readXyz(i, line, &((t_square *)m->obj[m->obj_count])->center);
		readXyz(i, line, &((t_square *)m->obj[m->obj_count])->orientation);
		((t_square *)m->obj[m->obj_count])->sidesize = readDouble(i, line);
		readRgb(i, line, &((t_sphere *)m->obj[m->obj_count])->rgb);
		m->obj_count++;
	}
	else if (line[*i] == 'c' && line[*i + 1] == 'y')
	{
		cmd = CMD_CYLINDER;
		(*i) += 2;
		m->obj_type[m->obj_count] = CMD_CYLINDER;
		m->obj[m->obj_count] = (t_cylinder *)malloc(sizeof(t_cylinder));
		readXyz(i, line, &((t_cylinder *)m->obj[m->obj_count])->center);
		readXyz(i, line, &((t_cylinder *)m->obj[m->obj_count])->orientation);
		((t_cylinder *)m->obj[m->obj_count])->diameter = readDouble(i, line);
		((t_cylinder *)m->obj[m->obj_count])->height = readDouble(i, line);
		readRgb(i, line, &((t_cylinder *)m->obj[m->obj_count])->rgb);
		m->obj_count++;
	}
	else if (line[*i] == 't' && line[*i + 1] == 'r')
	{
		cmd = CMD_TRIANGLE;
		(*i) += 2;
		m->obj_type[m->obj_count] = CMD_TRIANGLE;
		m->obj[m->obj_count] = (t_triangle *)malloc(sizeof(t_triangle));
		readXyz(i, line, &((t_triangle *)m->obj[m->obj_count])->first);
		readXyz(i, line, &((t_triangle *)m->obj[m->obj_count])->second);
		readXyz(i, line, &((t_triangle *)m->obj[m->obj_count])->third);
		readRgb(i, line, &((t_triangle *)m->obj[m->obj_count])->rgb);
		m->obj_count++;
	}
	return (cmd);
}

int	readLine(char *line, t_map *m)
{
	int	i;
	int	ret;

	i = 0;
	skipSep(&i, line);
	if (line[i] == '#' || line[i] == '\0')
		return (0);
	ret = readCmd1(&i, line, m);
	if (ret == CMD_NONE)
		ret = readCmd2(&i, line, m);
	if (ret < 0)
		return (ret);
	printf("%s\n", line);
	return (0);
}

void	readFromFile(char *filename, t_map *m)
{
	int	fd;
	char	*line;
	int	i;
	int	ret;

	ret = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		write(1, "Failed to open file.\n", 21);
		exit(-1);
	}
	write(1, "===== Config from File =====\n", 29);
	while (1)	
	{
		i = get_next_line(fd, &line);
		if (i < 0)
			break;
		ret = readLine(line, m);
		free(line);
		if (ret < 0)
			ft_showErrorExit(ERR_RD_INCORRECTFORMAT);
		if (i == 0)
			break;
	}
	close(fd);
}

/*
void	readFromFile2(char *filename, t_map *m)
{
	int fd;
	char buf[20] = {};
	int i;

	init_m(m);

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		write(1, "Failed to open file.\n", 21);
		exit(-1);
	}
	while (1)	
	{
		i = read(fd, &buf, 1);
		if (i <= 0)
			break;
		if (buf[0] == ' ' || buf[0] == '\n')
			continue;
		else if (buf[0] == 'R')
		{
			;
		}
		printf("%s", buf);
	}
	//read(fd, buf, 199);
	//printf("readed:%s\n", buf);
	close(fd);
}
*/
