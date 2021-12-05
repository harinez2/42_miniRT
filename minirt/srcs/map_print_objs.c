#include	"main.h"

void	print_cylinder(t_cylinder *tc)
{
	printf("Cylinder: ");
	ft_vecprint(&tc->center);
	printf(" / ");
	ft_vecprint(&tc->orientation);
	printf(" (r: %.2f h: %.2f) / ", tc->diameter, tc->height);
	ft_colorprint(&tc->rgb);
	printf("\n");
}

void	print_plane(t_plane *tp)
{
	printf("Plane   : ");
	ft_vecprint(&tp->normal);
	printf(" / ");
	ft_vecprint(&tp->position);
	printf(" / ");
	ft_colorprint(&tp->rgb);
	printf("\n");
}

void	print_sphere(t_sphere *ts)
{
	printf("Sphere  : ");
	ft_vecprint(&ts->center);
	printf(" (r:%.2f) / ", ts->diameter);
	ft_colorprint(&ts->rgb);
	printf("\n");
}

void	print_square(t_square *ts)
{
	printf("Square  : ");
	ft_vecprint(&ts->centr);
	printf(" / ");
	ft_vecprint(&ts->orientation);
	printf(" (ss:%.2f) / ", ts->sidesiz);
	ft_colorprint(&ts->rgb);
	printf("\n");
	printf("        ");
	print_triangle(&ts->tr_a);
	printf("        ");
	print_triangle(&ts->tr_b);
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
	printf("          ");
	print_plane(&tt->plane);
}
