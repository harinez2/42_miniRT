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
	printf("[vector] (%f, %f, %f)\n", v->x, v->y, v->z);
}
