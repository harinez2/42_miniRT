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

static void	print_m_eye_light(t_map *m)
{
	int	i;

	i = 0;
	while (i < m->eye_count)
	{
		printf("  Eye[%d]   : %.2f, %.2f, %.2f\n", i,
			m->v_eye[i].x, m->v_eye[i].y, m->v_eye[i].z);
		i++;
	}
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
	print_m_eye_light(m);
	print_m_obj(m);
	printf("\n  Local Endian : %d\n\n", m->endian);
}
