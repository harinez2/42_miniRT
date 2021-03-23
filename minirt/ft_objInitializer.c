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

void    ft_initSquare(t_square *ts)
{
    if (ts->orientation.x != 0)
    {

    }
    else if (ts->orientation.y != 0)
    {
        t_vec a = ft_vec(
            ts->center.x + ts->sidesize, 0, ts->center.z + ts->sidesize);
        t_vec b = ft_vec(
            ts->center.x + ts->sidesize, 0, ts->center.z - ts->sidesize);
        t_vec c = ft_vec(
            ts->center.x - ts->sidesize, 0, ts->center.z - ts->sidesize);
        t_vec d = ft_vec(
            ts->center.x - ts->sidesize, 0, ts->center.z + ts->sidesize);
        ts->tr_a.first = a;
        ts->tr_a.second = b;
        ts->tr_a.third = c;
        ts->tr_b.first = a;
        ts->tr_b.second = c;
        ts->tr_b.third = d;
        ft_initTriangle(&ts->tr_a);
        ft_initTriangle(&ts->tr_b);
    }
    else
    {

    }
}