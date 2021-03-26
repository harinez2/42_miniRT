#include	"main.h"

double	get_nearest_plane(t_vec v_w, t_vec v_eye, t_plane *tp)
{
	double	wn_dot;
	double t;

	wn_dot = ft_vecinnerprod(v_w, tp->normal);
	if (wn_dot != 0)
	{
		t_vec v_de = ft_vecsub(v_w, v_eye);
		double a = ft_vecinnerprod(tp->position, tp->normal);
		double b = ft_vecinnerprod(v_eye, tp->normal);
		double c = ft_vecinnerprod(v_de, tp->normal);
		t = (a - b) / c;
		if (t > 0)
			return (t);
	}
	return (-1);
}

t_color ray_trace_plane(t_vec v_w, t_map *m, t_plane *tp, double t)
{
	t_color color;
	int		i;

	//(1) ambient light 環境光
	set_color(&color, 
		m->kAmb.r * m->ambItsty * tp->rgb.r,
		m->kAmb.g * m->ambItsty * tp->rgb.g,
		m->kAmb.b * m->ambItsty * tp->rgb.b);

	t_vec v_de = ft_vecsub(v_w, m->v_ceye);
	t_vec v_tpos = ft_vecadd(m->v_ceye, ft_vecmult(v_de, t));
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
		t_vec v_lightDir = ft_vecnormalize(ft_vecsub(m->v_light[i], v_tpos));
		double naiseki = ft_vecinnerprod(ft_vecnormalize(tp->normal), v_lightDir);
		if (naiseki < 0)
			naiseki = 0;
		double nlDot = ft_map(naiseki, 0, 1, 0, 255);
		color.r += m->kDif.r * m->lightItsty[i] * m->light_rgb[i].r * nlDot * tp->rgb.r;
		color.g += m->kDif.g * m->lightItsty[i] * m->light_rgb[i].g * nlDot * tp->rgb.g;
		color.b += m->kDif.b * m->lightItsty[i] * m->light_rgb[i].b * nlDot * tp->rgb.b;
		
		//(3) specular reflection 鏡面反射光
		if (naiseki > 0)
		{
			t_vec refDir = ft_vecsub(ft_vecmult(tp->normal, 2 * naiseki), v_lightDir); 
			t_vec invEyeDir = ft_vecnormalize(ft_vecmult(v_de, -1));
			double vrDot = ft_vecinnerprod(invEyeDir, refDir);
			if (vrDot < 0)
				vrDot = 0;
			double vrDotPow = ft_map(pow(vrDot, m->shininess), 0, 1, 0, 255);
			color.r += m->kSpe.r * m->lightItsty[i] * m->light_rgb[i].r * vrDotPow * tp->rgb.r;
			color.g += m->kSpe.g * m->lightItsty[i] * m->light_rgb[i].g * vrDotPow * tp->rgb.g;
			color.b += m->kSpe.b * m->lightItsty[i] * m->light_rgb[i].b * vrDotPow * tp->rgb.b;
		}
		i++;
	}
	return (set_rgb_inrange(color));
}

void	print_plane(t_plane *tp)
{
	printf("Plane: ");
	ft_vecprint(&tp->normal);
	printf(" / ");
	ft_vecprint(&tp->position);
	printf(" / ");
	ft_colorprint(&tp->rgb);
	printf("\n");
}