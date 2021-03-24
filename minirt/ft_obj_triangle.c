#include	"main.h"

void    ft_initTriangle(t_triangle *tt)
{
	t_vec n = ft_veccrossprod(ft_vecsub(tt->second, tt->first), ft_vecsub(tt->third, tt->first));
	//printf("tri vec: %.2f %.2f %.2f\n", n.x, n.y, n.z);
	n = ft_vecnormalize(n);
	//printf("tri vec: %.2f %.2f %.2f\n", n.x, n.y, n.z);
    tt->plane.normal = n;

    //tt->plane.position = ft_vecnormalize(tt->first);
	tt->plane.position = tt->first;
}

double	get_nearest_triangle(t_vec v_w, t_vec v_eye, t_triangle *tt)
{
	double t;

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
	printf("%.2f, %.2f, %.2f / ", tt->first.x, tt->first.y, tt->first.z);
	printf("%.2f, %.2f, %.2f / ", tt->second.x, tt->second.y, tt->second.z);
	printf("%.2f, %.2f, %.2f / ", tt->third.x, tt->third.y, tt->third.z);
	printf("rgb:%.2f %.2f %.2f\n", tt->rgb.r, tt->rgb.g, tt->rgb.b);
	printf("        ");
	print_plane(&tt->plane);
}