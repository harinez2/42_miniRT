#include	"main.h"

t_vec	ft_vecinit(double x, double y, double z)
{
	t_vec	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

void	ft_vecset(t_vec *v, double x, double y, double z)
{
	v->x = x;
	v->y = y;
	v->z = z;
}

t_vec	ft_vec(double x, double y, double z)
{
	t_vec	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

void	ft_vecprint(t_vec *v)
{
	printf("%.2f, %.2f, %.2f", v->x, v->y, v->z);
}

void	ft_vecprint_with_name(char *vecname, t_vec *v)
{
	printf("%s : %.2f, %.2f, %.2f\n", vecname, v->x, v->y, v->z);
}
