#include	"main.h"

double	get_nearest_obj(t_vec v_w, t_vec vstart, int i, t_map *m)
{
	double	chkt;

	chkt = -1;
	if (m->obj_type[i] == CMD_SPHERE)
		chkt = get_nearest_sphere(v_w, vstart, (t_sphere *)m->obj[i]);
	else if (m->obj_type[i] == CMD_PLANE)
		chkt = get_nearest_plane(v_w, vstart, (t_plane *)m->obj[i]);
	else if (m->obj_type[i] == CMD_SQUARE)
		chkt = get_nearest_square(v_w, vstart, (t_square *)m->obj[i]);
	else if (m->obj_type[i] == CMD_CYLINDER)
		chkt = get_nearest_cylinder(v_w, vstart, (t_cylinder *)m->obj[i]);
	else if (m->obj_type[i] == CMD_TRIANGLE)
		chkt = get_nearest_triangle(v_w, vstart, (t_triangle *)m->obj[i]);
	return (chkt);
}

int	get_minimum_t_for_shadow(
	t_vec v_w, t_vec vstart, t_map *m, double *hit_t)
{
	double		t;
	int			hit_i;
	int			i;

	*hit_t = -1;
	hit_i = -1;
	i = 0;
	while (i < m->obj_count)
	{
		t = get_nearest_obj(v_w, vstart, i, m);
		if (t > 0.001 && (*hit_t == -1 || t < *hit_t))
		{
			*hit_t = t;
			hit_i = i;
		}
		i++;
	}
	return (hit_i);
}

t_color	ray_trace_obj(t_vec v_w, t_map *m, int i, double t)
{
	t_color	color;

	if (i == -1)
		set_color(&color, 30, 60, 60);
		// set_color(&color, 92, 151, 243);
	else if (m->obj_type[i] == CMD_SPHERE)
		color = ray_trace_sphere(v_w, m, (t_sphere *)m->obj[i], t);
	else if (m->obj_type[i] == CMD_PLANE)
		color = ray_trace_plane(v_w, m, (t_plane *)m->obj[i], t);
	else if (m->obj_type[i] == CMD_SQUARE)
		color = ray_trace_square(v_w, m, (t_square *)m->obj[i], t);
	else if (m->obj_type[i] == CMD_CYLINDER)
		color = ray_trace_cylinder(v_w, m, (t_cylinder *)m->obj[i], t);
	else if (m->obj_type[i] == CMD_TRIANGLE)
		color = ray_trace_triangle(v_w, m, (t_triangle *)m->obj[i], t);
	return (color);
}

t_color	decide_color_with_raytracing(t_vec v_w, t_map *m)
{
	double	hit_t;
	int		hit_i;

	hit_i = get_minimum_t_for_shadow(v_w, m->curr_cam.pos, m, &hit_t);
	return (ray_trace_obj(v_w, m, hit_i, hit_t));
}
