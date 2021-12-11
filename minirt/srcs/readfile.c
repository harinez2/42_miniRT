#include	"main.h"

static void	validate_before_opening_file(t_map *m, char *filename)
{
	if (m->dsp)
		printf(">>>>> Reading config file...\n");
	if (ft_strncmp(filename + ft_strlen(filename) - 3, ".rt", 4) != 0)
		print_error_exit(ERR_SYS_FILENAME, m);
}

static int	read_cmd(int *i, char *line, t_map *m)
{
	int	cmd;

	cmd = CMD_NONE;
	if (line[*i] == 'R')
		cmd = read_file_resolution(i, line, m);
	else if (line[*i] == 'A')
		cmd = read_file_ambient(i, line, m);
	else if (line[*i] == 'C')
		cmd = read_file_camera(i, line, m);
	else if (line[*i] == 'L')
		cmd = read_file_light(i, line, m);
	else if (ft_strncmp(&line[*i], "sp", 2) == 0)
		cmd = read_file_sphere(i, line, m);
	else if (ft_strncmp(&line[*i], "pl", 2) == 0)
		cmd = read_file_plane(i, line, m);
	else if (ft_strncmp(&line[*i], "sq", 2) == 0)
		cmd = read_file_square(i, line, m);
	else if (ft_strncmp(&line[*i], "cy", 2) == 0)
		cmd = read_file_cylinder(i, line, m);
	else if (ft_strncmp(&line[*i], "tr", 2) == 0)
		cmd = read_file_triangle(i, line, m);
	else if (ft_strncmp(&line[*i], "co", 2) == 0)
		cmd = read_file_cone(i, line, m);
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
	ret = read_cmd(&i, line, m);
	if (ret < 0)
		return (ret);
	if (m->dsp)
		printf("  read: %s\n", line);
	return (0);
}

void	read_config_file(char *filename, t_map *m)
{
	int		fd;
	char	*line;
	int		i;
	int		ret;

	ret = 0;
	validate_before_opening_file(m, filename);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		print_error_exit(ERR_SYS_FILEOPEN, m);
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
	validate_parameters(m);
}
