#include	"main.h"

void    ft_init_square(t_square *ts)
{
    if (ts->orientation.x != 0)
    {

    }
    else if (ts->orientation.y != 0)
    {
        t_vec a = ft_vec(
            ts->center.x + ts->sidesize, 0, ts->center.z + ts->sidesize);
        t_vec b = ft_vec(
            ts->center.x + ts->sidesize, 0, ts->center.z - ts->sidesize);
        t_vec c = ft_vec(
            ts->center.x - ts->sidesize, 0, ts->center.z - ts->sidesize);
        t_vec d = ft_vec(
            ts->center.x - ts->sidesize, 0, ts->center.z + ts->sidesize);
        ts->tr_a.first = a;
        ts->tr_a.second = b;
        ts->tr_a.third = c;
        ts->tr_b.first = a;
        ts->tr_b.second = c;
        ts->tr_b.third = d;
        ft_init_triangle(&ts->tr_a);
        ft_init_triangle(&ts->tr_b);
    }
    else
    {

    }
}

double	get_nearest_square(t_vec v_w, t_vec v_eye, t_square *ts)
{
	double t;

	t = get_nearest_plane(v_w, v_eye, &ts->tr_a.plane);
	if (t >= 0)
	{
		;
	}
	//printf("%.2f ", t);
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