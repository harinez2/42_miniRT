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

void	set_default_value(t_map *m)
{

	m->ambItsty = 0.1;
	m->kAmb.r = 0.01;
	m->kAmb.g = 0.01;
	m->kAmb.b = 0.01;

	ft_vecset(&m->v_ceye, 0.05, 0.05, -5);
	//ft_vecset(&m->v_corientation, 0.01, 0.01, 1);
	ft_vecset(&m->v_corientation, -0.01, 0, 1);

	ft_vecset(&m->v_eye[m->eye_count], 0, 0, -5);
	ft_vecset(&m->v_eye_orientation[m->eye_count], 0, 0, -1);
	m->eye_fov[m->eye_count] = 22.6;
	m->eye_count++;

	ft_vecset(&m->v_eye[m->eye_count], 0, 0, -4);
	ft_vecset(&m->v_eye_orientation[m->eye_count], 0, 0, -1);
	m->eye_fov[m->eye_count] = 120;
	m->eye_count++;

	ft_vecset(&m->v_eye[m->eye_count], 0, 0, -3);
	ft_vecset(&m->v_eye_orientation[m->eye_count], 0, 0, -1);
	m->eye_fov[m->eye_count] = 120;
	m->eye_count++;

	ft_vecset(&m->v_eye[m->eye_count], 0, 0, -2);
	ft_vecset(&m->v_eye_orientation[m->eye_count], 0, 0, -1);
	m->eye_fov[m->eye_count] = 120;
	m->eye_count++;

	ft_vecset(&m->v_eye[m->eye_count], 0, 0, -1);
	ft_vecset(&m->v_eye_orientation[m->eye_count], 0, 0, -1);
	m->eye_fov[m->eye_count] = 120;
	m->eye_count++;

	ft_vecset(&m->v_eye[m->eye_count], 0, 0, 0);
	ft_vecset(&m->v_eye_orientation[m->eye_count], 0, 0, -1);
	m->eye_fov[m->eye_count] = 120;
	m->eye_count++;

	ft_vecset(&m->v_eye[m->eye_count], 0, 0, 1);
	ft_vecset(&m->v_eye_orientation[m->eye_count], 0, 0, -1);
	m->eye_fov[m->eye_count] = 120;
	m->eye_count++;

	ft_vecset(&m->v_light[m->light_count], -5, 5, -5);
	m->litItsty[m->light_count] = 1.0;
	set_color(&m->light_rgb[m->light_count], 1, 1, 1);
	m->light_count++;

	ft_vecset(&m->v_light[m->light_count], 5, 2, -5);
	m->litItsty[m->light_count] = 1.0;
	set_color(&m->light_rgb[m->light_count], 0.9, 0.9, 0);
	m->light_count++;

	m->obj_type[m->obj_count] = CMD_SPHERE;
	m->obj[m->obj_count] = (t_sphere *)malloc(sizeof(t_sphere));
	ft_vecset(&((t_sphere *)m->obj[m->obj_count])->center, 3, 0, 25);
	((t_sphere *)m->obj[m->obj_count])->diameter = 1.0;
	set_color(&((t_sphere *)m->obj[m->obj_count])->rgb, 0.5, 0.1, 0.9);
	m->obj_count++;

	m->obj_type[m->obj_count] = CMD_SPHERE;
	m->obj[m->obj_count] = (t_sphere *)malloc(sizeof(t_sphere));
	ft_vecset(&((t_sphere *)m->obj[m->obj_count])->center, 2, 0, 20);
	((t_sphere *)m->obj[m->obj_count])->diameter = 1.0;
	set_color(&((t_sphere *)m->obj[m->obj_count])->rgb, 0.1, 0.9, 0.5);
	m->obj_count++;

	// m->obj_type[m->obj_count] = CMD_SPHERE;
	// m->obj[m->obj_count] = (t_sphere *)malloc(sizeof(t_sphere));
	// ft_vecset(&((t_sphere *)m->obj[m->obj_count])->center, 1, 0, 15);
	// ((t_sphere *)m->obj[m->obj_count])->diameter = 1.0;
	// set_color(&((t_sphere *)m->obj[m->obj_count])->rgb, 0.5, 0.1, 0.9);
	// m->obj_count++;

	m->obj_type[m->obj_count] = CMD_SPHERE;
	m->obj[m->obj_count] = (t_sphere *)malloc(sizeof(t_sphere));
	ft_vecset(&((t_sphere *)m->obj[m->obj_count])->center, 0, 0, 10);
	((t_sphere *)m->obj[m->obj_count])->diameter = 1.0;
	set_color(&((t_sphere *)m->obj[m->obj_count])->rgb, 0.8, 0.6, 0.2);
	m->obj_count++;

	m->obj_type[m->obj_count] = CMD_SPHERE;
	m->obj[m->obj_count] = (t_sphere *)malloc(sizeof(t_sphere));
	ft_vecset(&((t_sphere *)m->obj[m->obj_count])->center, -1, 0, 5);
	((t_sphere *)m->obj[m->obj_count])->diameter = 1.0;
	set_color(&((t_sphere *)m->obj[m->obj_count])->rgb, 0.8, 0.6, 0.2);
	m->obj_count++;

	m->obj_type[m->obj_count] = CMD_PLANE;
	m->obj[m->obj_count] = (t_plane *)malloc(sizeof(t_plane));
	ft_vecset(&((t_plane *)m->obj[m->obj_count])->normal, 0.0, 1.0, 0.0);
	ft_vecset(&((t_plane *)m->obj[m->obj_count])->position, 0.0, -1.0, 0.0);
	set_color(&((t_plane *)m->obj[m->obj_count])->rgb, 1, 0.4, 0.4);
	m->obj_count++;

	// m->obj_type[m->obj_count] = CMD_CYLINDER;
	// m->obj[m->obj_count] = (t_cylinder *)malloc(sizeof(t_cylinder));
	// ft_vecset(&((t_cylinder *)m->obj[m->obj_count])->center, 3, 0, 25);
	// ft_vecset(&((t_cylinder *)m->obj[m->obj_count])->orientation, 0.0, -1.0, 0.0);
	// ((t_cylinder *)m->obj[m->obj_count])->diameter = 1.0;
	// ((t_cylinder *)m->obj[m->obj_count])->height = 2.0;
	// set_color(&((t_cylinder *)m->obj[m->obj_count])->rgb, 0.8, 0.6, 0.2);
	// m->obj_count++;
	
	// m->obj_type[m->obj_count] = CMD_CYLINDER;
	// m->obj[m->obj_count] = (t_cylinder *)malloc(sizeof(t_cylinder));
	// ft_vecset(&((t_cylinder *)m->obj[m->obj_count])->center, 2, 0, 20);
	// ft_vecset(&((t_cylinder *)m->obj[m->obj_count])->orientation, 0.0, -1.0, 0.0);
	// ((t_cylinder *)m->obj[m->obj_count])->diameter = 1.0;
	// ((t_cylinder *)m->obj[m->obj_count])->height = 2.0;
	// set_color(&((t_cylinder *)m->obj[m->obj_count])->rgb, 0.8, 0.6, 0.2);
	// m->obj_count++;
	
	// m->obj_type[m->obj_count] = CMD_CYLINDER;
	// m->obj[m->obj_count] = (t_cylinder *)malloc(sizeof(t_cylinder));
	// ft_vecset(&((t_cylinder *)m->obj[m->obj_count])->center, 1, 0, 15);
	// ft_vecset(&((t_cylinder *)m->obj[m->obj_count])->orientation, 0.0, -1.0, 0.0);
	// ((t_cylinder *)m->obj[m->obj_count])->diameter = 1.0;
	// ((t_cylinder *)m->obj[m->obj_count])->height = 2.0;
	// set_color(&((t_cylinder *)m->obj[m->obj_count])->rgb, 0.8, 0.6, 0.2);
	// m->obj_count++;
	
	// m->obj_type[m->obj_count] = CMD_CYLINDER;
	// m->obj[m->obj_count] = (t_cylinder *)malloc(sizeof(t_cylinder));
	// ft_vecset(&((t_cylinder *)m->obj[m->obj_count])->center, 0, 0, 10);
	// ft_vecset(&((t_cylinder *)m->obj[m->obj_count])->orientation, 0.0, -1.0, 0.0);
	// ((t_cylinder *)m->obj[m->obj_count])->diameter = 1.0;
	// ((t_cylinder *)m->obj[m->obj_count])->height = 2.0;
	// set_color(&((t_cylinder *)m->obj[m->obj_count])->rgb, 0.8, 0.6, 0.2);
	// m->obj_count++;
	
	// m->obj_type[m->obj_count] = CMD_CYLINDER;
	// m->obj[m->obj_count] = (t_cylinder *)malloc(sizeof(t_cylinder));
	// ft_vecset(&((t_cylinder *)m->obj[m->obj_count])->center, -1, 0, 5);
	// ft_vecset(&((t_cylinder *)m->obj[m->obj_count])->orientation, 0.0, -1.0, 0.0);
	// ((t_cylinder *)m->obj[m->obj_count])->diameter = 1.0;
	// ((t_cylinder *)m->obj[m->obj_count])->height = 2.0;
	// set_color(&((t_cylinder *)m->obj[m->obj_count])->rgb, 0.4, 0.5, 0.9);
	// m->obj_count++;

	// m->obj_type[m->obj_count] = CMD_TRIANGLE;
	// m->obj[m->obj_count] = (t_triangle *)malloc(sizeof(t_triangle));
	// ft_vecset(&((t_triangle *)m->obj[m->obj_count])->first, 1.0, -0.9, 1.0);
	// ft_vecset(&((t_triangle *)m->obj[m->obj_count])->second, -1.0, -0.9, 1.0);
	// ft_vecset(&((t_triangle *)m->obj[m->obj_count])->third, 0.0, -0.9, 8.0);
	// set_color(&((t_triangle *)m->obj[m->obj_count])->rgb, 0.5, 0.6, 0.3);
	// ft_init_triangle(m->obj[m->obj_count]);
	// m->obj_count++;

	// ft_vecset(&((t_triangle *)m->obj[m->obj_count])->first, 0.0, -1.0, 0.0);
	// ft_vecset(&((t_triangle *)m->obj[m->obj_count])->second, 0.0, 0.0, -1.0);
	// ft_vecset(&((t_triangle *)m->obj[m->obj_count])->third, 1.0, 0.0, 00.0);
	// ft_vecset(&((t_triangle *)m->obj[m->obj_count])->first, 10.0, 20.0, 10.0);
	// ft_vecset(&((t_triangle *)m->obj[m->obj_count])->second, 10.0, 10.0, 20.0);
	// ft_vecset(&((t_triangle *)m->obj[m->obj_count])->third, 20.0, 10.0, 10.0);

	// m->obj_type[m->obj_count] = CMD_SQUARE;
	// m->obj[m->obj_count] = (t_square *)malloc(sizeof(t_square));
	// ft_vecset(&((t_square *)m->obj[m->obj_count])->center, 1.0, -0.5, 1.0);
	// ft_vecset(&((t_square *)m->obj[m->obj_count])->orientation, 0.0, 1.0, 0.0);
	// ((t_square *)m->obj[m->obj_count])->sidesize = 1.0;
	// set_color(&((t_square *)m->obj[m->obj_count])->rgb, 0.9, 0.6, 0.3);
	// ft_init_square(m->obj[m->obj_count]);
	// m->obj_count++;

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

int		main(int argc, char **argv)
{
	t_map	m;
	int		i;

	init_m(&m);
	// set_default_value(&m);
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
