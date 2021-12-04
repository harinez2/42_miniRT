#include	"main.h"

int	main(int argc, char **argv)
{
	t_map	m;
	int		i;

	init_map(&m);
	i = 0;
	while (++i < argc)
	{
		if (ft_strncmp(argv[i], "--save", 7) == 0)
			m.bmp = 1;
		else if (ft_strncmp(argv[i], "-v", 3) == 0)
			m.dsp = 1;
		else
			read_config_file(argv[i], &m);
	}
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
