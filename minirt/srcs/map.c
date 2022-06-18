#include	"main.h"

void	init_map(t_map *m)
{
	m->mlx = NULL;
	m->win = NULL;
	m->image = NULL;
	m->imgdata = NULL;
	m->window_x = -1;
	m->window_y = -1;
	m->cam_cnt = 0;
	m->curr_cam_num = 0;
	m->lit_cnt = 0;
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

#ifdef BONUS

static void	calc_kdif_kspe(t_map *m)
{
	m->kDif.r = 1 - m->kAmb.r;
	m->kDif.g = 1 - m->kAmb.g;
	m->kDif.b = 1 - m->kAmb.b;
	m->kSpe.r = (1 - m->kAmb.r) / 3;
	m->kSpe.g = (1 - m->kAmb.g) / 3;
	m->kSpe.b = (1 - m->kAmb.b) / 3;
}

#else

static void	calc_kdif_kspe(t_map *m)
{
	m->kDif.r = 1 - m->kAmb.r;
	m->kDif.g = 1 - m->kAmb.g;
	m->kDif.b = 1 - m->kAmb.b;
}

#endif

void	arrange_constant_values(t_map *m)
{
	m->kAmb.r = m->kAmb.r * m->ambItsty;
	m->kAmb.g = m->kAmb.g * m->ambItsty;
	m->kAmb.b = m->kAmb.b * m->ambItsty;
	calc_kdif_kspe(m);
	if (m->window_x == -1)
	{
		m->window_x = 512;
		m->window_y = 512;
	}
	init_screen_values(m);
}

void	free_map(t_map *m)
{
	int		i;

	if (m->image)
		mlx_destroy_image(m->mlx, m->image);
	i = 0;
	while (i < m->obj_count)
	{
		free(m->obj[i]);
		m->obj[i] = NULL;
		i++;
	}
}
