#include	"main.h"

double	get_distance_to_sphere(t_vec v_w, t_vec v_cam, t_sphere *ts)
{
	t_calcvals	cv;
	t_vec		v_center_cam;

	cv.v_de = ft_vecsub(v_w, v_cam);
	v_center_cam = ft_vecsub(v_cam, ts->center);
	cv.A = ft_vecnormsq(cv.v_de);
	cv.B = 2 * ft_vecinnerprod(cv.v_de, v_center_cam);
	cv.C = ft_vecnormsq(v_center_cam) - ts->diameter * ts->diameter;
	cv.D = cv.B * cv.B - 4 * cv.A * cv.C;
	cv.t = calc_t(cv.A, cv.B, cv.D);
	return (cv.t);
}

// (2) calc diffuse reflection (kakusan hansya kou)
double	calc_sphere_diffuse_reflection(
	t_map *m, t_color *color, t_vec v_tpos, int i, t_sphere *ts)
{
	t_vec	v_lightDir;
	t_vec	v_sphereN;
	double	naiseki;
	double	nlDot;

	v_lightDir = ft_vecnormalize(ft_vecsub(m->lit[i].pos, v_tpos));
	v_sphereN = ft_vecnormalize(ft_vecsub(v_tpos, ts->center));
	naiseki = ft_vecinnerprod(v_sphereN, v_lightDir);
	if (naiseki < 0)
		naiseki = 0;
	nlDot = adjust_range(naiseki,
			(t_minmax){.min = 0, .max = 1}, (t_minmax){.min = 0, .max = 255});
	color->r += m->kDif.r * m->lit[i].itsty * m->lit[i].rgb.r * nlDot * ts->rgb.r;
	color->g += m->kDif.g * m->lit[i].itsty * m->lit[i].rgb.g * nlDot * ts->rgb.g;
	color->b += m->kDif.b * m->lit[i].itsty * m->lit[i].rgb.b * nlDot * ts->rgb.b;
	return (naiseki);
}

// (3) calc specular reflection (kyomen hansya kou)
void	calc_specular_reflection(t_map *m, t_color *color, int i,
	t_sphere *ts, t_curr_cam_vecs cv)
{
	t_vec	v_sphereN;
	t_vec	v_lightDir;
	double	naiseki;
	t_vec	refDir;
	t_vec	invEyeDir;
	double	vrDot;
	double	vrDotPow;

	v_sphereN = ft_vecnormalize(ft_vecsub(cv.v_tpos, ts->center));
	v_lightDir = ft_vecnormalize(ft_vecsub(m->lit[i].pos, cv.v_tpos));
	naiseki = ft_vecinnerprod(v_sphereN, v_lightDir);
	refDir = ft_vecsub(ft_vecmult(v_sphereN, 2 * naiseki), v_lightDir);
	invEyeDir = ft_vecnormalize(ft_vecmult(cv.v_de, -1));
	vrDot = ft_vecinnerprod(invEyeDir, refDir);
	if (vrDot < 0)
		vrDot = 0;
	vrDotPow = adjust_range(pow(vrDot, m->shininess),
		(t_minmax){.min = 0, .max = 1}, (t_minmax){.min = 0, .max = 255});
	color->r += m->kSpe.r * m->lit[i].itsty * m->lit[i].rgb.r * vrDotPow * ts->rgb.r;
	color->g += m->kSpe.g * m->lit[i].itsty * m->lit[i].rgb.g * vrDotPow * ts->rgb.g;
	color->b += m->kSpe.b * m->lit[i].itsty * m->lit[i].rgb.b * vrDotPow * ts->rgb.b;
}

//tpos	across point of eyevec and sphere surface(pi)
t_color	get_color_by_rt_sphere(t_curr_cam_vecs cv, t_map *m, t_sphere *ts)
{
	t_color	color;
	int		i;
	double	hit_t;
	double	naiseki;

	//(1) ambient light (kankyo kou)
	set_color(&color,
		m->kAmb.r * m->ambItsty * ts->rgb.r,
		m->kAmb.g * m->ambItsty * ts->rgb.g,
		m->kAmb.b * m->ambItsty * ts->rgb.b);
	i = 0;
	while (i < m->lit_cnt)
	{
		get_minimum_distance_to_obj(m->lit[i].pos, cv.v_tpos, m, &hit_t);
		if (hit_t != -1)
		{
			i++;
			continue ;
		}
		naiseki = calc_sphere_diffuse_reflection(m, &color, cv.v_tpos, i, ts);
		if (naiseki > 0)
			calc_specular_reflection(m, &color, i, ts, cv);
		i++;
	}
	return (set_rgb_inrange(color));
}

void	print_sphere(t_sphere *ts)
{
	printf("Sphere  : ");
	ft_vecprint(&ts->center);
	printf(" (r:%.2f) / ", ts->diameter);
	ft_colorprint(&ts->rgb);
	printf("\n");
}
