#include	"main.h"

void	ft_init_square(t_square *ts)
{
	t_vec	a;
	t_vec	b;
	t_vec	c;
	t_vec	d;

	if (ts->orientation.x != 0)
	{
		a = ft_vec(0, ts->center.y + ts->sidesize, ts->center.z + ts->sidesize);
		b = ft_vec(0, ts->center.y + ts->sidesize, ts->center.z - ts->sidesize);
		c = ft_vec(0, ts->center.y - ts->sidesize, ts->center.z - ts->sidesize);
		d = ft_vec(0, ts->center.y - ts->sidesize, ts->center.z + ts->sidesize);
	}
	else if (ts->orientation.y != 0)
	{
		a = ft_vec(ts->center.x + ts->sidesize, 0, ts->center.z + ts->sidesize);
		b = ft_vec(ts->center.x + ts->sidesize, 0, ts->center.z - ts->sidesize);
		c = ft_vec(ts->center.x - ts->sidesize, 0, ts->center.z - ts->sidesize);
		d = ft_vec(ts->center.x - ts->sidesize, 0, ts->center.z + ts->sidesize);
	}
	else
	{
		a = ft_vec(ts->center.x + ts->sidesize, ts->center.y + ts->sidesize, 0);
		b = ft_vec(ts->center.x + ts->sidesize, ts->center.y - ts->sidesize, 0);
		c = ft_vec(ts->center.x - ts->sidesize, ts->center.y - ts->sidesize, 0);
		d = ft_vec(ts->center.x - ts->sidesize, ts->center.y + ts->sidesize, 0);
	}
	ts->tr_a.first = a;
	ts->tr_a.second = b;
	ts->tr_a.third = c;
	ts->tr_a.rgb = ts->rgb;
	ts->tr_b.first = a;
	ts->tr_b.second = c;
	ts->tr_b.third = d;
	ts->tr_b.rgb = ts->rgb;
	ft_init_triangle(&ts->tr_a);
	ft_init_triangle(&ts->tr_b);
}

double	get_nearest_square(t_vec v_w, t_vec v_eye, t_square *ts)
{
	double	t;
	double	t1;
	double	t2;

	t1 = get_nearest_triangle(v_w, v_eye, &ts->tr_a);
	t2 = get_nearest_triangle(v_w, v_eye, &ts->tr_b);
	if (t1 > 0 && t2 > 0)
		t = fmin(t1, t2);
	else
		t = fmax(t1, t2);
	return (t);
}

t_color	ray_trace_square(t_vec v_w, t_map *m, t_square *ts, double t)
{
	return (ray_trace_plane(v_w, m, &ts->tr_a.plane, t));
}

void	print_square(t_square *ts)
{
	printf("Square: ");
	ft_vecprint(&ts->center);
	printf(" / ");
	ft_vecprint(&ts->orientation);
	printf(" (ss:%.2f) / ", ts->sidesize);
	ft_colorprint(&ts->rgb);
	printf("\n");
	printf("      ");
	print_triangle(&ts->tr_a);
	printf("      ");
	print_triangle(&ts->tr_b);
}
