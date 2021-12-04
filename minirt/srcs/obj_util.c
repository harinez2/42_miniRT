#include	"main.h"

void	set_ambient_reflection_color(
	t_map *m, t_color *color, t_color *add_color)
{
	set_color(color,
		m->kAmb.r * m->ambItsty * add_color->r,
		m->kAmb.g * m->ambItsty * add_color->g,
		m->kAmb.b * m->ambItsty * add_color->b);
}

t_color	adjust_color_level(t_color *base_color, double innprod)
{
	double	innprod_color;
	t_color	add_color;

	innprod_color = adjust_range(innprod,
			(t_minmax){.min = 0, .max = 1}, (t_minmax){.min = 0, .max = 255});
	add_color.r = base_color->r * innprod_color;
	add_color.g = base_color->g * innprod_color;
	add_color.b = base_color->b * innprod_color;
	return (add_color);
}

void	add_diffuse_reflection_color(
	t_map *m, int lit_i, t_color *color, t_color *add_color)
{
	color->r += m->kDif.r * m->lit[lit_i].itsty * m->lit[lit_i].rgb.r
		* add_color->r;
	color->g += m->kDif.g * m->lit[lit_i].itsty * m->lit[lit_i].rgb.g
		* add_color->g;
	color->b += m->kDif.b * m->lit[lit_i].itsty * m->lit[lit_i].rgb.b
		* add_color->b;
}

void	add_specular_reflection_color(
	t_map *m, int lit_i, t_color *color, t_color *add_color)
{
	color->r += m->kSpe.r * m->lit[lit_i].itsty * m->lit[lit_i].rgb.r
		* add_color->r;
	color->g += m->kSpe.g * m->lit[lit_i].itsty * m->lit[lit_i].rgb.g
		* add_color->g;
	color->b += m->kSpe.b * m->lit[lit_i].itsty * m->lit[lit_i].rgb.b
		* add_color->b;
}

double	calc_minimum_t(double A, double B, double D)
{
	double	t1;
	double	t2;
	double	t;

	t = -1;
	if (-EPSILON < D && D < EPSILON)
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
