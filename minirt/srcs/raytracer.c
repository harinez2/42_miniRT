#include	"main.h"

static double	get_distance_to_obj(t_vec v_w, t_vec vstart, int i, t_map *m)
{
	double	chkt;

	chkt = -1;
	if (m->obj_type[i] == CMD_SPHERE)
		chkt = get_distance_to_sphere(v_w, vstart, (t_sphere *)m->obj[i]);
	else if (m->obj_type[i] == CMD_PLANE)
		chkt = get_distance_to_plane(v_w, vstart, (t_plane *)m->obj[i]);
	else if (m->obj_type[i] == CMD_SQUARE)
		chkt = get_distance_to_square(v_w, vstart, (t_square *)m->obj[i]);
	else if (m->obj_type[i] == CMD_CYLINDER)
		chkt = get_distance_to_cylinder(v_w, vstart, (t_cylinder *)m->obj[i]);
	else if (m->obj_type[i] == CMD_TRIANGLE)
		chkt = get_distance_to_triangle(v_w, vstart, (t_triangle *)m->obj[i]);
	return (chkt);
}

int	get_minimum_distance_to_obj(
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
		t = get_distance_to_obj(v_w, vstart, i, m);
		if (t > 0.001 && (*hit_t == -1 || t < *hit_t))
		{
			*hit_t = t;
			hit_i = i;
		}
		i++;
	}
	return (hit_i);
}

t_color	get_color_by_raytracing(t_vec v_w, t_map *m, int i, double t)
{
	t_color			color;
	t_curr_cam_vecs	cv;
	
	cv.v_w = v_w;
	cv.v_de = ft_vecsub(v_w, m->curr_cam.pos);
	cv.v_tpos = ft_vecadd(m->curr_cam.pos, ft_vecmult(cv.v_de, t));
	if (i == -1)
		set_color(&color, 30, 60, 60);
		// set_color(&color, 92, 151, 243);
	else if (m->obj_type[i] == CMD_SPHERE)
		color = get_color_by_rt_sphere(cv, m, (t_sphere *)m->obj[i]);
	else if (m->obj_type[i] == CMD_PLANE)
		color = get_color_by_rt_plane(cv, m, (t_plane *)m->obj[i]);
	else if (m->obj_type[i] == CMD_SQUARE)
		color = get_color_by_rt_square(cv, m, (t_square *)m->obj[i]);
	else if (m->obj_type[i] == CMD_CYLINDER)
		color = get_color_by_rt_cylinder(cv, m, (t_cylinder *)m->obj[i]);
	else if (m->obj_type[i] == CMD_TRIANGLE)
		color = get_color_by_rt_triangle(cv, m, (t_triangle *)m->obj[i]);
	return (color);
}

t_color	decide_color_with_raytracing(t_vec v_w, t_map *m)
{
	double	hit_t;
	int		hit_i;

	hit_i = get_minimum_distance_to_obj(v_w, m->curr_cam.pos, m, &hit_t);
	return (get_color_by_raytracing(v_w, m, hit_i, hit_t));
}
