#include	"main.h"

double	ft_map(double x, int froma, int fromb, int toa, int tob)
{
	double	pos;
	double	ret;

	pos = (x - (double)froma) / ((double)fromb - (double)froma);
	ret = pos * ((double)tob - (double)toa) + (double)toa;
	return (ret);
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
	int	i;

	printf(">>>>> Current config\n");
	printf("  R        : %d x %d\n", m->window_x, m->window_y);
	printf("  ambItsty : %.2f\n", m->ambItsty);
	printf("  kAmb     : %.2f, %.2f, %.2f\n", m->kAmb.r, m->kAmb.g, m->kAmb.b);
	printf("  kDif     : %.2f, %.2f, %.2f\n", m->kDif.r, m->kDif.g, m->kDif.b);
	printf("  kSpe     : %.2f, %.2f, %.2f\n", m->kSpe.r, m->kSpe.g, m->kSpe.b);
	printf("  shininess: %.2f\n", m->shininess);
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
	print_m_obj(m);
	printf("\n  Local Endian : %d\n\n", m->endian);
}

int	get_endian(void)
{
	int		a;
	int		local_endian;

	a = 0x11223344;
	if (((unsigned char *)&a)[0] == 0x11)
		local_endian = 1;
	else
		local_endian = 0;
	return (local_endian);
}
