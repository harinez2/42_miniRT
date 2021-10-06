#include	"main.h"

void	init_m(t_map *m)
{
	m->window_x = 242;
	m->window_y = 242;
	m->eye_count = 0;
	m->ceye_num = 0;
	m->light_count = 0;
	m->ambItsty = -1;
	m->kAmb.r = -1;
	m->kAmb.g = -1;
	m->kAmb.b = -1;
	m->shininess = 8;
	m->obj_count = 0;
	m->bmp = 0;
	m->dsp = 0;
	m->endian = get_endian();
}

static void	arrange_constant_values(t_map *m)
{
	m->kDif.r = 2 * (1 - m->kAmb.r) / 3;
	m->kDif.g = 2 * (1 - m->kAmb.g) / 3;
	m->kDif.b = 2 * (1 - m->kAmb.b) / 3;
	m->kSpe.r = (1 - m->kAmb.r) / 3;
	m->kSpe.g = (1 - m->kAmb.g) / 3;
	m->kSpe.b = (1 - m->kAmb.b) / 3;
}

int	main(int argc, char **argv)
{
	t_map	m;
	int		i;

	init_m(&m);
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
