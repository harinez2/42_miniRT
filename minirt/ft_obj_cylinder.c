#include	"main.h"

double	get_nearest_cylinder(t_vec v_w, t_vec v_eye, t_cylinder *tc)
{
	t_vec	v_de;
	double	mx;
	double	mz;
	double	t;

	v_de = ft_vecsub(v_w, v_eye);
	mx = v_eye.x - tc->center.x;
	mz = v_eye.z - tc->center.z;
	double A = v_de.x * v_de.x + v_de.z * v_de.z;
	double B = 2 * (v_de.x * mx + v_de.z * mz);
	double C = mx * mx + mz * mz - tc->diameter * tc->diameter;
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
	if (t > 0)
	{
		t_vec v_tpos = ft_vecadd(v_eye, ft_vecmult(v_de, t));//tpos：視線と球上の交点(pi)
		double diff = v_tpos.y - tc->center.y;
		if (diff < 0)
			diff *= -1;
		if (diff > tc->height / 2)
			t = -1;
	}
	return (t);
}

t_color	ray_trace_cylinder(t_vec v_w, t_map *m, t_cylinder *tc, double t)
{
	t_color color;
	int		i;

	//(1) ambient light 環境光
	set_color(&color,
		m->kAmb.r * m->ambItsty * tc->rgb.r,
		m->kAmb.g * m->ambItsty * tc->rgb.g,
		m->kAmb.b * m->ambItsty * tc->rgb.b);

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
		t_vec v_n;//法線ベクトル(n)
		v_n.x = 2 * (v_tpos.x - tc->center.x);
		v_n.y = 0;
		v_n.z = 2 * (v_tpos.z - tc->center.z);
		double naiseki = ft_vecinnerprod(ft_vecnormalize(v_n), v_lightDir);
		if (naiseki < 0)
			naiseki = 0;
		double nlDot = ft_map(naiseki, 0, 1, 0, 255);
		color.r += m->kDif.r * m->lightItsty[i] * m->light_rgb[i].r * nlDot * tc->rgb.r;
		color.g += m->kDif.g * m->lightItsty[i] * m->light_rgb[i].g * nlDot * tc->rgb.g;
		color.b += m->kDif.b * m->lightItsty[i] * m->light_rgb[i].b * nlDot * tc->rgb.b;

		//(3) specular reflection 鏡面反射光
		if (naiseki > 0)
		{
			t_vec refDir = ft_vecnormalize(ft_vecsub(ft_vecmult(ft_vecnormalize(v_n), 2 * naiseki), v_lightDir)); 
			t_vec invEyeDir = ft_vecnormalize(ft_vecmult(v_de, -1));
			double vrDot = ft_vecinnerprod(invEyeDir, refDir);
			if (vrDot < 0)
				vrDot = 0;
			double vrDotPow = ft_map(pow(vrDot, m->shininess), 0, 1, 0, 255);
			color.r += m->kSpe.r * m->lightItsty[i] * m->light_rgb[i].r * vrDotPow * tc->rgb.r;
			color.g += m->kSpe.g * m->lightItsty[i] * m->light_rgb[i].g * vrDotPow * tc->rgb.g;
			color.b += m->kSpe.b * m->lightItsty[i] * m->light_rgb[i].b * vrDotPow * tc->rgb.b;
		}
		i++;
	}
	return (set_rgb_inrange(color));
}

void	print_cylinder(t_cylinder *tc)
{
	printf("Cylinder: ");
	ft_vecprint(&tc->center);
	printf(" / ");
	ft_vecprint(&tc->orientation);
	printf(" (r: %.2f h: %.2f) / ", tc->diameter, tc->height);
	ft_colorprint(&tc->rgb);
	printf("\n");
}