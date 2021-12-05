#include	"main.h"

static double	get_distance_to_obj(t_vec v_w, int i, t_map *m)
{
	double	chkt;

	chkt = -1;
	if (m->obj_type[i] == CMD_SPHERE)
		chkt = get_distance_to_sphere(v_w, m, (t_sphere *)m->obj[i]);
	else if (m->obj_type[i] == CMD_PLANE)
		chkt = get_distance_to_plane(v_w, m, (t_plane *)m->obj[i]);
	else if (m->obj_type[i] == CMD_SQUARE)
		chkt = get_distance_to_square(v_w, m, (t_square *)m->obj[i]);
	else if (m->obj_type[i] == CMD_CYLINDER)
		chkt = get_distance_to_cylinder(v_w, m, (t_cylinder *)m->obj[i]);
	else if (m->obj_type[i] == CMD_TRIANGLE)
		chkt = get_distance_to_triangle(v_w, m, (t_triangle *)m->obj[i]);
	else if (m->obj_type[i] == CMD_CONE)
		chkt = get_distance_to_cone(v_w, m, (t_cone *)m->obj[i]);
	return (chkt);
}

int	get_minimum_distance_to_obj(t_vec v_w, t_map *m, double *hit_t)
{
	double		t;
	int			hit_i;
	int			i;

	*hit_t = -1;
	hit_i = -1;
	i = 0;
	while (i < m->obj_count)
	{
		t = get_distance_to_obj(v_w, i, m);
		if (t > 0 && (*hit_t == -1 || t < *hit_t))
		{
			*hit_t = t;
			hit_i = i;
		}
		i++;
	}
	return (hit_i);
}

static t_color	get_color_with_lightning(t_vec v_w, t_map *m, int i, double t)
{
	t_color			color;

	m->camdir.v_w = v_w;
	m->camdir.v_de = ft_vecsub(v_w, m->curr_cam.pos);
	m->camdir.v_tpos
		= ft_vecadd(m->curr_cam.pos, ft_vecmult(m->camdir.v_de, t));
	if (i == -1)
		set_color(&color, 0, 0, 0);
	else if (m->obj_type[i] == CMD_SPHERE)
		color = get_color_by_rt_sphere(m, (t_sphere *)m->obj[i]);
	else if (m->obj_type[i] == CMD_PLANE)
		color = get_color_by_rt_plane(m, (t_plane *)m->obj[i]);
	else if (m->obj_type[i] == CMD_SQUARE)
		color = get_color_by_rt_square(m, (t_square *)m->obj[i]);
	else if (m->obj_type[i] == CMD_CYLINDER)
		color = get_color_by_rt_cylinder(m, (t_cylinder *)m->obj[i]);
	else if (m->obj_type[i] == CMD_TRIANGLE)
		color = get_color_by_rt_triangle(m, (t_triangle *)m->obj[i]);
	else if (m->obj_type[i] == CMD_CONE)
		color = get_color_by_rt_cone(m, (t_cone *)m->obj[i]);
	return (color);
}

static t_color	get_color_with_raytracing(t_vec v_w, t_map *m)
{
	double	hit_t;
	int		hit_i;

	hit_i = get_minimum_distance_to_obj(v_w, m, &hit_t);
	return (get_color_with_lightning(v_w, m, hit_i, hit_t));
}

t_color	get_color_on_screen(t_map *m, int x, int y)
{
	t_vec		v_w;
	t_color		color;
	const int	print_foreach = 100;

	v_w.x = m->curr_cam.orien.x * m->scr.distance_cam_scr
		- (x - m->window_x / 2) * m->scr.unitvec_scrx.x
		- (y - m->window_y / 2) * m->scr.unitvec_scry.x;
	v_w.y = m->curr_cam.orien.y * m->scr.distance_cam_scr
		- (x - m->window_x / 2) * m->scr.unitvec_scrx.y
		- (y - m->window_y / 2) * m->scr.unitvec_scry.y;
	v_w.z = m->curr_cam.orien.z * m->scr.distance_cam_scr
		- (x - m->window_x / 2) * m->scr.unitvec_scrx.z
		- (y - m->window_y / 2) * m->scr.unitvec_scry.z;
	color = get_color_with_raytracing(v_w, m);
	if (m->dsp && x % print_foreach == 0 && y % print_foreach == 0)
	{
		if (x == 0)
			printf("\n");
		printf("  v_w : pos ");
		ft_vecprint(&v_w);
		printf("  / color %.2f, %.2f, %.2f\n", color.r, color.g, color.b);
	}
	return (color);
}
