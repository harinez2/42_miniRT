#include	"main.h"

static double	check_cone_length(t_map *m, t_cone *tc, t_calc_crossing	cv)
{
	t_vec		v_tpos;
	t_vec		v_po_p;
	double		v_po_p_len;
	
	v_tpos = ft_vecadd(m->curr_cam.pos, ft_vecmult(cv.v_de, cv.t));
	v_po_p = ft_vecsub(v_tpos, tc->vertex);
	v_po_p_len = ft_vecnorm(v_po_p);
	if (ft_vecnorm(tc->normal) / cos(ft_degree_to_rad(tc->theta)) < v_po_p_len)
		return (-1);
	return (cv.t);
}

double	get_distance_to_cone(t_vec v_w, t_map *m, t_cone *tc)
{
	t_calc_crossing	cv;
	t_multdouble	md1;
	t_multdouble	md2;
	double			l;

	cv.v_de = ft_vecsub(v_w, m->curr_cam.pos);
	md1.a = m->curr_cam.pos.x - tc->vertex.x;
	md1.b = m->curr_cam.pos.y - tc->vertex.y;
	md1.c = m->curr_cam.pos.z - tc->vertex.z;
	l = sqrt(tc->normal.x * tc->normal.x + tc->normal.y * tc->normal.y
		+ tc->normal.z * tc->normal.z) * cos(ft_degree_to_rad(tc->theta));
	md2.a = tc->normal.x * tc->normal.x / (l * l) - 1;
	md2.b = tc->normal.y * tc->normal.y / (l * l) - 1;
	md2.c = tc->normal.z * tc->normal.z / (l * l) - 1;
	cv.A = md2.a * cv.v_de.x * cv.v_de.x + md2.b * cv.v_de.y * cv.v_de.y
		+ md2.c * cv.v_de.z * cv.v_de.z;
	cv.B = 2 * (md2.a * md1.a * cv.v_de.x + md2.b * md1.b * cv.v_de.y + md2.c * md1.c * cv.v_de.z);
	cv.C = md2.a * md1.a * md1.a + md2.b * md1.b * md1.b + md2.c * md1.c * md1.c;
	cv.D = cv.B * cv.B - 4 * cv.A * cv.C;
	cv.t = calc_t(cv.A, cv.B, cv.D);
	if (cv.t > 0)
		return(check_cone_length(m, tc, cv));
	return (cv.t);
}
