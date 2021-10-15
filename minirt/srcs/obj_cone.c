#include	"main.h"

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

	double t = (m->camdir.v_tpos.x * tc->normal.x
		+ m->camdir.v_tpos.y * tc->normal.y
		+ m->camdir.v_tpos.z * tc->normal.z
		- tc->vertex.x * tc->normal.x
		- tc->vertex.y * tc->normal.y
		- tc->vertex.z * tc->normal.z)
		/ ( (m->camdir.v_tpos.x - tc->vertex.x) * (m->camdir.v_tpos.x - tc->vertex.x)
		  + (m->camdir.v_tpos.y - tc->vertex.y) * (m->camdir.v_tpos.y - tc->vertex.y)
		  + (m->camdir.v_tpos.z - tc->vertex.z) * (m->camdir.v_tpos.z - tc->vertex.z)
		);
	v_n.x = t * m->camdir.v_tpos.x - t * tc->vertex.x - tc->normal.x;
	v_n.y = t * m->camdir.v_tpos.y - t * tc->vertex.y - tc->normal.y;
	v_n.z = t * m->camdir.v_tpos.z - t * tc->vertex.z - tc->normal.z;
	// double			l;
	// double mm;
	// l = sqrt(tc->normal.x * tc->normal.x + tc->normal.y * tc->normal.y
	// 	+ tc->normal.z * tc->normal.z) * cos(ft_degree_to_rad(tc->theta));
	// mm = sqrt(m->camdir.v_tpos.x * m->camdir.v_tpos.x
	// 		- 2 * m->camdir.v_tpos.x * tc->vertex.x
	// 		+ tc->vertex.x * tc->vertex.x
	// 		+ m->camdir.v_tpos.y * m->camdir.v_tpos.y
	// 		- 2 * m->camdir.v_tpos.y * tc->vertex.y
	// 		+ tc->vertex.y * tc->vertex.y
	// 		+ m->camdir.v_tpos.z * m->camdir.v_tpos.z
	// 		- 2 * m->camdir.v_tpos.z * tc->vertex.z
	// 		+ tc->vertex.z * tc->vertex.z
	// 	);
	// v_n.x = tc->normal.x - l * (m->camdir.v_tpos.x - tc->vertex.x) / mm;
	// v_n.y = tc->normal.y - l * (m->camdir.v_tpos.y - tc->vertex.y) / mm;
	// v_n.z = tc->normal.z - l * (m->camdir.v_tpos.z - tc->vertex.z) / mm;
	// if (rand() % 100 == 0)
	// {
	// 	t_vec v = ft_vecnormalize(v_n);
	// 	ft_vecprint(&v);
	// 	printf("\n");
	// }
	naiseki = ft_vecinnerprod(ft_vecnormalize(v_n), v_lightDir);
	// printf("%f\n", naiseki);
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
	(void)m;(void)color;(void)i;(void)tc;
	// t_calc_light	cl;

	// cl.v_lightDir = ft_vecnormalize(ft_vecsub(m->lit[i].pos, m->camdir.v_tpos));
	// cl.v_n.x = 2 * (m->camdir.v_tpos.x - tc->normal.x);
	// cl.v_n.y = 0;
	// cl.v_n.z = 2 * (m->camdir.v_tpos.z - tc->normal.z);
	// cl.naiseki = ft_vecinnerprod(ft_vecnormalize(cl.v_n), cl.v_lightDir);
	// cl.refDir = ft_vecnormalize(ft_vecsub(ft_vecmult(
	// 				ft_vecnormalize(cl.v_n), 2 * cl.naiseki), cl.v_lightDir));
	// cl.invEyeDir = ft_vecnormalize(ft_vecmult(m->camdir.v_de, -1));
	// cl.vrDot = ft_vecinnerprod(cl.invEyeDir, cl.refDir);
	// if (cl.vrDot < 0)
	// 	cl.vrDot = 0;
	// cl.vrDotPow = adjust_range(pow(cl.vrDot, m->shininess),
	// 		(t_minmax){.min = 0, .max = 1}, (t_minmax){.min = 0, .max = 255});
	// color->r += m->kSpe.r * m->lit[i].itsty * m->lit[i].rgb.r
	// 	* cl.vrDotPow * tc->rgb.r;
	// color->g += m->kSpe.g * m->lit[i].itsty * m->lit[i].rgb.g
	// 	* cl.vrDotPow * tc->rgb.g;
	// color->b += m->kSpe.b * m->lit[i].itsty * m->lit[i].rgb.b
	// 	* cl.vrDotPow * tc->rgb.b;
}

// tpos			：cross point (pi) of the v_cam and the surface of the object
// v_lightDir	: vector of incidence (l) (nyuusha vector)
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
