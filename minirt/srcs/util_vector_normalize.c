#include	"main.h"

// Normalize (length of the vec)
double	ft_vecnorm(t_vec v)
{
	double	ret;

	ret = v.x * v.x;
	ret += v.y * v.y;
	ret += v.z * v.z;
	return (sqrt(ret));
}

// Normalize square (norm is the length of the vec)
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
