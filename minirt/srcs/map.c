#include	"main.h"

void	init_map(t_map *m)
{
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

void	arrange_constant_values(t_map *m)
{
	m->kAmb.r = m->kAmb.r * m->ambItsty;
	m->kAmb.g = m->kAmb.g * m->ambItsty;
	m->kAmb.b = m->kAmb.b * m->ambItsty;
	m->kDif.r = 2 * (1 - m->kAmb.r) / 3;
	m->kDif.g = 2 * (1 - m->kAmb.g) / 3;
	m->kDif.b = 2 * (1 - m->kAmb.b) / 3;
	m->kSpe.r = (1 - m->kAmb.r) / 3;
	m->kSpe.g = (1 - m->kAmb.g) / 3;
	m->kSpe.b = (1 - m->kAmb.b) / 3;
	if (m->window_x == -1)
	{
		m->window_x = 242;
		m->window_y = 242;
	}
	init_screen_values(m);
}

void	free_map(t_map *m)
{
	int		i;

	i = 0;
	while (i < m->obj_count)
	{
		free(m->obj[i]);
		m->obj[i] = NULL;
		i++;
	}
}
