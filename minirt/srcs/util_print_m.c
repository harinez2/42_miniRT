#include	"main.h"

static void	print_m_config(t_map *m)
{
	printf("  R        : %d x %d\n", m->window_x, m->window_y);
	printf("  ambItsty : %.2f\n", m->ambItsty);
	printf("  kAmb     : %.2f, %.2f, %.2f\n", m->kAmb.r, m->kAmb.g, m->kAmb.b);
	printf("  kDif     : %.2f, %.2f, %.2f\n", m->kDif.r, m->kDif.g, m->kDif.b);
	printf("  kSpe     : %.2f, %.2f, %.2f\n", m->kSpe.r, m->kSpe.g, m->kSpe.b);
	printf("  shininess: %.2f\n\n", m->shininess);
}

static void	print_m_eye(t_map *m)
{
	int	i;

	i = 0;
	while (i < m->cam_cnt)
	{
		printf("  Camera[%d]: pos: %.2f, %.2f, %.2f / orien: %.2f, %.2f, %.2f / fov:%.2f\n",
			i, m->cam[i].pos.x, m->cam[i].pos.y, m->cam[i].pos.z,
			m->cam[i].orien.x, m->cam[i].orien.y, m->cam[i].orien.z, m->cam[i].fov);
		i++;
	}
	printf("  Current Camera[%d]: pos: %.2f, %.2f, %.2f / orien: %.2f, %.2f, %.2f / distance:%.2f\n",
		m->curr_cam_num, m->curr_cam.pos.x, m->curr_cam.pos.y, m->curr_cam.pos.z,
		m->curr_cam.orien.x, m->curr_cam.orien.y, m->curr_cam.orien.z,
		m->distance_cam_scr);
	printf("                     basex: %.2f, %.2f, %.2f / basey: %.2f, %.2f, %.2f\n\n",
		m->v_basevec_scrx.x, m->v_basevec_scrx.y, m->v_basevec_scrx.z,
		m->v_basevec_scry.x, m->v_basevec_scry.y, m->v_basevec_scry.z);
}

static void	print_m_light(t_map *m)
{
	int	i;

	i = 0;
	while (i < m->light_count)
	{
		printf("  Light[%d] : ", i);
		ft_vecprint(&m->v_light[i]);
		printf(" / ");
		ft_colorprint(&m->light_rgb[i]);
		printf(" (itsty:%.2f)\n", m->litItsty[i]);
		i++;
	}
}

static void	print_m_obj(t_map *m)
{
	int	i;

	printf("\n  obj_count: %d\n", m->obj_count);
	i = 0;
	while (i < m->obj_count)
	{
		printf("  [%d] ", i);
		if (m->obj_type[i] == CMD_SPHERE)
			print_sphere(m->obj[i]);
		else if (m->obj_type[i] == CMD_PLANE)
			print_plane(m->obj[i]);
		else if (m->obj_type[i] == CMD_SQUARE)
			print_square(m->obj[i]);
		else if (m->obj_type[i] == CMD_CYLINDER)
			print_cylinder(m->obj[i]);
		else if (m->obj_type[i] == CMD_TRIANGLE)
			print_triangle(m->obj[i]);
		i++;
	}
}

void	print_m(t_map *m)
{
	printf("\n>>>>> Current config\n");
	print_m_config(m);
	print_m_eye(m);
	print_m_light(m);
	print_m_obj(m);
	printf("\n  Local Endian : %d\n\n", m->endian);
}
