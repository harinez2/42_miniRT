#include	"main.h"

static void	read_params(int argc, char **argv, t_map *m)
{
	int		i;
	int		paramflg;

	paramflg = 1;
	i = 0;
	while (++i < argc)
	{
		if (paramflg == 1 && ft_strncmp(argv[i], "--help", 7) == 0)
		{
			printf("Usage: miniRT [options] [filename]\n");
			printf("  options:\n");
			printf("    --help       Show help.\n");
			printf("    --save       Save image as bmp file.\n");
			printf("    -v           Show detail config on screen.\n");
			exit(0);
		}
		else if (paramflg == 1 && ft_strncmp(argv[i], "--save", 7) == 0)
			m->bmp = 1;
		else if (paramflg == 1 && ft_strncmp(argv[i], "-v", 3) == 0)
			m->dsp = 1;
		else if (paramflg < 0)
			print_error_exit(ERR_RD_INCORRECTFORMAT, m);
		else
		{
			--paramflg;
			read_config_file(argv[i], m);
		}
	}
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
