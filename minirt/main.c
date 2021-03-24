#include	"main.h"

int		local_endian;

/*
 ** Resizing scale
 **/
double	ft_map(double x, int froma, int fromb, int toa, int tob)
{
	double pos = (x - (double)froma) / ((double)fromb - (double)froma);
	double ret = pos * ((double)tob - (double)toa) + (double)toa;
	return (ret);
}

t_color	decide_color(t_vec v_w, t_map *m)
{
	double	t;
	t_color		color;
	double 	chkt;

	t = -1;
	set_color(&color, 92, 151, 243);
	for (int i = 0; i < m->obj_count; i++)
	{
		chkt = -1;
		if (m->obj_type[i] == CMD_SPHERE)
			chkt = get_nearest_sphere(v_w, m->v_eye[0], (t_sphere *)m->obj[i]);
		else if (m->obj_type[i] == CMD_PLANE)
			chkt = get_nearest_plane(v_w, m->v_eye[0], (t_plane *)m->obj[i]);
		else if (m->obj_type[i] == CMD_SQUARE)
			chkt = get_nearest_square(v_w, m->v_eye[0], (t_square *)m->obj[i]);
		else if (m->obj_type[i] == CMD_CYLINDER)
			chkt = get_nearest_cylinder(v_w, m->v_eye[0], (t_cylinder *)m->obj[i]);
		else if (m->obj_type[i] == CMD_TRIANGLE)
			chkt = get_nearest_triangle(v_w, m->v_eye[0], (t_triangle *)m->obj[i]);
		if (chkt >= 0 && (t == -1 || chkt < t))
		{
			t = chkt;
			if (m->obj_type[i] == CMD_SPHERE)
				color = ray_trace_sphere(v_w, m, (t_sphere *)m->obj[i], chkt);
			else if (m->obj_type[i] == CMD_PLANE)
				color = ray_trace_plane(v_w, m, (t_plane *)m->obj[i], chkt);
			else if (m->obj_type[i] == CMD_SQUARE)
				color = ray_trace_square(v_w, m, (t_square *)m->obj[i], chkt);
			else if (m->obj_type[i] == CMD_CYLINDER)
				color = ray_trace_cylinder(v_w, m, (t_cylinder *)m->obj[i], chkt);
			else if (m->obj_type[i] == CMD_TRIANGLE)
				color = ray_trace_triangle(v_w, m, (t_triangle *)m->obj[i], chkt);
		}
	}
	return (color);
}

void	init_m(t_map *m)
{
	m->eye_count = 0;
	m->light_count = 0;
	m->obj_count = 0;
	
	m->window_x = -1;
	m->window_y = -1;

	m->kAmb.r = -1;
	m->kAmb.g = -1;
	m->kAmb.b = -1;
	
	m->ambItsty = -1;
}

void	set_default_Value(t_map *m)
{
	m->window_x = 242;
	m->window_y = 242;

	ft_vecset(&m->v_eye[m->eye_count++], 0, 0, -5);
	ft_vecset(&m->v_eye[m->eye_count++], 0, 1, 2);

	ft_vecset(&m->v_light[m->light_count++], -5, 5, -5);
	ft_vecset(&m->v_light[m->light_count++], -5, 3, -2);

	m->kAmb.r = 0.01;
	m->kAmb.g = 0.01;
	m->kAmb.b = 0.01;

	m->kDif.r = 0.69;
	m->kDif.g = 0.0;
	m->kDif.b = 0.0;

	m->kSpe.r = 0.3;
	m->kSpe.g = 0.3;
	m->kSpe.b = 0.3;

	m->shininess = 8;

	m->lightItsty[0] = 1.0;
	m->ambItsty = 0.1;

	m->obj_type[m->obj_count] = CMD_SPHERE;
	m->obj[m->obj_count] = (t_sphere *)malloc(sizeof(t_sphere));
	ft_vecset(&((t_sphere *)m->obj[m->obj_count])->center, 3, 0, 25);
	((t_sphere *)m->obj[m->obj_count])->diameter = 1.0;
	m->obj_count++;

	m->obj_type[m->obj_count] = CMD_SPHERE;
	m->obj[m->obj_count] = (t_sphere *)malloc(sizeof(t_sphere));
	ft_vecset(&((t_sphere *)m->obj[m->obj_count])->center, 2, 0, 20);
	((t_sphere *)m->obj[m->obj_count])->diameter = 1.0;
	m->obj_count++;

	// m->obj_type[m->obj_count] = CMD_SPHERE;
	// m->obj[m->obj_count] = (t_sphere *)malloc(sizeof(t_sphere));
	// ft_vecset(&((t_sphere *)m->obj[m->obj_count])->center, 1, 0, 15);
	// ((t_sphere *)m->obj[m->obj_count])->diameter = 1.0;
	// m->obj_count++;

	// m->obj_type[m->obj_count] = CMD_SPHERE;
	// m->obj[m->obj_count] = (t_sphere *)malloc(sizeof(t_sphere));
	// ft_vecset(&((t_sphere *)m->obj[m->obj_count])->center, 0, 0, 10);
	// ((t_sphere *)m->obj[m->obj_count])->diameter = 1.0;
	// m->obj_count++;

	// m->obj_type[m->obj_count] = CMD_SPHERE;
	// m->obj[m->obj_count] = (t_sphere *)malloc(sizeof(t_sphere));
	// ft_vecset(&((t_sphere *)m->obj[m->obj_count])->center, -1, 0, 5);
	// ((t_sphere *)m->obj[m->obj_count])->diameter = 1.0;
	// m->obj_count++;

	// m->obj_type[m->obj_count] = CMD_PLANE;
	// m->obj[m->obj_count] = (t_plane *)malloc(sizeof(t_plane));
	// ft_vecset(&((t_plane *)m->obj[m->obj_count])->normal, 0.0, 1.0, 0.0);
	// ft_vecset(&((t_plane *)m->obj[m->obj_count])->position, 0.0, -1.0, 0.0);
	// m->obj_count++;

	// m->obj_type[m->obj_count] = CMD_CYLINDER;
	// m->obj[m->obj_count] = (t_cylinder *)malloc(sizeof(t_cylinder));
	// ft_vecset(&((t_cylinder *)m->obj[m->obj_count])->center, 3, 0, 25);
	// ft_vecset(&((t_cylinder *)m->obj[m->obj_count])->orientation, 0.0, -1.0, 0.0);
	// ((t_cylinder *)m->obj[m->obj_count])->diameter = 1.0;
	// ((t_cylinder *)m->obj[m->obj_count])->height = 2.0;
	// m->obj_count++;
	
	// m->obj_type[m->obj_count] = CMD_CYLINDER;
	// m->obj[m->obj_count] = (t_cylinder *)malloc(sizeof(t_cylinder));
	// ft_vecset(&((t_cylinder *)m->obj[m->obj_count])->center, 2, 0, 20);
	// ft_vecset(&((t_cylinder *)m->obj[m->obj_count])->orientation, 0.0, -1.0, 0.0);
	// ((t_cylinder *)m->obj[m->obj_count])->diameter = 1.0;
	// ((t_cylinder *)m->obj[m->obj_count])->height = 2.0;
	// m->obj_count++;
	
	// m->obj_type[m->obj_count] = CMD_CYLINDER;
	// m->obj[m->obj_count] = (t_cylinder *)malloc(sizeof(t_cylinder));
	// ft_vecset(&((t_cylinder *)m->obj[m->obj_count])->center, 1, 0, 15);
	// ft_vecset(&((t_cylinder *)m->obj[m->obj_count])->orientation, 0.0, -1.0, 0.0);
	// ((t_cylinder *)m->obj[m->obj_count])->diameter = 1.0;
	// ((t_cylinder *)m->obj[m->obj_count])->height = 2.0;
	// m->obj_count++;
	
	// m->obj_type[m->obj_count] = CMD_CYLINDER;
	// m->obj[m->obj_count] = (t_cylinder *)malloc(sizeof(t_cylinder));
	// ft_vecset(&((t_cylinder *)m->obj[m->obj_count])->center, 0, 0, 10);
	// ft_vecset(&((t_cylinder *)m->obj[m->obj_count])->orientation, 0.0, -1.0, 0.0);
	// ((t_cylinder *)m->obj[m->obj_count])->diameter = 1.0;
	// ((t_cylinder *)m->obj[m->obj_count])->height = 2.0;
	// m->obj_count++;
	
	// m->obj_type[m->obj_count] = CMD_CYLINDER;
	// m->obj[m->obj_count] = (t_cylinder *)malloc(sizeof(t_cylinder));
	// ft_vecset(&((t_cylinder *)m->obj[m->obj_count])->center, -1, 0, 5);
	// ft_vecset(&((t_cylinder *)m->obj[m->obj_count])->orientation, 0.0, -1.0, 0.0);
	// ((t_cylinder *)m->obj[m->obj_count])->diameter = 1.0;
	// ((t_cylinder *)m->obj[m->obj_count])->height = 2.0;
	// m->obj_count++;

	m->obj_type[m->obj_count] = CMD_TRIANGLE;
	m->obj[m->obj_count] = (t_triangle *)malloc(sizeof(t_triangle));
	ft_vecset(&((t_triangle *)m->obj[m->obj_count])->first, 1.0, -1.0, 1.0);
	ft_vecset(&((t_triangle *)m->obj[m->obj_count])->second, -1.0, -1.0, 1.0);
	ft_vecset(&((t_triangle *)m->obj[m->obj_count])->third, 0.0, -1.0, 8.0);
	// ft_vecset(&((t_triangle *)m->obj[m->obj_count])->first, 0.0, -1.0, 0.0);
	// ft_vecset(&((t_triangle *)m->obj[m->obj_count])->second, 0.0, 0.0, -1.0);
	// ft_vecset(&((t_triangle *)m->obj[m->obj_count])->third, 1.0, 0.0, 00.0);
	// ft_vecset(&((t_triangle *)m->obj[m->obj_count])->first, 10.0, 20.0, 10.0);
	// ft_vecset(&((t_triangle *)m->obj[m->obj_count])->second, 10.0, 10.0, 20.0);
	// ft_vecset(&((t_triangle *)m->obj[m->obj_count])->third, 20.0, 10.0, 10.0);
	ft_initTriangle(m->obj[m->obj_count]);
	m->obj_count++;

	m->obj_type[m->obj_count] = CMD_SQUARE;
	m->obj[m->obj_count] = (t_square *)malloc(sizeof(t_square));
	ft_vecset(&((t_square *)m->obj[m->obj_count])->center, 1.0, -1.0, 1.0);
	ft_vecset(&((t_square *)m->obj[m->obj_count])->orientation, 0.0, 1.0, 0.0);
	((t_square *)m->obj[m->obj_count])->sidesize = 10.0;
	ft_initSquare(m->obj[m->obj_count]);
	m->obj_count++;

}

void	print_m(t_map *m)
{
	printf("===== current config begin =====\n");
	printf("R        : %d x %d\n", m->window_x, m->window_y);
	for (int i = 0; i < m->eye_count; i++)
		printf("Eye[%d]   : %.2f, %.2f, %.2f\n", i, m->v_eye[i].x, m->v_eye[i].y, m->v_eye[i].z);
	for (int i = 0; i < m->light_count; i++)
		printf("Light[%d] : %.2f, %.2f, %.2f\n", i, m->v_light[i].x, m->v_light[i].y, m->v_light[i].z);

	printf("kAmb     : %.2f, %.2f, %.2f\n", m->kAmb.r, m->kAmb.g, m->kAmb.b);
	printf("kDif     : %.2f, %.2f, %.2f\n", m->kDif.r, m->kDif.g, m->kDif.b);
	printf("kSpe     : %.2f, %.2f, %.2f\n", m->kSpe.r, m->kSpe.g, m->kSpe.b);

	printf("shininess     : %.2f\n", m->shininess);

	for (int i = 0; i < m->light_count; i++)
		printf("lightItsty[%d] : %.2f\n", i, m->lightItsty[i]);
	printf("ambItsty      : %.2f\n", m->ambItsty);
	printf("obj_count     : %d\n", m->obj_count);
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

void	decide_endian(void)
{
	int		a;

	a = 0x11223344;
	if (((unsigned char *)&a)[0] == 0x11)
		local_endian = 1;
	else
		local_endian = 0;
	printf("Local Endian : %d.\n",local_endian);
}

/*
 ** main func
 **/
int	main(int argc, char **argv)
{
	t_map	m;

	init_m(&m);
	if (argc >= 2)
		readFromFile(argv[1], &m);
	else
		set_default_Value(&m);
	//set_default_Value(&m);
	print_m(&m);

	decide_endian();
	if (argc >= 3 && strcmp(argv[2], "--save") == 0)
		write_bmp(&m);
	else
		display_window(&m);
	freeX(&m);
	return (0);
}
