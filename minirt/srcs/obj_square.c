#include	"main.h"

static void	set_four_vertex(t_multivec *mv, t_square *ts)
{
	if (ts->orientation.x != 0)
	{
		mv->a = ft_vec(0, ts->centr.y + ts->sidesiz, ts->centr.z + ts->sidesiz);
		mv->b = ft_vec(0, ts->centr.y + ts->sidesiz, ts->centr.z - ts->sidesiz);
		mv->c = ft_vec(0, ts->centr.y - ts->sidesiz, ts->centr.z - ts->sidesiz);
		mv->d = ft_vec(0, ts->centr.y - ts->sidesiz, ts->centr.z + ts->sidesiz);
	}
	else if (ts->orientation.y != 0)
	{
		mv->a = ft_vec(ts->centr.x + ts->sidesiz, 0, ts->centr.z + ts->sidesiz);
		mv->b = ft_vec(ts->centr.x + ts->sidesiz, 0, ts->centr.z - ts->sidesiz);
		mv->c = ft_vec(ts->centr.x - ts->sidesiz, 0, ts->centr.z - ts->sidesiz);
		mv->d = ft_vec(ts->centr.x - ts->sidesiz, 0, ts->centr.z + ts->sidesiz);
	}
	else
	{
		mv->a = ft_vec(ts->centr.x + ts->sidesiz, ts->centr.y + ts->sidesiz, 0);
		mv->b = ft_vec(ts->centr.x + ts->sidesiz, ts->centr.y - ts->sidesiz, 0);
		mv->c = ft_vec(ts->centr.x - ts->sidesiz, ts->centr.y - ts->sidesiz, 0);
		mv->d = ft_vec(ts->centr.x - ts->sidesiz, ts->centr.y + ts->sidesiz, 0);
	}
}

void	ft_init_square(t_square *ts)
{
	t_multivec	mv;

	set_four_vertex(&mv, ts);
	ts->tr_a.first = mv.a;
	ts->tr_a.second = mv.b;
	ts->tr_a.third = mv.c;
	ts->tr_a.rgb = ts->rgb;
	ts->tr_b.first = mv.a;
	ts->tr_b.second = mv.c;
	ts->tr_b.third = mv.d;
	ts->tr_b.rgb = ts->rgb;
	ft_init_triangle(&ts->tr_a);
	ft_init_triangle(&ts->tr_b);
}

double	get_distance_to_square(t_vec v_w, t_map *m, t_square *ts)
{
	double	t;
	double	t1;
	double	t2;

	t1 = get_distance_to_triangle(v_w, m, &ts->tr_a);
	t2 = get_distance_to_triangle(v_w, m, &ts->tr_b);
	if (t1 > 0 && t2 > 0)
		t = fmin(t1, t2);
	else
		t = fmax(t1, t2);
	return (t);
}

t_color	get_color_by_rt_square(t_map *m, t_square *ts)
{
	return (get_color_by_rt_plane(m, &ts->tr_a.plane));
}
