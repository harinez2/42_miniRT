#include	"main.h"

void	ft_init_triangle(t_triangle *tt)
{
	t_vec	n;

	n = ft_veccrossprod(ft_vecsub(tt->second, tt->first), ft_vecsub(tt->third, tt->first));
	//printf("tri vec: %.2f %.2f %.2f\n", n.x, n.y, n.z);
	tt->plane.normal = ft_vecnormalize(n);
	tt->plane.position = tt->first;//ft_vecnormalize(tt->first);
	tt->plane.rgb = tt->rgb;
}

double	get_nearest_triangle(t_vec v_w, t_vec v_eye, t_triangle *tt)
{
	double	t;

	t = get_nearest_plane(v_w, v_eye, &tt->plane);
	if (t >= 0)
	{
		t_vec v_de = ft_vecsub(v_w, v_eye);
		t_vec v_tpos = ft_vecadd(v_eye, ft_vecmult(v_de, t));//tpos：視線と面上の交点(pi)
		double a, b, c;
		if (tt->first.x == tt->second.x && tt->first.x == tt->third.x)
		{
			a = ft_veccrossprod(ft_vecsub(tt->second, tt->first), ft_vecsub(v_tpos, tt->second)).x;
			b = ft_veccrossprod(ft_vecsub(tt->third, tt->second), ft_vecsub(v_tpos, tt->third)).x;
			c = ft_veccrossprod(ft_vecsub(tt->first, tt->third), ft_vecsub(v_tpos, tt->first)).x;
		}
		else
		{
			a = ft_veccrossprod(ft_vecsub(tt->second, tt->first), ft_vecsub(v_tpos, tt->second)).y;
			b = ft_veccrossprod(ft_vecsub(tt->third, tt->second), ft_vecsub(v_tpos, tt->third)).y;
			c = ft_veccrossprod(ft_vecsub(tt->first, tt->third), ft_vecsub(v_tpos, tt->first)).y;
		}
		//printf("tr %.2f %.2f %.2f / ", v_tpos.x, v_tpos.y, v_tpos.z);
		//printf("%.2f %.2f %.2f\n", a, b, c);
		if (!((a >=0 && b >= 0 && c >= 0) || (a < 0 && b < 0 && c < 0)))
			t = -1;
	}
	return (t);
}

t_color	ray_trace_triangle(t_vec v_w, t_map *m, t_triangle *tt, double t)
{
	return (ray_trace_plane(v_w, m, &tt->plane, t));
}

void	print_triangle(t_triangle *tt)
{
	printf("Triangle: ");
	ft_vecprint(&tt->first);
	printf(" / ");
	ft_vecprint(&tt->second);
	printf(" / ");
	ft_vecprint(&tt->third);
	printf(" / ");
	ft_colorprint(&tt->rgb);
	printf("\n");

	printf("        ");
	print_plane(&tt->plane);
}
