#include	"main.h"

double	get_distance_to_plane(t_vec v_w, t_map *m, t_plane *tp)
{
	double	t;
	t_vec	v_de;
	double	a;
	double	b;
	double	c;

	if (ft_vecinnerprod(v_w, tp->normal) != 0)
	{
		v_de = ft_vecsub(v_w, m->curr_cam.pos);
		a = ft_vecinnerprod(tp->position, tp->normal);
		b = ft_vecinnerprod(m->curr_cam.pos, tp->normal);
		c = ft_vecinnerprod(v_de, tp->normal);
		t = (a - b) / c;
		if (t > 0)
			return (t);
	}
	return (-1);
}

//(1) ambient light (kankyo kou)
void	calc_plane_ambient_reflection(
	t_map *m, t_color *color, t_plane *tp)
{
	set_color(color,
		m->kAmb.r * m->ambItsty * tp->rgb.r,
		m->kAmb.g * m->ambItsty * tp->rgb.g,
		m->kAmb.b * m->ambItsty * tp->rgb.b);
}

// (2) calc diffuse reflection (kakusan hansya kou)
double	calc_plane_diffuse_reflection(
	t_map *m, t_color *color, int i, t_plane *tp)
{
	t_vec	v_lightDir;
	double	naiseki;
	double	nlDot;

	v_lightDir = ft_vecnormalize(ft_vecsub(m->lit[i].pos, m->camdir.v_tpos));
	naiseki = ft_vecinnerprod(ft_vecnormalize(tp->normal), v_lightDir);
	if (naiseki < 0)
		naiseki = 0;
	nlDot = adjust_range(naiseki,
			(t_minmax){.min = 0, .max = 1}, (t_minmax){.min = 0, .max = 255});
	color->r += m->kDif.r * m->lit[i].itsty * m->lit[i].rgb.r
		* nlDot * tp->rgb.r;
	color->g += m->kDif.g * m->lit[i].itsty * m->lit[i].rgb.g
		* nlDot * tp->rgb.g;
	color->b += m->kDif.b * m->lit[i].itsty * m->lit[i].rgb.b
		* nlDot * tp->rgb.b;
	return (naiseki);
}

// (3) calc specular reflection (kyomen hansya kou)
void	calc_plane_specular_reflection(
	t_map *m, t_color *color, int i, t_plane *tp)
{
	t_calc_light	cl;

	cl.v_lightDir = ft_vecnormalize(ft_vecsub(m->lit[i].pos, m->camdir.v_tpos));
	cl.naiseki = ft_vecinnerprod(ft_vecnormalize(tp->normal), cl.v_lightDir);
	cl.refDir
		= ft_vecsub(ft_vecmult(tp->normal, 2 * cl.naiseki), cl.v_lightDir);
	cl.invEyeDir = ft_vecnormalize(ft_vecmult(m->camdir.v_de, -1));
	cl.vrDot = ft_vecinnerprod(cl.invEyeDir, cl.refDir);
	if (cl.vrDot < 0)
		cl.vrDot = 0;
	cl.vrDotPow = adjust_range(pow(cl.vrDot, m->shininess),
			(t_minmax){.min = 0, .max = 1}, (t_minmax){.min = 0, .max = 255});
	color->r += m->kSpe.r * m->lit[i].itsty * m->lit[i].rgb.r
		* cl.vrDotPow * tp->rgb.r;
	color->g += m->kSpe.g * m->lit[i].itsty * m->lit[i].rgb.g
		* cl.vrDotPow * tp->rgb.g;
	color->b += m->kSpe.b * m->lit[i].itsty * m->lit[i].rgb.b
		* cl.vrDotPow * tp->rgb.b;
}

t_color	get_color_by_rt_plane(t_map *m, t_plane *tp)
{
	t_color	color;
	int		i;
	double	hit_t;
	double	naiseki;

	calc_plane_ambient_reflection(m, &color, tp);
	i = 0;
	while (i < m->lit_cnt)
	{
		get_minimum_distance_to_obj(m->lit[i].pos, m, &hit_t);
		if (hit_t != -1)
		{
			i++;
			continue ;
		}
		naiseki = calc_plane_diffuse_reflection(m, &color, i, tp);
		if (naiseki > 0)
			calc_plane_specular_reflection(m, &color, i, tp);
		i++;
	}
	return (set_rgb_inrange(color));
}
