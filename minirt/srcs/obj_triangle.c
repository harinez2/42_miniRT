#include	"main.h"

void	ft_init_triangle(t_triangle *tt)
{
	t_vec	n;

	n = ft_veccrossprod(ft_vecsub(tt->second, tt->first),
			ft_vecsub(tt->third, tt->first));
	tt->plane.normal = ft_vecnormalize(n);
	tt->plane.position = tt->first;
	tt->plane.rgb = tt->rgb;
}

static void	calc_triangle_crossprod(
	t_multivec *mv, t_vec v_tpos, t_triangle *tt)
{
	mv->a = ft_veccrossprod(
			ft_vecsub(tt->second, tt->first), ft_vecsub(v_tpos, tt->second));
	mv->b = ft_veccrossprod(
			ft_vecsub(tt->third, tt->second), ft_vecsub(v_tpos, tt->third));
	mv->c = ft_veccrossprod(
			ft_vecsub(tt->first, tt->third), ft_vecsub(v_tpos, tt->first));
}

//tpos	across point of eyevec and plane surface(pi)
double	get_distance_to_triangle(t_vec v_w, t_map *m, t_triangle *tt)
{
	double		t;
	t_vec		v_de;
	t_vec		v_tpos;
	t_multivec	mv;

	t = get_distance_to_plane(v_w, m, &tt->plane);
	if (t > 0)
	{
		v_de = ft_vecsub(v_w, m->curr_cam.pos);
		v_tpos = ft_vecadd(m->curr_cam.pos, ft_vecmult(v_de, t));
		calc_triangle_crossprod(&mv, v_tpos, tt);
		if (tt->first.x == tt->second.x && tt->first.x == tt->third.x)
		{
			if (!((mv.a.x >= 0 && mv.b.x >= 0 && mv.c.x >= 0)
					|| (mv.a.x < 0 && mv.b.x < 0 && mv.c.x < 0)))
				t = -1;
		}
		else
		{
			if (!((mv.a.y >= 0 && mv.b.y >= 0 && mv.c.y >= 0)
					|| (mv.a.y < 0 && mv.b.y < 0 && mv.c.y < 0)))
				t = -1;
		}
	}
	return (t);
}

t_color	get_color_by_rt_triangle(t_map *m, t_triangle *tt)
{
	return (get_color_by_rt_plane(m, &tt->plane));
}
