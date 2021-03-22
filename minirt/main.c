#include	"main.h"

void	*mlx;
void	*win1;
int		local_endian;

int	key_win1(int key,void *p)
{
	(void) p;

	printf("Key in Win1 : %d\n",key);
	if (key==0xFF1B)
		exit(0);
	return (0);
}

/*
 ** Resizing scale
 **/
double	ft_map(double x, int froma, int fromb, int toa, int tob)
{
	double pos = (x - (double)froma) / ((double)fromb - (double)froma);
	double ret = pos * ((double)tob - (double)toa) + (double)toa;
	return (ret);
}

/* color
 * specify color value between 0-255 for each params
 */
int	ft_color(int red, int green, int blue)
{
	int	c;

	c = (red << 16) + (green << 8) + blue;
	return (c);
}

void	set_color(t_color *c, double red, double green, double blue)
{
	c->r = red;
	c->g = green;
	c->b = blue;
	return ;
}

t_color		set_rgb_inrange(t_color c)
{
	if (c.r > 255)
		c.r = 255;
	if (c.r < 0)
		c.r = 0;
	if (c.g > 255)
		c.g = 255;
	if (c.g < 0)
		c.g = 0;
	if (c.b > 255)
		c.b = 255;
	if (c.b < 0)
		c.b = 0;
	return (c);
}

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

int ray_trace_sphere(t_vec v_w, t_map *m, t_sphere *ts, double t)
{
	t_color color;

	//(1) ambient light 環境光
	set_color(&color, m->kAmb.r * m->ambItsty, m->kAmb.g * m->ambItsty, m->kAmb.b * m->ambItsty);

	//(2) diffuse reflection 拡散反射光
	t_vec v_de = ft_vecsub(v_w, m->v_eye[0]);
	t_vec v_tpos = ft_vecadd(m->v_eye[0], ft_vecmult(v_de, t));//tpos：視線と球上の交点(pi)
	t_vec v_lightDir = ft_vecnormalize(ft_vecsub(m->v_light[0], v_tpos));//入射ベクトル(l)
	t_vec v_sphereN = ft_vecnormalize(ft_vecsub(v_tpos, ts->center));//法線ベクトル(n)
	double naiseki = ft_vecinnerprod(v_sphereN, v_lightDir);
	if (naiseki < 0)
		naiseki = 0;
	double nlDot = ft_map(naiseki, 0, 1, 0, 255);
	color.r += m->kDif.r * m->lightItsty[0] * nlDot;
	color.g += m->kDif.g * m->lightItsty[0] * nlDot;
	color.b += m->kDif.b * m->lightItsty[0] * nlDot;

	//(3) specular reflection 鏡面反射光
	if (naiseki > 0)
	{
		t_vec refDir = ft_vecsub(ft_vecmult(v_sphereN, 2 * naiseki), v_lightDir); 
		t_vec invEyeDir = ft_vecnormalize(ft_vecmult(v_de, -1));
		double vrDot = ft_vecinnerprod(invEyeDir, refDir);
		if (vrDot < 0)
			vrDot = 0;
		double vrDotPow = ft_map(pow(vrDot, m->shininess), 0, 1, 0, 255);
		color.r += m->kSpe.r * m->lightItsty[0] * vrDotPow;
		color.g += m->kSpe.g * m->lightItsty[0] * vrDotPow;
		color.b += m->kSpe.b * m->lightItsty[0] * vrDotPow;
	}
	color = set_rgb_inrange(color);
	return (ft_color(color.r, color.g, color.b));
}

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

int ray_trace_plane(t_vec v_w, t_map *m, t_plane *tp, double t)
{
	t_color color;

	//(1) ambient light 環境光
	set_color(&color, m->kAmb.r * m->ambItsty, m->kAmb.g * m->ambItsty, m->kAmb.b * m->ambItsty);

	//(2) diffuse reflection 拡散反射光
	t_vec v_de = ft_vecsub(v_w, m->v_eye[0]);
	t_vec v_tpos = ft_vecadd(m->v_eye[0], ft_vecmult(v_de, t));
	t_vec v_lightDir = ft_vecnormalize(ft_vecsub(m->v_light[0], v_tpos));
	double naiseki = ft_vecinnerprod(ft_vecnormalize(tp->normal), v_lightDir);
	if (naiseki < 0)
		naiseki = 0;
	double nlDot = ft_map(naiseki, 0, 1, 0, 255);
	color.r += m->kDif.r * m->lightItsty[0] * nlDot;
	color.g += m->kDif.g * m->lightItsty[0] * nlDot;
	color.b += m->kDif.b * m->lightItsty[0] * nlDot;
	
	//(3) specular reflection 鏡面反射光
	if (naiseki > 0)
	{
		t_vec refDir = ft_vecsub(ft_vecmult(tp->normal, 2 * naiseki), v_lightDir); 
		t_vec invEyeDir = ft_vecnormalize(ft_vecmult(v_de, -1));
		double vrDot = ft_vecinnerprod(invEyeDir, refDir);
		if (vrDot < 0)
			vrDot = 0;
		double vrDotPow = ft_map(pow(vrDot, m->shininess), 0, 1, 0, 255);
		color.r += m->kSpe.r * m->lightItsty[0] * vrDotPow;
		color.g += m->kSpe.g * m->lightItsty[0] * vrDotPow;
		color.b += m->kSpe.b * m->lightItsty[0] * vrDotPow;
	}
	color = set_rgb_inrange(color);
	return (ft_color(color.r, color.g, color.b));
}

double	get_nearest_square(t_vec v_w, t_vec v_eye, t_square *ts)
{
	(void)v_w;
	(void)v_eye;
	(void)ts;
	return (-1);
}

int	ray_trace_square(t_vec v_w, t_map *m, t_square *ts, double t)
{
	(void)v_w;
	(void)m;
	(void)ts;
	(void)t;
	return (0);
}

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

int	ray_trace_cylinder(t_vec v_w, t_map *m, t_cylinder *tc, double t)
{
	t_color color;

	//(1) ambient light 環境光
	set_color(&color, m->kAmb.r * m->ambItsty, m->kAmb.g * m->ambItsty, m->kAmb.b * m->ambItsty);

	//(2) diffuse reflection 拡散反射光
	t_vec v_de = ft_vecsub(v_w, m->v_eye[0]);
	t_vec v_tpos = ft_vecadd(m->v_eye[0], ft_vecmult(v_de, t));//tpos：視線と球上の交点(pi)
	t_vec v_lightDir = ft_vecnormalize(ft_vecsub(m->v_light[0], v_tpos));//入射ベクトル(l)
	t_vec v_n;//法線ベクトル(n)
	v_n.x = 2 * (v_tpos.x - tc->center.x);
	v_n.y = 0;
	v_n.z = 2 * (v_tpos.z - tc->center.z);
	double naiseki = ft_vecinnerprod(ft_vecnormalize(v_n), v_lightDir);
	if (naiseki < 0)
		naiseki = 0;
	double nlDot = ft_map(naiseki, 0, 1, 0, 255);
	color.r += m->kDif.r * m->lightItsty[0] * nlDot;
	color.g += m->kDif.g * m->lightItsty[0] * nlDot;
	color.b += m->kDif.b * m->lightItsty[0] * nlDot;

	//(3) specular reflection 鏡面反射光
	if (naiseki > 0)
	{
		t_vec refDir = ft_vecnormalize(ft_vecsub(ft_vecmult(ft_vecnormalize(v_n), 2 * naiseki), v_lightDir)); 
		t_vec invEyeDir = ft_vecnormalize(ft_vecmult(v_de, -1));
		double vrDot = ft_vecinnerprod(invEyeDir, refDir);
		if (vrDot < 0)
			vrDot = 0;
		double vrDotPow = ft_map(pow(vrDot, m->shininess), 0, 1, 0, 255);
		color.r += m->kSpe.r * m->lightItsty[0] * vrDotPow;
		color.g += m->kSpe.g * m->lightItsty[0] * vrDotPow;
		color.b += m->kSpe.b * m->lightItsty[0] * vrDotPow;
	}
	color = set_rgb_inrange(color);
	return (ft_color(color.r, color.g, color.b));
}

double	get_nearest_triangle(t_vec v_w, t_vec v_eye, t_triangle *tt)
{
	t_plane tp;
	double t;

	tp.normal = tt->normal;
	//tp.position = ft_vecsub(tt->second, tt->first);
	tp.position = tt->first;
	t = get_nearest_plane(v_w, v_eye, &tp);
	if (t >= 0)
	{
		t_vec v_de = ft_vecsub(v_w, v_eye);
		t_vec v_tpos = ft_vecadd(v_eye, ft_vecmult(v_de, t));//tpos：視線と面上の交点(pi)
		int	a,b,c;
		a = ft_veccrossprod_sign(v_tpos, tt->first, tt->second) < 0 ? -1 : 1;
		b = ft_veccrossprod_sign(v_tpos, tt->second, tt->third) < 0 ? -1 : 1;
		c = ft_veccrossprod_sign(v_tpos, tt->third, tt->first) < 0 ? -1 : 1;
		if (a != b || b != c)
			t = -1;
	}
	return (t);
}

int	ray_trace_triangle(t_vec v_w, t_map *m, t_triangle *tt, double t)
{
	t_plane tp;

	tp.normal = tt->normal;
	//tp.position = ft_vecnormalize(ft_vecsub(tt->second, tt->first));
	tp.position = tt->first;
	return (ray_trace_plane(v_w, m, &tp, t));
}

int	decide_color(t_vec v_w, t_map *m)
{
	double	t;
	int		color;
	double 	chkt;

	t = -1;
	color = ft_color(92, 151, 243);
	for (int i = 0; i < m->obj_count; i++)
	{
		chkt = -1;
		if (m->obj_type[i] == CMD_SPHERE)
			chkt = get_nearest_sphere(v_w, m->v_eye[0], (t_sphere *)m->obj[i]);
		else if (m->obj_type[i] == CMD_PLANE)
			chkt = get_nearest_plane(v_w, m->v_eye[0], (t_plane *)m->obj[i]);
		else if (m->obj_type[i] == CMD_SQUARE)
			chkt = get_nearest_square(v_w, m->v_eye[0], (t_square *)m->obj[i]);
		else if (m->obj_type[i] == CMD_CYLINDER)
			chkt = get_nearest_cylinder(v_w, m->v_eye[0], (t_cylinder *)m->obj[i]);
		else if (m->obj_type[i] == CMD_TRIANGLE)
			chkt = get_nearest_triangle(v_w, m->v_eye[0], (t_triangle *)m->obj[i]);
		if (chkt >= 0 && (t == -1 || chkt < t))
		{
			t = chkt;
			if (m->obj_type[i] == CMD_SPHERE)
				color = ray_trace_sphere(v_w, m, (t_sphere *)m->obj[i], chkt);
			else if (m->obj_type[i] == CMD_PLANE)
				color = ray_trace_plane(v_w, m, (t_plane *)m->obj[i], chkt);
			else if (m->obj_type[i] == CMD_SQUARE)
				color = ray_trace_square(v_w, m, (t_square *)m->obj[i], chkt);
			else if (m->obj_type[i] == CMD_CYLINDER)
				color = ray_trace_cylinder(v_w, m, (t_cylinder *)m->obj[i], chkt);
			else if (m->obj_type[i] == CMD_TRIANGLE)
				color = ray_trace_triangle(v_w, m, (t_triangle *)m->obj[i], chkt);
		}
	}
	return (color);
}

void	init_m(t_map *m)
{
	m->eye_count = 0;
	m->light_count = 0;
	m->obj_count = 0;
	
	m->window_x = -1;
	m->window_y = -1;

	m->kAmb.r = -1;
	m->kAmb.g = -1;
	m->kAmb.b = -1;
	
	m->ambItsty = -1;
}

void	set_default_Value(t_map *m)
{
	m->window_x = 242;
	m->window_y = 242;

	ft_vecset(&m->v_eye[m->eye_count++], 0, 0, -5);
	ft_vecset(&m->v_eye[m->eye_count++], 0, 1, 2);

	ft_vecset(&m->v_light[m->light_count++], -5, 5, -5);
	ft_vecset(&m->v_light[m->light_count++], -5, 3, -2);

	m->kAmb.r = 0.01;
	m->kAmb.g = 0.01;
	m->kAmb.b = 0.01;

	m->kDif.r = 0.69;
	m->kDif.g = 0.0;
	m->kDif.b = 0.0;

	m->kSpe.r = 0.3;
	m->kSpe.g = 0.3;
	m->kSpe.b = 0.3;

	m->shininess = 8;

	m->lightItsty[0] = 1.0;
	m->ambItsty = 0.1;

	m->obj_type[m->obj_count] = CMD_SPHERE;
	m->obj[m->obj_count] = (t_sphere *)malloc(sizeof(t_sphere));
	ft_vecset(&((t_sphere *)m->obj[m->obj_count])->center, 3, 0, 25);
	((t_sphere *)m->obj[m->obj_count])->diameter = 1.0;
	m->obj_count++;

	m->obj_type[m->obj_count] = CMD_SPHERE;
	m->obj[m->obj_count] = (t_sphere *)malloc(sizeof(t_sphere));
	ft_vecset(&((t_sphere *)m->obj[m->obj_count])->center, 2, 0, 20);
	((t_sphere *)m->obj[m->obj_count])->diameter = 1.0;
	m->obj_count++;

	// m->obj_type[m->obj_count] = CMD_SPHERE;
	// m->obj[m->obj_count] = (t_sphere *)malloc(sizeof(t_sphere));
	// ft_vecset(&((t_sphere *)m->obj[m->obj_count])->center, 1, 0, 15);
	// ((t_sphere *)m->obj[m->obj_count])->diameter = 1.0;
	// m->obj_count++;

	// m->obj_type[m->obj_count] = CMD_SPHERE;
	// m->obj[m->obj_count] = (t_sphere *)malloc(sizeof(t_sphere));
	// ft_vecset(&((t_sphere *)m->obj[m->obj_count])->center, 0, 0, 10);
	// ((t_sphere *)m->obj[m->obj_count])->diameter = 1.0;
	// m->obj_count++;

	// m->obj_type[m->obj_count] = CMD_SPHERE;
	// m->obj[m->obj_count] = (t_sphere *)malloc(sizeof(t_sphere));
	// ft_vecset(&((t_sphere *)m->obj[m->obj_count])->center, -1, 0, 5);
	// ((t_sphere *)m->obj[m->obj_count])->diameter = 1.0;
	// m->obj_count++;

	// m->obj_type[m->obj_count] = CMD_PLANE;
	// m->obj[m->obj_count] = (t_plane *)malloc(sizeof(t_plane));
	// ft_vecset(&((t_plane *)m->obj[m->obj_count])->normal, 0.0, 1.0, 0.0);
	// ft_vecset(&((t_plane *)m->obj[m->obj_count])->position, 0.0, -1.0, 0.0);
	// m->obj_count++;

	// m->obj_type[m->obj_count] = CMD_CYLINDER;
	// m->obj[m->obj_count] = (t_cylinder *)malloc(sizeof(t_cylinder));
	// ft_vecset(&((t_cylinder *)m->obj[m->obj_count])->center, 3, 0, 25);
	// ft_vecset(&((t_cylinder *)m->obj[m->obj_count])->orientation, 0.0, -1.0, 0.0);
	// ((t_cylinder *)m->obj[m->obj_count])->diameter = 1.0;
	// ((t_cylinder *)m->obj[m->obj_count])->height = 2.0;
	// m->obj_count++;
	
	// m->obj_type[m->obj_count] = CMD_CYLINDER;
	// m->obj[m->obj_count] = (t_cylinder *)malloc(sizeof(t_cylinder));
	// ft_vecset(&((t_cylinder *)m->obj[m->obj_count])->center, 2, 0, 20);
	// ft_vecset(&((t_cylinder *)m->obj[m->obj_count])->orientation, 0.0, -1.0, 0.0);
	// ((t_cylinder *)m->obj[m->obj_count])->diameter = 1.0;
	// ((t_cylinder *)m->obj[m->obj_count])->height = 2.0;
	// m->obj_count++;
	
	// m->obj_type[m->obj_count] = CMD_CYLINDER;
	// m->obj[m->obj_count] = (t_cylinder *)malloc(sizeof(t_cylinder));
	// ft_vecset(&((t_cylinder *)m->obj[m->obj_count])->center, 1, 0, 15);
	// ft_vecset(&((t_cylinder *)m->obj[m->obj_count])->orientation, 0.0, -1.0, 0.0);
	// ((t_cylinder *)m->obj[m->obj_count])->diameter = 1.0;
	// ((t_cylinder *)m->obj[m->obj_count])->height = 2.0;
	// m->obj_count++;
	
	// m->obj_type[m->obj_count] = CMD_CYLINDER;
	// m->obj[m->obj_count] = (t_cylinder *)malloc(sizeof(t_cylinder));
	// ft_vecset(&((t_cylinder *)m->obj[m->obj_count])->center, 0, 0, 10);
	// ft_vecset(&((t_cylinder *)m->obj[m->obj_count])->orientation, 0.0, -1.0, 0.0);
	// ((t_cylinder *)m->obj[m->obj_count])->diameter = 1.0;
	// ((t_cylinder *)m->obj[m->obj_count])->height = 2.0;
	// m->obj_count++;
	
	// m->obj_type[m->obj_count] = CMD_CYLINDER;
	// m->obj[m->obj_count] = (t_cylinder *)malloc(sizeof(t_cylinder));
	// ft_vecset(&((t_cylinder *)m->obj[m->obj_count])->center, -1, 0, 5);
	// ft_vecset(&((t_cylinder *)m->obj[m->obj_count])->orientation, 0.0, -1.0, 0.0);
	// ((t_cylinder *)m->obj[m->obj_count])->diameter = 1.0;
	// ((t_cylinder *)m->obj[m->obj_count])->height = 2.0;
	// m->obj_count++;

	m->obj_type[m->obj_count] = CMD_TRIANGLE;
	m->obj[m->obj_count] = (t_triangle *)malloc(sizeof(t_triangle));
	ft_vecset(&((t_triangle *)m->obj[m->obj_count])->first, 0.0, 5.0, 0.0);
	ft_vecset(&((t_triangle *)m->obj[m->obj_count])->second, 0.0, 0.0, -2.0);
	ft_vecset(&((t_triangle *)m->obj[m->obj_count])->third, 5.0, 0.0, 00.0);
	// ft_vecset(&((t_triangle *)m->obj[m->obj_count])->first, 10.0, 20.0, 10.0);
	// ft_vecset(&((t_triangle *)m->obj[m->obj_count])->second, 10.0, 10.0, 20.0);
	// ft_vecset(&((t_triangle *)m->obj[m->obj_count])->third, 20.0, 10.0, 10.0);
	t_triangle *t = (t_triangle *)m->obj[m->obj_count];
	t_vec n = ft_veccrossprod(ft_vecsub(t->second, t->first), ft_vecsub(t->third, t->first));
	n = ft_vecnormalize(n);
	ft_vecset(&((t_triangle *)m->obj[m->obj_count])->normal, n.x, n.y, n.z);
	m->obj_count++;

}

void	print_sphere(t_sphere *ts)
{
	printf("Sphere");
	printf(": %.2f, %.2f, %.2f (r:%.2f) / rgb:%.2f %.2f %.2f\n",
			ts->center.x,
			ts->center.y,
			ts->center.z,
			ts->diameter,
			ts->rgb.r,
			ts->rgb.g,
			ts->rgb.b);
}

void	print_plane(t_plane *tp)
{
	printf("Plane");
	printf(": %.2f, %.2f, %.2f / %.2f, %.2f, %.2f / rgb:%.2f %.2f %.2f\n",
			tp->normal.x,
			tp->normal.y,
			tp->normal.z,
			tp->position.x,
			tp->position.y,
			tp->position.z,
			tp->rgb.r,
			tp->rgb.g,
			tp->rgb.b);
}

void	print_square(t_square *ts)
{
	printf("Square");
	printf(": %.2f, %.2f, %.2f / %.2f, %.2f, %.2f / %.2f / rgb:%.2f %.2f %.2f\n",
			ts->center.x,
			ts->center.y,
			ts->center.z,
			ts->orientation.x,
			ts->orientation.y,
			ts->orientation.z,
			ts->sidesize,
			ts->rgb.r,
			ts->rgb.g,
			ts->rgb.b);
}

void	print_cylinder(t_cylinder *tc)
{
	printf("Cylinder");
	printf(": %.2f, %.2f, %.2f / %.2f, %.2f, %.2f / %.2f / %.2f / rgb:%.2f %.2f %.2f\n",
			tc->center.x,
			tc->center.y,
			tc->center.z,
			tc->orientation.x,
			tc->orientation.y,
			tc->orientation.z,
			tc->diameter,
			tc->height,
			tc->rgb.r,
			tc->rgb.g,
			tc->rgb.b);
}

void	print_triangle(t_triangle *tt)
{
	printf("Triangle");
	printf(": %.2f, %.2f, %.2f / %.2f, %.2f, %.2f / %.2f, %.2f, %.2f / rgb:%.2f %.2f %.2f\n",
			tt->first.x,
			tt->first.y,
			tt->first.z,
			tt->second.x,
			tt->second.y,
			tt->second.z,
			tt->third.x,
			tt->third.y,
			tt->third.z,
			tt->rgb.r,
			tt->rgb.g,
			tt->rgb.b);
}

void	print_m(t_map *m)
{
	printf("===== current config begin =====\n");
	printf("R        : %d x %d\n", m->window_x, m->window_y);
	for (int i = 0; i < m->eye_count; i++)
		printf("Eye[%d]   : %.2f, %.2f, %.2f\n", i, m->v_eye[i].x, m->v_eye[i].y, m->v_eye[i].z);
	for (int i = 0; i < m->light_count; i++)
		printf("Light[%d] : %.2f, %.2f, %.2f\n", i, m->v_light[i].x, m->v_light[i].y, m->v_light[i].z);

	printf("kAmb     : %.2f, %.2f, %.2f\n", m->kAmb.r, m->kAmb.g, m->kAmb.b);
	printf("kDif     : %.2f, %.2f, %.2f\n", m->kDif.r, m->kDif.g, m->kDif.b);
	printf("kSpe     : %.2f, %.2f, %.2f\n", m->kSpe.r, m->kSpe.g, m->kSpe.b);

	printf("shininess       : %.2f\n", m->shininess);

	for (int i = 0; i < m->light_count; i++)
		printf("lightItsty[%d]  : %.2f\n", i, m->lightItsty[i]);
	printf("ambItsty        : %.2f\n", m->ambItsty);
	printf("obj_count       : %d\n", m->obj_count);
	for (int i = 0; i < m->obj_count; i++)
	{
		printf("[%d] ", i);
		if (m->obj_type[i] == CMD_SPHERE)
			print_sphere(m->obj[i]);
		else if (m->obj_type[i] == CMD_PLANE)
			print_plane(m->obj[i]);
		else if (m->obj_type[i] == CMD_SQUARE)
			print_square(m->obj[i]);
		else if (m->obj_type[i] == CMD_CYLINDER)
			print_cylinder(m->obj[i]);
		else if (m->obj_type[i] == CMD_TRIANGLE)
			print_triangle(m->obj[i]);
	}
	printf("===== current config end =====\n\n");
}

int	draw_map(void *win, int w, int h, t_map *m)
{
	int	x;
	int	y;
	t_vec	v_w;
	int	color;

	v_w.z = 0;
	y = 0;
	while (y < h)
	{
		v_w.y = ft_map(y, 0, h-1, 1, -1);
		x = 0;
		while (x < w)
		{
			v_w.x = ft_map(x, 0, w-1, -1, 1);
			color = decide_color(v_w, m);
			mlx_pixel_put(mlx, win, x, y, color);
			x++;
		}
		y++;
	}
	return (0);
}

void	decide_endian(void)
{
	int		a;

	a = 0x11223344;
	if (((unsigned char *)&a)[0] == 0x11)
		local_endian = 1;
	else
		local_endian = 0;
	printf("Local Endian : %d.\n",local_endian);
}

void	display_window(t_map *m)
{
	if (!(mlx = mlx_init()))
	{
		write(1, "Error\nInitialization failed.\n", 29);
		exit(1);
	}
	printf("Mlx init OK (use_xshm:%d, pshm_format:%d).\n",((t_xvar *)mlx)->use_xshm,((t_xvar *)mlx)->pshm_format);

	printf("Window1 creation: %dx%d \"Title 1\" ...", m->window_x, m->window_y);
	if (!(win1 = mlx_new_window(mlx, m->window_x, m->window_y, "Title1")))
	{
		printf(" !! KO !!\n");
		exit(1);
	}
	printf("OK\n");

	printf("Drawing sphere ...");
	draw_map(win1, m->window_x, m->window_y, m);
	printf("OK\n");
	mlx_key_hook(win1, key_win1, 0);
	mlx_loop(mlx);
	//sleep(2);
}

int	write_bmp_simple_stream(FILE *fp)//, image_t *img) {
{
	uint8_t		header_buffer[DEFAULT_HEADER_SIZE];
	BITMAPFILEHEADER *file = (BITMAPFILEHEADER*)header_buffer;
	BITMAPINFOHEADER *info = (BITMAPINFOHEADER*)(header_buffer + FILE_HEADER_SIZE);
	int x, y;
	int stride;
	uint8_t *row, *buffer;
	/*
	if (img->color_type != COLOR_TYPE_RGB) {
		return -1;
	}
	*/
	//stride = (img->width * 3 + 3) / 4 * 4;
	stride = (100 * 3 + 3) / 4 * 4;
	if ((buffer = malloc(stride)) == NULL) {
		return -1;
	}
	file->bfType = FILE_TYPE;
	//file->bfSize = DEFAULT_HEADER_SIZE + stride * img->height;
	file->bfSize = DEFAULT_HEADER_SIZE + stride * 100;
	file->bfReserved1 = 0;
	file->bfReserved2 = 0;
	file->bfOffBits = DEFAULT_HEADER_SIZE;
	info->biSize = INFO_HEADER_SIZE;
	info->biWidth = 100;//img->width;
	//info->biHeight = img->height;
	info->biHeight = 100;
	info->biPlanes = 1;
	info->biBitCount = 24;
	info->biCompression = 0;
	info->biSizeImage = stride * 100;//img->height;
	info->biXPelsPerMeter = 0;
	info->biYPelsPerMeter = 0;
	info->biClrUsed = 0;
	info->biClrImportant = 0;
	if (fwrite(header_buffer, DEFAULT_HEADER_SIZE, 1, fp) != 1) {
		goto error;
	}
	memset(buffer, 0, stride);
	//for (y = img->height - 1; y >= 0; y--) {
	for (y = 100 - 1; y >= 0; y--) {
		row = buffer;
		//for (x = 0; x < img->width; x++) {
		for (x = 0; x < 100; x++) {
			//*row++ = img->map[y][x].c.b;
			//*row++ = img->map[y][x].c.g;
			//*row++ = img->map[y][x].c.r;
			*row++ = 0;
			*row++ = 0;
			*row++ = 255;
		}
		if (fwrite(buffer, stride, 1, fp) != 1) {
			goto error;
		}
	}
	free(buffer);
	return (0);
error:
	free(buffer);
	return (-1);
}

int	write_bmp(t_map *m)
{
	int	ret;
	char	*filename = "out.bmp";

	(void)m;

	ret = -1;
	FILE *fp = fopen(filename, "wb");
	if (fp == NULL) {
		perror(filename);
		return ret;
	}
	ret = write_bmp_simple_stream(fp);//, img);
	fclose(fp);
	return ret;
}

/*
 ** main func
 **/
int	main(int argc, char **argv)
{
	t_map	m;

	init_m(&m);
	if (argc >= 2)
		readFromFile(argv[1], &m);
	else
		set_default_Value(&m);
	print_m(&m);

	decide_endian();
	if (argc >= 3 && strcmp(argv[2], "--save") == 0)
		write_bmp(&m);
	else
		display_window(&m);
	freeX(&m);
	return (0);
}
