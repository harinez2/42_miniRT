#include	"main.h"

int	readCmd(int *i, char *line)
{
	int	cmd;
	
	cmd = -1;
	if (line[*i] == 'R')
		cmd = CMD_RESOLUTION;
	else if (line[*i] == 'A')
		cmd = CMD_AMBIENT;
	else if (line[*i] == 'c')
		cmd = CMD_CAMERA;
	else if (line[*i] == 'l')
		cmd = CMD_LIGHT;
	else if (line[*i] == 's' && line[*i + 1] == 'p')
		cmd = CMD_SPHERE;
	else if (line[*i] == 'p' && line[*i + 1] == 'l')
		cmd = CMD_PLANE;
	else if (line[*i] == 's' && line[*i + 1] == 'q')
		cmd = CMD_SQUARE;
	else if (line[*i] == 'c' && line[*i + 1] == 'y')
		cmd = CMD_CYLINDER;
	else if (line[*i] == 't' && line[*i + 1] == 'r')
		cmd = CMD_TRIANGLE;
	if (0 <= cmd && cmd < 10)
		i++;
	else
		i += 2;
	return (cmd);
}

void	readFromFile(char *filename, t_map *m)
{
	int	fd;
	char	*line;
	int	i;
	int	j;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		write(1, "Failed to open file.\n", 21);
		exit(-1);
	}
	while (1)	
	{
		i = get_next_line(fd, &line);
		if (i <= 0)
			break;
		j = 0;
		while (line[j] == ' ')
			j++;
		if (line[j] == '#')
		{
			free(line);
			continue;
		}
		readCmd(&i, line);
		if (line[j] == 'R')
			printf("%s\n", line);
		else
			printf("%s\n", line);
		free(line);
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
