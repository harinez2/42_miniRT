#include	"main.h"

int	readCmd1(int *i, char *line, t_map *m)
{
	int	cmd;
	int ret;
	
	cmd = -1;
	if (line[*i] == 'R')
	{
		cmd = CMD_RESOLUTION;
		(*i)++;
		m->window_x = readInt(i, line);
		m->window_y = readInt(i, line);
	}
	else if (line[*i] == 'A')
	{
		cmd = CMD_AMBIENT;
		(*i)++;
		m->ambientIntensity = readDouble(i, line);
		readRgb(i, line, &(m->kAmb));
	}
	else if (line[*i] == 'c' && line[*i + 1] != 'y')
	{
		cmd = CMD_CAMERA;
		(*i)++;
		readXyz(i, line, &(m->v_eye[0]));
		readXyz(i, line, NULL);
		ret = readInt(i, line);
printf("cmd:c int:%d ", ret);
	}
	else if (line[*i] == 'l')
	{
		cmd = CMD_LIGHT;
		(*i)++;
		readXyz(i, line, &(m->v_light[0]));
		m->lightIntensity = readDouble(i, line);
		readRgb(i, line, NULL);
	}
	else if (line[*i] == 's' && line[*i + 1] == 'p')
	{
		cmd = CMD_SPHERE;
		(*i) += 2;
		readXyz(i, line, &(m->v_sphere[0]));
		m->sphereR[0] = readDouble(i, line);
		readRgb(i, line, NULL);
	}
	return (cmd);
}

int	readCmd2(int *i, char *line, t_map *m)
{
	int	cmd;
	double retd;
	
	cmd = -1;
	if (line[*i] == 'p' && line[*i + 1] == 'l')
	{
		cmd = CMD_PLANE;
		(*i) += 2;
		readXyz(i, line, NULL);
		readXyz(i, line, NULL);
		readRgb(i, line, NULL);
printf("cmd:pl ");
	}
	else if (line[*i] == 's' && line[*i + 1] == 'q')
	{
		cmd = CMD_SQUARE;
		(*i) += 2;
		readXyz(i, line, NULL);
		readXyz(i, line, NULL);
		retd = readDouble(i, line);
printf("cmd:sq dbl:%.2f ", retd);
		readRgb(i, line, NULL);
	}
	else if (line[*i] == 'c' && line[*i + 1] == 'y')
	{
		cmd = CMD_CYLINDER;
		(*i) += 2;
		readXyz(i, line, NULL);
		readXyz(i, line, NULL);
		retd = readDouble(i, line);
printf("cmd:cy dbl:%.2f ", retd);
		retd = readDouble(i, line);
printf("dbl:%.2f ", retd);
		readRgb(i, line, NULL);
	}
	else if (line[*i] == 't' && line[*i + 1] == 'r')
	{
		cmd = CMD_TRIANGLE;
		(*i) += 2;
		readXyz(i, line, NULL);
		readXyz(i, line, NULL);
		readXyz(i, line, NULL);
		readRgb(i, line, NULL);
printf("cmd:tr ");
	}
	(void)m;
	return (cmd);
}

void	readLine(char *line, t_map *m)
{
	int	i;
	int	ret;

	i = 0;
	skipSep(&i, line);
	if (line[i] == '#' || line[i] == '\0')
		return;
	ret = readCmd1(&i, line, m);
	if (ret == -1)
		ret = readCmd2(&i, line, m);
printf(" // ");
	if (line[i] == 'R')
		printf("%s\n", line);
	else
		printf("%s\n", line);

}

void	readFromFile(char *filename, t_map *m)
{
	int	fd;
	char	*line;
	int	i;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		write(1, "Failed to open file.\n", 21);
		exit(-1);
	}
	while (1)	
	{
		i = get_next_line(fd, &line);
		if (i < 0)
			break;
		readLine(line, m);
		free(line);
		if (i == 0)
			break;
	}
	close(fd);
	(void)m;
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
