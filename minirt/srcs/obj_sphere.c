#include	"main.h"

double	get_nearest_sphere(t_vec v_w, t_vec v_eye, t_sphere *ts)
{
	t_vec	v_de;
	t_vec	v_tmp;
	double	t;
	double	A;
	double	B;
	double	C;
	double	D;
	double	t1;
	double	t2;

	v_de = ft_vecsub(v_w, v_eye);
	v_tmp = ft_vecsub(v_eye, ts->center);
	A = ft_vecnormsq(v_de);
	B = 2 * ft_vecinnerprod(v_de, v_tmp);
	C = ft_vecnormsq(v_tmp) - ts->diameter * ts->diameter;
	D = B * B - 4 * A * C;
	t = -1;
	if (D == 0)
		t = -B / (2 * A);
	else if (D > 0)
	{
		t1 = (-B - sqrt(D)) / (2 * A);
		t2 = (-B + sqrt(D)) / (2 * A);
		if (t1 > 0 && t2 > 0)
			t = fmin(t1, t2);
		else
			t = fmax(t1, t2);
	}
	return (t);
}

// (2) calc diffuse reflection (kakusan hansya kou)
double	calc_sphere_diffuse_reflection(
	t_map *m, t_color *color, t_vec v_tpos, int i, t_sphere *ts)
{
	t_vec	v_lightDir;
	t_vec	v_sphereN;
	double	naiseki;
	double	nlDot;

	v_lightDir = ft_vecnormalize(ft_vecsub(m->v_light[i], v_tpos));
	v_sphereN = ft_vecnormalize(ft_vecsub(v_tpos, ts->center));
	naiseki = ft_vecinnerprod(v_sphereN, v_lightDir);
	if (naiseki < 0)
		naiseki = 0;
	nlDot = ft_map(naiseki, 0, 1, 0, 255);
	color->r += m->kDif.r * m->litItsty[i] * m->light_rgb[i].r * nlDot * ts->rgb.r;
	color->g += m->kDif.g * m->litItsty[i] * m->light_rgb[i].g * nlDot * ts->rgb.g;
	color->b += m->kDif.b * m->litItsty[i] * m->light_rgb[i].b * nlDot * ts->rgb.b;
	return (naiseki);
}

// (3) calc specular reflection (kyomen hansya kou)
void	calc_specular_reflection(t_map *m, t_color *color, t_vec v_tpos, int i,
	t_sphere *ts, t_vec v_de)
{
	t_vec	v_sphereN;
	t_vec	v_lightDir;
	double	naiseki;
	t_vec	refDir;
	t_vec	invEyeDir;
	double	vrDot;
	double	vrDotPow;

	v_sphereN = ft_vecnormalize(ft_vecsub(v_tpos, ts->center));
	v_lightDir = ft_vecnormalize(ft_vecsub(m->v_light[i], v_tpos));
	naiseki = ft_vecinnerprod(v_sphereN, v_lightDir);
	refDir = ft_vecsub(ft_vecmult(v_sphereN, 2 * naiseki), v_lightDir);
	invEyeDir = ft_vecnormalize(ft_vecmult(v_de, -1));
	vrDot = ft_vecinnerprod(invEyeDir, refDir);
	if (vrDot < 0)
		vrDot = 0;
	vrDotPow = ft_map(pow(vrDot, m->shininess), 0, 1, 0, 255);
	color->r += m->kSpe.r * m->litItsty[i] * m->light_rgb[i].r * vrDotPow * ts->rgb.r;
	color->g += m->kSpe.g * m->litItsty[i] * m->light_rgb[i].g * vrDotPow * ts->rgb.g;
	color->b += m->kSpe.b * m->litItsty[i] * m->light_rgb[i].b * vrDotPow * ts->rgb.b;
}

//tpos	across point of eyevec and sphere surface(pi)
t_color	ray_trace_sphere(t_vec v_w, t_map *m, t_sphere *ts, double t)
{
	t_color	color;
	int		i;
	t_vec	v_de;
	t_vec	v_tpos;
	double	hit_t;
	double	naiseki;

	//(1) ambient light (kankyo kou)
	set_color(&color,
		m->kAmb.r * m->ambItsty * ts->rgb.r,
		m->kAmb.g * m->ambItsty * ts->rgb.g,
		m->kAmb.b * m->ambItsty * ts->rgb.b);
	v_de = ft_vecsub(v_w, m->curr_cam.pos);
	v_tpos = ft_vecadd(m->curr_cam.pos, ft_vecmult(v_de, t));
	i = 0;
	while (i < m->light_count)
	{
		get_minimum_t_for_shadow(m->v_light[i], v_tpos, m, &hit_t);
		if (hit_t != -1)
		{
			i++;
			continue ;
		}
		naiseki = calc_sphere_diffuse_reflection(m, &color, v_tpos, i, ts);
		if (naiseki > 0)
			calc_specular_reflection(m, &color, v_tpos, i, ts, v_de);
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
