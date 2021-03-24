#include	"main.h"

/* Inner product
*/
double	ft_vecinnerprod(t_vec v, t_vec w)
{
	double	ret;

	ret = v.x * w.x;
	ret += v.y * w.y;
	ret += v.z * w.z;
	return (ret);
}

t_vec	ft_veccrossprod(t_vec v, t_vec w)
{
	t_vec	ret;

	ret.x = v.y * w.z - v.z * w.y;
	ret.y = v.z * w.x - v.x * w.z;
	ret.z = v.x * w.y - v.y * w.x;
	return (ret);
}

double ft_veccrossprod_sign(t_vec v1, t_vec v2, t_vec v3)
{
    return ((v1.x - v3.x) * (v2.y - v3.y) - (v2.x - v3.x) * (v1.y - v3.y));
}

/* Norm (length of the vec)
*/
double	ft_vecnorm(t_vec v)
{
	double	ret;

	ret = v.x * v.x;
	ret += v.y * v.y;
	ret += v.z * v.z;
	return (sqrt(ret));
}

/* Norm square (norm is the length of the vec)
*/
double	ft_vecnormsq(t_vec v)
{
	double	ret;

	ret = v.x * v.x;
	ret += v.y * v.y;
	ret += v.z * v.z;
	return (ret);
}

t_vec	ft_vecnormalize(t_vec v)
{
	return (ft_vecdiv(v, ft_vecnorm(v)));
}

void	ft_vecprint(t_vec *v)
{
	printf("%.2f, %.2f, %.2f", v->x, v->y, v->z);
}