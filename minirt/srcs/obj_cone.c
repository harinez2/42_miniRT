#include	"main.h"

double	get_distance_to_cone(t_vec v_w, t_map *m, t_cone *tc)
{
	t_calc_crossing	cv;
	t_multdouble	md1;
	t_multdouble	md2;
	double			l;
	t_vec			v_tpos;

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
	{
		v_tpos = ft_vecadd(m->curr_cam.pos, ft_vecmult(cv.v_de, cv.t));
		t_vec v_po_p = ft_vecsub(v_tpos, tc->vertex);
		double v_po_p_len = ft_vecnorm(v_po_p);
		if (ft_vecnorm(tc->normal) / cos(ft_degree_to_rad(tc->theta)) < v_po_p_len)
			return (-1);
	}
	return (cv.t);
}

//(1) ambient light (kankyo kou)
void	calc_cone_ambient_reflection(
	t_map *m, t_color *color, t_cone *tc)
{
	set_color(color,
		m->kAmb.r * m->ambItsty * tc->rgb.r,
		m->kAmb.g * m->ambItsty * tc->rgb.g,
		m->kAmb.b * m->ambItsty * tc->rgb.b);
}

// (2) calc diffuse reflection (kakusan hansya kou)
double	calc_cone_diffuse_reflection(
	t_map *m, t_color *color, int i, t_cone *tc)
{
	t_vec	v_lightDir;
	t_vec	v_n;
	double	naiseki;
	double	nlDot;

	v_lightDir = ft_vecnormalize(ft_vecsub(m->lit[i].pos, m->camdir.v_tpos));
	v_n.x = 2 * (m->camdir.v_tpos.x - tc->normal.x);
	v_n.y = 0;
	v_n.z = 2 * (m->camdir.v_tpos.z - tc->normal.z);
	naiseki = ft_vecinnerprod(ft_vecnormalize(v_n), v_lightDir);
	if (naiseki < 0)
		naiseki = 0;
	nlDot = adjust_range(naiseki,
			(t_minmax){.min = 0, .max = 1}, (t_minmax){.min = 0, .max = 255});
	color->r += m->kDif.r * m->lit[i].itsty * m->lit[i].rgb.r
		* nlDot * tc->rgb.r;
	color->g += m->kDif.g * m->lit[i].itsty * m->lit[i].rgb.g
		* nlDot * tc->rgb.g;
	color->b += m->kDif.b * m->lit[i].itsty * m->lit[i].rgb.b
		* nlDot * tc->rgb.b;
	return (naiseki);
}

// (3) calc specular reflection (kyomen hansya kou)
void	calc_cone_reflection(
	t_map *m, t_color *color, int i, t_cone *tc)
{
	t_calc_light	cl;

	cl.v_lightDir = ft_vecnormalize(ft_vecsub(m->lit[i].pos, m->camdir.v_tpos));
	cl.v_n.x = 2 * (m->camdir.v_tpos.x - tc->normal.x);
	cl.v_n.y = 0;
	cl.v_n.z = 2 * (m->camdir.v_tpos.z - tc->normal.z);
	cl.naiseki = ft_vecinnerprod(ft_vecnormalize(cl.v_n), cl.v_lightDir);
	cl.refDir = ft_vecnormalize(ft_vecsub(ft_vecmult(
					ft_vecnormalize(cl.v_n), 2 * cl.naiseki), cl.v_lightDir));
	cl.invEyeDir = ft_vecnormalize(ft_vecmult(m->camdir.v_de, -1));
	cl.vrDot = ft_vecinnerprod(cl.invEyeDir, cl.refDir);
	if (cl.vrDot < 0)
		cl.vrDot = 0;
	cl.vrDotPow = adjust_range(pow(cl.vrDot, m->shininess),
			(t_minmax){.min = 0, .max = 1}, (t_minmax){.min = 0, .max = 255});
	color->r += m->kSpe.r * m->lit[i].itsty * m->lit[i].rgb.r
		* cl.vrDotPow * tc->rgb.r;
	color->g += m->kSpe.g * m->lit[i].itsty * m->lit[i].rgb.g
		* cl.vrDotPow * tc->rgb.g;
	color->b += m->kSpe.b * m->lit[i].itsty * m->lit[i].rgb.b
		* cl.vrDotPow * tc->rgb.b;
}

// tpos			：cross point (pi) of the v_cam and the surface of the cylinder
// v_lightDir	: vector of incidence (l) (nyuusha bector)
// v_n			: normal vector (n) (housen vector)
t_color	get_color_by_rt_cone(t_map *m, t_cone *tc)
{
	t_color	color;
	int		i;
	double	hit_t;
	double	naiseki;

	calc_cone_ambient_reflection(m, &color, tc);
	i = 0;
	while (i < m->lit_cnt)
	{
		get_minimum_distance_to_obj(m->lit[i].pos, m, &hit_t);
		if (hit_t != -1)
		{
			i++;
			continue ;
		}
		naiseki = calc_cone_diffuse_reflection(m, &color, i, tc);
		if (naiseki > 0)
			calc_cone_reflection(m, &color, i, tc);
		i++;
	}
	return (set_rgb_inrange(color));
}
