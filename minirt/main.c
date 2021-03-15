
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

/* Diffuse: 拡散反射
*/
double	calcDiffuse()
{
	return (0);
}

/* Specular: 鏡面反射
*/
double	calcSpecular()
{
	return (0);
}

double	get_nearest_shape(t_vec v_w, t_vec v_sphere, double sphereR, t_map m)
{
	t_vec	v_de;
	t_vec	v_tmp;
	double	t;
	
	v_de = ft_vecsub(v_w, m.v_eye[0]);
	v_tmp = ft_vecsub(m.v_eye[0], v_sphere);
	double A = ft_vecnormsq(v_de);
	double B = 2 * ft_vecinnerprod(v_de, v_tmp);
	double C = ft_vecnormsq(v_tmp) - sphereR * sphereR;
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

int ray_trace(t_vec v_w, t_map m, t_vec v_sphere, double t)
{
	//(1) ambient light 環境光
	t_color radianceAmb;
	radianceAmb.r = m.kAmb.r * m.ambientIntensity;
	radianceAmb.g = m.kAmb.g * m.ambientIntensity;
	radianceAmb.b = m.kAmb.b * m.ambientIntensity;

	//(2) diffuse reflection 拡散反射光
	t_vec v_de = ft_vecsub(v_w, m.v_eye[0]);
	t_vec v_tpos = ft_vecadd(m.v_eye[0], ft_vecmult(v_de, t));
	t_vec v_lightDir = ft_vecnormalize(ft_vecsub(m.v_light[0], v_tpos));
	t_vec v_sphereN = ft_vecnormalize(ft_vecsub(v_tpos, v_sphere));
	double naiseki = ft_vecinnerprod(v_sphereN, v_lightDir);
	if (naiseki < 0)
		naiseki = 0;
	double nlDot = ft_map(naiseki, 0, 1, 0, 255);
	t_color radianceDif;
	radianceDif.r = m.kDif.r * m.lightIntensity * nlDot;
	radianceDif.g = m.kDif.g * m.lightIntensity * nlDot;
	radianceDif.b = m.kDif.b * m.lightIntensity * nlDot;
	
	//(3) specular reflection 鏡面反射光
	t_color radianceSpe;// = 0.0f;
	if (naiseki > 0)
	{
		t_vec refDir = ft_vecsub(ft_vecmult(v_sphereN, 2 * naiseki), v_lightDir); 
		t_vec invEyeDir = ft_vecnormalize(ft_vecmult(v_de, -1));
		double vrDot = ft_vecinnerprod(invEyeDir, refDir);
		if (vrDot < 0)
			vrDot = 0;
		vrDot = ft_map(pow(vrDot, m.shininess), 0, 1, 0, 255);
		radianceSpe.r = m.kSpe.r * m.lightIntensity * vrDot;
		radianceSpe.g = m.kSpe.g * m.lightIntensity * vrDot;
		radianceSpe.b = m.kSpe.b * m.lightIntensity * vrDot;
		//radianceSpe = m.kSpe * m.lightIntensity * pow(vrDot, m.shininess);
	}

	//(1)-(3)合計
	double rSumr = radianceAmb.r + radianceDif.r + radianceSpe.r;
	double rSumg = radianceAmb.g + radianceDif.g + radianceSpe.g;
	double rSumb = radianceAmb.b + radianceDif.b + radianceSpe.b;
	//rSum = radianceAmb + radianceDif;
	//rSum = radianceAmb + radianceSpe;
	if (rSumr > 255)
		rSumr = 255;
	if (rSumg > 255)
		rSumg = 255;
	if (rSumb > 255)
		rSumb = 255;
	//return (ft_color(rSum, 0, 0));
	return (ft_color(rSumr, rSumg, rSumb));
}

int	draw_plane(t_vec v_w, t_map m)
{
	double	dn_dot;

	dn_dot = ft_vecinnerprod(v_w, m.pl.normal);
	if (dn_dot >= 0)
	{
		t_vec	v_sp;
		double t;
		v_sp.x = v_w.x - m.pl.position.x;
		v_sp.y = v_w.y - m.pl.position.x;
		v_sp.z = v_w.z - m.pl.position.x;
		t = - ft_vecinnerprod(v_sp, m.pl.normal) / dn_dot;
		if (t > 0)
		{
			return (t);
		}
		else
			return (0);
	}
	else
		return (-1);
}

int	decide_color(t_vec v_w, t_map m)
{
	double	t;
	int		color;
	double 	chkt;

	t = -1;
	color = draw_plane(v_w, m);
	for (int i = 0; i < 5; i++)
	{
		chkt = get_nearest_shape(v_w, m.v_sphere[i], m.sphereR[i], m);
		if (chkt >= 0 && (t == -1 || chkt < t))
		{
			color = ray_trace(v_w, m, m.v_sphere[i], chkt);
			t = chkt;
		}
	}
	return (color);
}

void	init_m(t_map *m)
{
	m->window_x = 242;
	m->window_y = 242;
	ft_vecset(&m->v_eye[0], 0, 0, -5);
	
	ft_vecset(&m->pl.normal, 0.0, 1.0, 0.0);
	ft_vecset(&m->pl.position, 0.0, -1.0, 0.0);
	
	//ft_vecset(&m->v_sphere[0], 0, 0, 5);
	//ft_vecset(&m->v_sphere[1], 1, 1, 2);
	ft_vecset(&m->v_sphere[0], 3, 0, 25);
	ft_vecset(&m->v_sphere[1], 2, 0, 20);
	ft_vecset(&m->v_sphere[2], 1, 0, 15);
	ft_vecset(&m->v_sphere[3], 0, 0, 10);
	ft_vecset(&m->v_sphere[4], -1, 0, 5);
	m->sphereR[0] = 1.0;
	m->sphereR[1] = 1.0;
	m->sphereR[2] = 1.0;
	m->sphereR[3] = 1.0;
	m->sphereR[4] = 1.0;
	ft_vecset(&m->v_light[0], -5, 5, -5);

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

	m->lightIntensity = 1.0;
	m->ambientIntensity = 0.1;
}

void	print_m(t_map *m)
{
	printf("===== current config begin =====\n");
	printf("R        : %d x %d\n", m->window_x, m->window_y);
	printf("Eye[0]   : %.2f, %.2f, %.2f\n", m->v_eye[0].x, m->v_eye[0].y, m->v_eye[0].z);
	printf("Plane    : %.2f, %.2f, %.2f / %.2f, %.2f, %.2f\n", m->pl.normal.x, m->pl.normal.y, m->pl.normal.z,
			m->pl.position.x, m->pl.position.y, m->pl.position.z);
	
	printf("Sphere[0]: %.2f, %.2f, %.2f (r:%.2f)\n", m->v_sphere[0].x, m->v_sphere[0].y, m->v_sphere[0].z, m->sphereR[0]);
	printf("Sphere[1]: %.2f, %.2f, %.2f (r:%.2f)\n", m->v_sphere[1].x, m->v_sphere[1].y, m->v_sphere[1].z, m->sphereR[1]);
	printf("Sphere[2]: %.2f, %.2f, %.2f (r:%.2f)\n", m->v_sphere[2].x, m->v_sphere[2].y, m->v_sphere[2].z, m->sphereR[2]);
	printf("Sphere[3]: %.2f, %.2f, %.2f (r:%.2f)\n", m->v_sphere[3].x, m->v_sphere[3].y, m->v_sphere[3].z, m->sphereR[3]);
	printf("Sphere[4]: %.2f, %.2f, %.2f (r:%.2f)\n", m->v_sphere[4].x, m->v_sphere[4].y, m->v_sphere[4].z, m->sphereR[4]);
	printf("Light[0] : %.2f, %.2f, %.2f\n", m->v_light[0].x, m->v_light[0].y, m->v_light[0].z);

	printf("kAmb     : %.2f, %.2f, %.2f\n", m->kAmb.r, m->kAmb.g, m->kAmb.b);
	printf("kDif     : %.2f, %.2f, %.2f\n", m->kDif.r, m->kDif.g, m->kDif.b);
	printf("kSpe     : %.2f, %.2f, %.2f\n", m->kSpe.r, m->kSpe.g, m->kSpe.b);
	
	printf("shininess       : %.2f\n", m->shininess);

	printf("lightIntensity  : %.2f\n", m->lightIntensity);
	printf("ambientIntensity: %.2f\n", m->ambientIntensity);
	printf("===== current config end =====\n\n");
}

/*
** Sphere
**/
int	draw_sphere(void *win, int w, int h, t_map *m)
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
			color = decide_color(v_w, *m);
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

/*
** main func
**/
int	main(int argc, char **argv)
{
	t_map	m;

	init_m(&m);
	if (argc >= 2)
		readFromFile(argv[1], &m);
	print_m(&m);

	decide_endian();

	if (!(mlx = mlx_init()))
	{
		write(1, "Error\nInitialization failed.\n", 29);
		exit(1);
	}
	printf("Mlx init OK (use_xshm:%d, pshm_format:%d).\n",((t_xvar *)mlx)->use_xshm,((t_xvar *)mlx)->pshm_format);

	printf("Window1 creation: %dx%d \"Title 1\" ...", m.window_x, m.window_y);
	if (!(win1 = mlx_new_window(mlx, m.window_x, m.window_y, "Title1")))
	{
		printf(" !! KO !!\n");
		exit(1);
	}
	printf("OK\n");


	m.objtype[0] = 'Q';
	m.obj[0] = malloc(sizeof(t_square));
	if (m.objtype[0] == 'Q')
	{
		//t_square *sq = (t_square *)m.obj[0];
	//	sq->center_x = 10;
		((t_square *)m.obj[0])->center.x = 10;
		printf("sq:%f\n", ((t_square *)m.obj[0])->center.x);
	}


	printf("Drawing sphere ...");
	draw_sphere(win1, m.window_x, m.window_y, &m);
	printf("OK\n");
	mlx_key_hook(win1, key_win1, 0);
	mlx_loop(mlx);
	//sleep(2);
	exit(0);
}
