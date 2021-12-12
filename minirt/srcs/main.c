#include	"main.h"

static void	show_usage_exit(void)
{
	printf("Usage: miniRT [options] [filename]\n");
	printf("  options:\n");
	printf("    --help       Show help.\n");
	printf("    --save       Save image as bmp file.\n");
	printf("    -v           Show detail config on screen.\n");
	exit(0);
}

static void	read_params(int argc, char **argv, t_map *m)
{
	int		i;

	if (argc < 2)
		print_error_exit(ERR_SYS_PARAMETER, m);
	if (ft_strncmp(argv[1], "--help", 7) == 0)
		show_usage_exit();
	i = 1;
	while (++i < argc)
	{
		if (ft_strncmp(argv[i], "--save", 7) == 0)
			m->bmp = 1;
		else if (ft_strncmp(argv[i], "-v", 3) == 0)
			m->dsp = 1;
		else
			print_error_exit(ERR_SYS_PARAMETER, m);
	}
	read_config_file(argv[1], m);
}

int	main(int argc, char **argv)
{
	t_map	m;

	init_map(&m);
	read_params(argc, argv, &m);
	arrange_constant_values(&m);
	if (m.dsp)
		print_m(&m);
	if (m.bmp == 1)
		write_bmp(&m);
	else
		display_window(&m);
	free_map(&m);
	return (0);
}
