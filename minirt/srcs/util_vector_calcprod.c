#include	"main.h"

// Inner product
double	ft_vecinnerprod(t_vec v, t_vec w)
{
	double	ret;

	ret = v.x * w.x;
	ret += v.y * w.y;
	ret += v.z * w.z;
	return (ret);
}

// Cross product
t_vec	ft_veccrossprod(t_vec v, t_vec w)
{
	t_vec	ret;

	ret.x = v.y * w.z - v.z * w.y;
	ret.y = v.z * w.x - v.x * w.z;
	ret.z = v.x * w.y - v.y * w.x;
	return (ret);
}

double	ft_veccrossprod_sign(t_vec v1, t_vec v2, t_vec v3)
{
	return ((v1.x - v3.x) * (v2.y - v3.y) - (v2.x - v3.x) * (v1.y - v3.y));
}
