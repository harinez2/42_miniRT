#include	"main.h"

// tpos：cross point (pi) of the v_cam and the surface of the cylinder
double	get_nearest_cylinder(t_vec v_w, t_vec v_cam, t_cylinder *tc)
{
	t_calcvals	cv;
	double		mx;
	double		mz;
	t_vec		v_tpos;
	double		diff;

	cv.v_de = ft_vecsub(v_w, v_cam);
	mx = v_cam.x - tc->center.x;
	mz = v_cam.z - tc->center.z;
	cv.A = cv.v_de.x * cv.v_de.x + cv.v_de.z * cv.v_de.z;
	cv.B = 2 * (cv.v_de.x * mx + cv.v_de.z * mz);
	cv.C = mx * mx + mz * mz - tc->diameter * tc->diameter;
	cv.D = cv.B * cv.B - 4 * cv.A * cv.C;
	cv.t = calc_t(cv.A, cv.B, cv.D);
	if (cv.t > 0)
	{
		v_tpos = ft_vecadd(v_cam, ft_vecmult(cv.v_de, cv.t));
		diff = v_tpos.y - tc->center.y;
		if (diff < 0)
			diff *= -1;
		if (diff > tc->height / 2)
			cv.t = -1;
	}
	return (cv.t);
}

// tpos：cross point (pi) of the v_cam and the surface of the cylinder
t_color	ray_trace_cylinder(t_vec v_w, t_map *m, t_cylinder *tc, double t)
{
	t_color color;
	int		i;
	double	hit_t;
	t_vec	v_de;
	t_vec	v_tpos;

	//(1) ambient light 環境光
	set_color(&color,
		m->kAmb.r * m->ambItsty * tc->rgb.r,
		m->kAmb.g * m->ambItsty * tc->rgb.g,
		m->kAmb.b * m->ambItsty * tc->rgb.b);
	v_de = ft_vecsub(v_w, m->curr_cam.pos);
	v_tpos = ft_vecadd(m->curr_cam.pos, ft_vecmult(v_de, t));
	i = 0;
	while (i < m->lit_cnt)
	{
		get_minimum_t_for_shadow(m->lit[i].pos, v_tpos, m, &hit_t);
		if (hit_t != -1)
		{
			i++;
			continue ;
		}
		//(2) diffuse reflection 拡散反射光
		t_vec v_lightDir = ft_vecnormalize(ft_vecsub(m->lit[i].pos, v_tpos));//入射ベクトル(l)
		t_vec v_n;//法線ベクトル(n)
		v_n.x = 2 * (v_tpos.x - tc->center.x);
		v_n.y = 0;
		v_n.z = 2 * (v_tpos.z - tc->center.z);
		double naiseki = ft_vecinnerprod(ft_vecnormalize(v_n), v_lightDir);
		if (naiseki < 0)
			naiseki = 0;
		double nlDot = adjust_range(naiseki,
			(t_minmax){.min = 0, .max = 1}, (t_minmax){.min = 0, .max = 255});
		color.r += m->kDif.r * m->lit[i].itsty * m->lit[i].rgb.r * nlDot * tc->rgb.r;
		color.g += m->kDif.g * m->lit[i].itsty * m->lit[i].rgb.g * nlDot * tc->rgb.g;
		color.b += m->kDif.b * m->lit[i].itsty * m->lit[i].rgb.b * nlDot * tc->rgb.b;
		//(3) specular reflection 鏡面反射光
		if (naiseki > 0)
		{
			t_vec refDir = ft_vecnormalize(ft_vecsub(ft_vecmult(ft_vecnormalize(v_n), 2 * naiseki), v_lightDir)); 
			t_vec invEyeDir = ft_vecnormalize(ft_vecmult(v_de, -1));
			double vrDot = ft_vecinnerprod(invEyeDir, refDir);
			if (vrDot < 0)
				vrDot = 0;
			double vrDotPow = adjust_range(pow(vrDot, m->shininess),
				(t_minmax){.min = 0, .max = 1}, (t_minmax){.min = 0, .max = 255});
			color.r += m->kSpe.r * m->lit[i].itsty * m->lit[i].rgb.r * vrDotPow * tc->rgb.r;
			color.g += m->kSpe.g * m->lit[i].itsty * m->lit[i].rgb.g * vrDotPow * tc->rgb.g;
			color.b += m->kSpe.b * m->lit[i].itsty * m->lit[i].rgb.b * vrDotPow * tc->rgb.b;
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