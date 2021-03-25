#include	"main.h"

double	ft_map(double x, int froma, int fromb, int toa, int tob)
{
	double pos = (x - (double)froma) / ((double)fromb - (double)froma);
	double ret = pos * ((double)tob - (double)toa) + (double)toa;
	return (ret);
}

void	print_m(t_map *m)
{
	printf("===== current config begin =====\n");
	printf("R        : %d x %d\n", m->window_x, m->window_y);
	printf("ambItsty : %.2f\n", m->ambItsty);
	printf("kAmb     : %.2f, %.2f, %.2f\n", m->kAmb.r, m->kAmb.g, m->kAmb.b);
	printf("kDif     : %.2f, %.2f, %.2f\n", m->kDif.r, m->kDif.g, m->kDif.b);
	printf("kSpe     : %.2f, %.2f, %.2f\n", m->kSpe.r, m->kSpe.g, m->kSpe.b);

	printf("shininess: %.2f\n", m->shininess);

	for (int i = 0; i < m->eye_count; i++)
		printf("Eye[%d]   : %.2f, %.2f, %.2f\n", i,
			m->v_eye[i].x, m->v_eye[i].y, m->v_eye[i].z);
	for (int i = 0; i < m->light_count; i++)
	{
		printf("Light[%d] : ", i);
		ft_vecprint(&m->v_light[i]);
		printf(" / ");
		ft_colorprint(&m->light_rgb[i]);
		printf(" (itsty:%.2f)\n", m->lightItsty[i]);
	}

	printf("obj_count: %d\n", m->obj_count);
	for (int i = 0; i < m->obj_count; i++)
	{
		printf("[%d] ", i);
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
	}
	printf("===== current config end =====\n\n");
}

int	decide_endian(void)
{
	int		a;
	int		local_endian;

	a = 0x11223344;
	if (((unsigned char *)&a)[0] == 0x11)
		local_endian = 1;
	else
		local_endian = 0;
	printf("Local Endian : %d.\n", local_endian);
	return (local_endian);
}