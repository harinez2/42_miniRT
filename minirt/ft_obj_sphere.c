#include	"main.h"

double	get_nearest_sphere(t_vec v_w, t_vec v_eye, t_sphere *ts)
{
	t_vec	v_de;
	t_vec	v_tmp;
	double	t;

	v_de = ft_vecsub(v_w, v_eye);
	v_tmp = ft_vecsub(v_eye, ts->center);
	double A = ft_vecnormsq(v_de);
	double B = 2 * ft_vecinnerprod(v_de, v_tmp);
	double C = ft_vecnormsq(v_tmp) - ts->diameter * ts->diameter;
	double D = B * B - 4 * A * C;

	t = -1;
	if (D == 0)
		t = -B / (2 * A);
	else if (D > 0)
	{
		double t1 = (-B - sqrt(D)) / (2 * A);
		double t2 = (-B + sqrt(D)) / (2 * A);
		t = t1 > 0 && t2 > 0 ? fmin(t1, t2) : fmax(t1, t2);
	}
	return (t);
}

t_color ray_trace_sphere(t_vec v_w, t_map *m, t_sphere *ts, double t)
{
	t_color color;
	int		i;

	//(1) ambient light 環境光
	set_color(&color, 
		m->kAmb.r * m->ambItsty * ts->rgb.r,
		m->kAmb.g * m->ambItsty * ts->rgb.g,
		m->kAmb.b * m->ambItsty * ts->rgb.b);

	t_vec v_de = ft_vecsub(v_w, m->v_ceye);
	t_vec v_tpos = ft_vecadd(m->v_ceye, ft_vecmult(v_de, t));//tpos：視線と球上の交点(pi)
	i = 0;
	while (i < m->light_count)
	{
		//影の判定
		double		hit_t;
		get_minimum_t(m->v_light[i], v_tpos, m, &hit_t);
		if (hit_t != -1)
		{
			i++;
			continue;
		}
		
		//(2) diffuse reflection 拡散反射光
		t_vec v_lightDir = ft_vecnormalize(ft_vecsub(m->v_light[i], v_tpos));//入射ベクトル(l)
		t_vec v_sphereN = ft_vecnormalize(ft_vecsub(v_tpos, ts->center));//法線ベクトル(n)
		double naiseki = ft_vecinnerprod(v_sphereN, v_lightDir);
		if (naiseki < 0)
			naiseki = 0;
		double nlDot = ft_map(naiseki, 0, 1, 0, 255);
		color.r += m->kDif.r * m->lightItsty[i] * m->light_rgb[i].r * nlDot * ts->rgb.r;
		color.g += m->kDif.g * m->lightItsty[i] * m->light_rgb[i].g * nlDot * ts->rgb.g;
		color.b += m->kDif.b * m->lightItsty[i] * m->light_rgb[i].b * nlDot * ts->rgb.b;

		//(3) specular reflection 鏡面反射光
		if (naiseki > 0)
		{
			t_vec v_lightDir = ft_vecnormalize(ft_vecsub(m->v_light[i], v_tpos));//入射ベクトル(l)
			t_vec refDir = ft_vecsub(ft_vecmult(v_sphereN, 2 * naiseki), v_lightDir); 
			t_vec invEyeDir = ft_vecnormalize(ft_vecmult(v_de, -1));
			double vrDot = ft_vecinnerprod(invEyeDir, refDir);
			if (vrDot < 0)
				vrDot = 0;
			double vrDotPow = ft_map(pow(vrDot, m->shininess), 0, 1, 0, 255);
			color.r += m->kSpe.r * m->lightItsty[i] * m->light_rgb[i].r * vrDotPow * ts->rgb.r;
			color.g += m->kSpe.g * m->lightItsty[i] * m->light_rgb[i].g * vrDotPow * ts->rgb.g;
			color.b += m->kSpe.b * m->lightItsty[i] * m->light_rgb[i].b * vrDotPow * ts->rgb.b;
		}
		i++;
	}
	return (set_rgb_inrange(color));
}

void	print_sphere(t_sphere *ts)
{
	printf("Sphere: ");
	ft_vecprint(&ts->center);
	printf(" (r:%.2f) / ", ts->diameter);
	ft_colorprint(&ts->rgb);
	printf("\n");
}