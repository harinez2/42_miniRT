#include	"main.h"

double	get_distance_to_plane(t_vec v_w, t_vec v_eye, t_plane *tp)
{
	double	t;
	t_vec	v_de;
	double	a;
	double	b;
	double	c;

	if (ft_vecinnerprod(v_w, tp->normal) != 0)
	{
		v_de = ft_vecsub(v_w, v_eye);
		a = ft_vecinnerprod(tp->position, tp->normal);
		b = ft_vecinnerprod(v_eye, tp->normal);
		c = ft_vecinnerprod(v_de, tp->normal);
		t = (a - b) / c;
		if (t > 0)
			return (t);
	}
	return (-1);
}

t_color	ray_trace_plane(t_vec v_w, t_map *m, t_plane *tp, double t)
{
	t_color	color;
	int		i;
	t_vec	v_de;
	t_vec	v_tpos;
	double	hit_t;
	t_vec	v_lightDir;
	double	naiseki;
	double	nlDot;
	t_vec	refDir;
	t_vec	invEyeDir;
	double	vrDot;
	double	vrDotPow;

	//(1) ambient light 環境光
	set_color(&color,
		m->kAmb.r * m->ambItsty * tp->rgb.r,
		m->kAmb.g * m->ambItsty * tp->rgb.g,
		m->kAmb.b * m->ambItsty * tp->rgb.b);
	v_de = ft_vecsub(v_w, m->curr_cam.pos);
	v_tpos = ft_vecadd(m->curr_cam.pos, ft_vecmult(v_de, t));
	i = 0;
	while (i < m->lit_cnt)
	{
		get_minimum_distance_to_obj(m->lit[i].pos, v_tpos, m, &hit_t);
		if (hit_t != -1)
		{
			i++;
			continue ;
		}

		//(2) diffuse reflection 拡散反射光
		v_lightDir = ft_vecnormalize(ft_vecsub(m->lit[i].pos, v_tpos));
		naiseki = ft_vecinnerprod(ft_vecnormalize(tp->normal), v_lightDir);
		if (naiseki < 0)
			naiseki = 0;
		nlDot = adjust_range(naiseki,
			(t_minmax){.min = 0, .max = 1}, (t_minmax){.min = 0, .max = 255});
		color.r += m->kDif.r * m->lit[i].itsty * m->lit[i].rgb.r * nlDot * tp->rgb.r;
		color.g += m->kDif.g * m->lit[i].itsty * m->lit[i].rgb.g * nlDot * tp->rgb.g;
		color.b += m->kDif.b * m->lit[i].itsty * m->lit[i].rgb.b * nlDot * tp->rgb.b;

		//(3) specular reflection 鏡面反射光
		if (naiseki > 0)
		{
			refDir = ft_vecsub(ft_vecmult(tp->normal, 2 * naiseki), v_lightDir);
			invEyeDir = ft_vecnormalize(ft_vecmult(v_de, -1));
			vrDot = ft_vecinnerprod(invEyeDir, refDir);
			if (vrDot < 0)
				vrDot = 0;
			vrDotPow = adjust_range(pow(vrDot, m->shininess),
				(t_minmax){.min = 0, .max = 1}, (t_minmax){.min = 0, .max = 255});
			color.r += m->kSpe.r * m->lit[i].itsty * m->lit[i].rgb.r * vrDotPow * tp->rgb.r;
			color.g += m->kSpe.g * m->lit[i].itsty * m->lit[i].rgb.g * vrDotPow * tp->rgb.g;
			color.b += m->kSpe.b * m->lit[i].itsty * m->lit[i].rgb.b * vrDotPow * tp->rgb.b;
		}
		i++;
	}
	return (set_rgb_inrange(color));
}

void	print_plane(t_plane *tp)
{
	printf("Plane   : ");
	ft_vecprint(&tp->normal);
	printf(" / ");
	ft_vecprint(&tp->position);
	printf(" / ");
	ft_colorprint(&tp->rgb);
	printf("\n");
}
