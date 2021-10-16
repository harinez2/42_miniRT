#include	"main.h"

// tpos：cross point (pi) of the v_cam and the surface of the cylinder
double	get_distance_to_cylinder(t_vec v_w, t_map *m, t_cylinder *tc)
{
	t_calc_crossing	cv;
	double			mx;
	double			mz;
	t_vec			v_tpos;
	double			diff;

	cv.v_de = ft_vecsub(v_w, m->curr_cam.pos);
	mx = m->curr_cam.pos.x - tc->center.x;
	mz = m->curr_cam.pos.z - tc->center.z;
	cv.A = cv.v_de.x * cv.v_de.x + cv.v_de.z * cv.v_de.z;
	cv.B = 2 * (cv.v_de.x * mx + cv.v_de.z * mz);
	cv.C = mx * mx + mz * mz - tc->diameter * tc->diameter;
	cv.D = cv.B * cv.B - 4 * cv.A * cv.C;
	cv.t = calc_t(cv.A, cv.B, cv.D);
	if (cv.t > 0)
	{
		v_tpos = ft_vecadd(m->curr_cam.pos, ft_vecmult(cv.v_de, cv.t));
		diff = v_tpos.y - tc->center.y;
		if (diff < 0)
			diff *= -1;
		if (diff > tc->height / 2)
			cv.t = -1;
	}
	return (cv.t);
}

//(1) ambient light (kankyo kou)
void	calc_cylinder_ambient_reflection(
	t_map *m, t_color *color, t_cylinder *tc)
{
	set_ambient_reflection_color(m, color, &tc->rgb);
}

// (2) calc diffuse reflection (kakusan hansya kou)
double	calc_cylinder_diffuse_reflection(
	t_map *m, t_color *color, int i, t_cylinder *tc)
{
	t_vec	v_lightDir;
	t_vec	v_nornal;
	double	innprod_lit_n;
	t_color	add_color;

	v_lightDir = ft_vecnormalize(ft_vecsub(m->lit[i].pos, m->camdir.v_tpos));
	v_nornal.x = 2 * (m->camdir.v_tpos.x - tc->center.x);
	v_nornal.y = 0;
	v_nornal.z = 2 * (m->camdir.v_tpos.z - tc->center.z);
	innprod_lit_n = ft_vecinnerprod(ft_vecnormalize(v_nornal), v_lightDir);
	if (innprod_lit_n < 0)
		innprod_lit_n = 0;
	add_color = adjust_color_level(&tc->rgb, innprod_lit_n);
	add_diffuse_reflection_color(m, i, color, &add_color);
	return (innprod_lit_n);
}

// (3) calc specular reflection (kyomen hansya kou)
void	calc_cylinder_reflection(
	t_map *m, t_color *color, int i, t_cylinder *tc)
{
	t_calc_light	cl;

	cl.v_lightDir = ft_vecnormalize(ft_vecsub(m->lit[i].pos, m->camdir.v_tpos));
	cl.v_n.x = 2 * (m->camdir.v_tpos.x - tc->center.x);
	cl.v_n.y = 0;
	cl.v_n.z = 2 * (m->camdir.v_tpos.z - tc->center.z);
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

// tpos			：cross point (pi) of the v_cam and the surface of the object
// v_lightDir	: vector of incidence (l) (nyuusha vector)
// v_n			: normal vector (n) (housen vector)
t_color	get_color_by_rt_cylinder(t_map *m, t_cylinder *tc)
{
	t_color	color;
	int		i;
	double	hit_t;
	double	naiseki;

	calc_cylinder_ambient_reflection(m, &color, tc);
	i = 0;
	while (i < m->lit_cnt)
	{
		get_minimum_distance_to_obj(m->lit[i].pos, m, &hit_t);
		if (hit_t != -1)
		{
			i++;
			continue ;
		}
		naiseki = calc_cylinder_diffuse_reflection(m, &color, i, tc);
		if (naiseki > 0)
			calc_cylinder_reflection(m, &color, i, tc);
		i++;
	}
	return (set_rgb_inrange(color));
}
