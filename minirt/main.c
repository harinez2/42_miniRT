
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

int		set_rgb_inrange(double color)
{
	if (color > 255)
		color = 255;
	if (color < 0)
		color = 0;
	return (color);
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
	t_vec v_tpos = ft_vecadd(m.v_eye[0], ft_vecmult(v_de, t));//tpos：視線と球上の交点(pi)
	t_vec v_lightDir = ft_vecnormalize(ft_vecsub(m.v_light[0], v_tpos));//入射ベクトル(l)
	t_vec v_sphereN = ft_vecnormalize(ft_vecsub(v_tpos, v_sphere));//法線ベクトル(n)
	double naiseki = ft_vecinnerprod(v_sphereN, v_lightDir);
	if (naiseki < 0)
		naiseki = 0;
	double nlDot = ft_map(naiseki, 0, 1, 0, 255);
	t_color radianceDif;
	radianceDif.r = m.kDif.r * m.lightIntensity[0] * nlDot;
	radianceDif.g = m.kDif.g * m.lightIntensity[0] * nlDot;
	radianceDif.b = m.kDif.b * m.lightIntensity[0] * nlDot;

	//(3) specular reflection 鏡面反射光
	t_color radianceSpe;
	radianceSpe.r = 0;
	radianceSpe.g = 0;
	radianceSpe.b = 0;
	if (naiseki > 0)
	{
		t_vec refDir = ft_vecsub(ft_vecmult(v_sphereN, 2 * naiseki), v_lightDir); 
		t_vec invEyeDir = ft_vecnormalize(ft_vecmult(v_de, -1));
		double vrDot = ft_vecinnerprod(invEyeDir, refDir);
		if (vrDot < 0)
			vrDot = 0;
		double vrDotPow = ft_map(pow(vrDot, m.shininess), 0, 1, 0, 255);
		radianceSpe.r = m.kSpe.r * m.lightIntensity[0] * vrDotPow;
		radianceSpe.g = m.kSpe.g * m.lightIntensity[0] * vrDotPow;
		radianceSpe.b = m.kSpe.b * m.lightIntensity[0] * vrDotPow;
	}

	//(1)-(3)合計
	double rSumr = radianceAmb.r + radianceDif.r + radianceSpe.r;
	double rSumg = radianceAmb.g + radianceDif.g + radianceSpe.g;
	double rSumb = radianceAmb.b + radianceDif.b + radianceSpe.b;
	return (ft_color(set_rgb_inrange(rSumr), set_rgb_inrange(rSumg), set_rgb_inrange(rSumb)));
}

int	draw_plane(t_vec v_w, t_map m)
{
	double	wn_dot;

	wn_dot = ft_vecinnerprod(v_w, m.pl.normal);
	if (wn_dot != 0)
	{
		double t;
		
		t_vec v_de = ft_vecsub(v_w, m.v_eye[0]);
		double a = ft_vecinnerprod(m.pl.position, m.pl.normal);
		double b = ft_vecinnerprod(m.v_eye[0], m.pl.normal);
		double c = ft_vecinnerprod(v_de, m.pl.normal);
		t = (a - b) / c;
		if (t > 0)
		{
			//(1) ambient light 環境光
			t_color radianceAmb;
			radianceAmb.r = m.kAmb.r * m.ambientIntensity;
			radianceAmb.g = m.kAmb.g * m.ambientIntensity;
			radianceAmb.b = m.kAmb.b * m.ambientIntensity;

			//(2) diffuse reflection 拡散反射光
			t_vec v_tpos = ft_vecadd(m.v_eye[0], ft_vecmult(v_de, t));
			t_vec v_lightDir = ft_vecnormalize(ft_vecsub(m.v_light[0], v_tpos));
			double naiseki = ft_vecinnerprod(ft_vecnormalize(m.pl.normal), v_lightDir);
			if (naiseki < 0)
				naiseki = 0;
			double nlDot = ft_map(naiseki, 0, 1, 0, 255);
			t_color radianceDif;
			radianceDif.r = m.kDif.r * m.lightIntensity[0] * nlDot;
			radianceDif.g = m.kDif.g * m.lightIntensity[0] * nlDot;
			radianceDif.b = m.kDif.b * m.lightIntensity[0] * nlDot;
			
			//(3) specular reflection 鏡面反射光
			t_color radianceSpe;
			radianceSpe.r = 0;
			radianceSpe.g = 0;
			radianceSpe.b = 0;
			if (naiseki > 0)
			{
				t_vec refDir = ft_vecsub(ft_vecmult(m.pl.normal, 2 * naiseki), v_lightDir); 
				t_vec invEyeDir = ft_vecnormalize(ft_vecmult(v_de, -1));
				double vrDot = ft_vecinnerprod(invEyeDir, refDir);
				if (vrDot < 0)
					vrDot = 0;
				double vrDotPow = ft_map(pow(vrDot, m.shininess), 0, 1, 0, 255);
				radianceSpe.r = m.kSpe.r * m.lightIntensity[0] * vrDotPow;
				radianceSpe.g = m.kSpe.g * m.lightIntensity[0] * vrDotPow;
				radianceSpe.b = m.kSpe.b * m.lightIntensity[0] * vrDotPow;
			}

			//(1)-(3)合計
			double rSumr = radianceAmb.r + radianceDif.r + radianceSpe.r;
			double rSumg = radianceAmb.g + radianceDif.g + radianceSpe.g;
			double rSumb = radianceAmb.b + radianceDif.b + radianceSpe.b;
			return (ft_color(set_rgb_inrange(rSumr), set_rgb_inrange(rSumg), set_rgb_inrange(rSumb)));
		}
	}
	return (ft_color(92, 151, 243));//背景色
}

int	decide_color(t_vec v_w, t_map m)
{
	double	t;
	int		color;
	double 	chkt;

	t = -1;
	color = draw_plane(v_w, m);
	for (int i = 0; i < m.obj_count; i++)
	{
		chkt = get_nearest_shape(v_w, ((t_sphere *)m.obj[i])->center,
				((t_sphere *)m.obj[i])->diameter, m);
		//chkt = get_nearest_shape(v_w, m.v_sphere[i], m.sphereR[i], m);
		if (chkt >= 0 && (t == -1 || chkt < t))
		{
			color = ray_trace(v_w, m, ((t_sphere *)m.obj[i])->center, chkt);
			t = chkt;
		}
	}
	return (color);
}

void	init_m(t_map *m)
{
	m->eye_count = 0;
	m->light_count = 0;
	m->obj_count = 0;
}

void	set_default_Value(t_map *m)
{
	m->window_x = 242;
	m->window_y = 242;

	ft_vecset(&m->v_eye[m->eye_count++], 0, 0, -5);
	ft_vecset(&m->v_eye[m->eye_count++], 0, 1, 2);

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

	m->lightIntensity[0] = 1.0;
	m->ambientIntensity = 0.1;

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

	m->obj_type[m->obj_count] = CMD_SPHERE;
	m->obj[m->obj_count] = (t_sphere *)malloc(sizeof(t_sphere));
	ft_vecset(&((t_sphere *)m->obj[m->obj_count])->center, 1, 0, 15);
	((t_sphere *)m->obj[m->obj_count])->diameter = 1.0;
	m->obj_count++;

	m->obj_type[m->obj_count] = CMD_SPHERE;
	m->obj[m->obj_count] = (t_sphere *)malloc(sizeof(t_sphere));
	ft_vecset(&((t_sphere *)m->obj[m->obj_count])->center, 0, 0, 10);
	((t_sphere *)m->obj[m->obj_count])->diameter = 1.0;
	m->obj_count++;

	m->obj_type[m->obj_count] = CMD_SPHERE;
	m->obj[m->obj_count] = (t_sphere *)malloc(sizeof(t_sphere));
	ft_vecset(&((t_sphere *)m->obj[m->obj_count])->center, -1, 0, 5);
	((t_sphere *)m->obj[m->obj_count])->diameter = 1.0;
	m->obj_count++;

	m->obj_type[m->obj_count] = CMD_PLANE;
	m->obj[m->obj_count] = (t_plane *)malloc(sizeof(t_plane));
	ft_vecset(&((t_plane *)m->obj[m->obj_count])->normal, 0.0, 1.0, 0.0);
	ft_vecset(&((t_plane *)m->obj[m->obj_count])->position, 0.0, -1.0, 0.0);
	m->obj_count++;
}

void	print_m(t_map *m)
{
	printf("===== current config begin =====\n");
	printf("R        : %d x %d\n", m->window_x, m->window_y);
	for (int i = 0; i < m->eye_count; i++)
		printf("Eye[%d]   : %.2f, %.2f, %.2f\n", i, m->v_eye[i].x, m->v_eye[i].y, m->v_eye[i].z);
	printf("Plane    : %.2f, %.2f, %.2f / %.2f, %.2f, %.2f\n", m->pl.normal.x, m->pl.normal.y, m->pl.normal.z,
			m->pl.position.x, m->pl.position.y, m->pl.position.z);

	printf("Sphere[0]: %.2f, %.2f, %.2f (r:%.2f)\n", m->v_sphere[0].x, m->v_sphere[0].y, m->v_sphere[0].z, m->sphereR[0]);
	printf("Sphere[1]: %.2f, %.2f, %.2f (r:%.2f)\n", m->v_sphere[1].x, m->v_sphere[1].y, m->v_sphere[1].z, m->sphereR[1]);
	printf("Sphere[2]: %.2f, %.2f, %.2f (r:%.2f)\n", m->v_sphere[2].x, m->v_sphere[2].y, m->v_sphere[2].z, m->sphereR[2]);
	printf("Sphere[3]: %.2f, %.2f, %.2f (r:%.2f)\n", m->v_sphere[3].x, m->v_sphere[3].y, m->v_sphere[3].z, m->sphereR[3]);
	printf("Sphere[4]: %.2f, %.2f, %.2f (r:%.2f)\n", m->v_sphere[4].x, m->v_sphere[4].y, m->v_sphere[4].z, m->sphereR[4]);
	for (int i = 0; i < m->light_count; i++)
		printf("Light[%d] : %.2f, %.2f, %.2f\n", i, m->v_light[i].x, m->v_light[i].y, m->v_light[i].z);

	printf("kAmb     : %.2f, %.2f, %.2f\n", m->kAmb.r, m->kAmb.g, m->kAmb.b);
	printf("kDif     : %.2f, %.2f, %.2f\n", m->kDif.r, m->kDif.g, m->kDif.b);
	printf("kSpe     : %.2f, %.2f, %.2f\n", m->kSpe.r, m->kSpe.g, m->kSpe.b);

	printf("shininess       : %.2f\n", m->shininess);

	for (int i = 0; i < m->light_count; i++)
		printf("lightIntensity[%d]  : %.2f\n", i, m->lightIntensity[i]);
	printf("ambientIntensity: %.2f\n", m->ambientIntensity);
	printf("obj_count       : %d\n", m->obj_count);
	for (int i = 0; i < m->obj_count; i++)
	{
		printf("[%d] ", i);
		if (m->obj_type[i] == CMD_SPHERE)
		{
			printf("Sphere");
			printf(": %.2f, %.2f, %.2f (r:%.2f) / rgb:%.2f %.2f %.2f\n",
					((t_sphere *)m->obj[i])->center.x,
					((t_sphere *)m->obj[i])->center.y,
					((t_sphere *)m->obj[i])->center.z,
					((t_sphere *)m->obj[i])->diameter,
					((t_sphere *)m->obj[i])->rgb.r,
					((t_sphere *)m->obj[i])->rgb.g,
					((t_sphere *)m->obj[i])->rgb.b);
		}
		else if (m->obj_type[i] == CMD_PLANE)
		{
			printf("Plane");
			printf(": %.2f, %.2f, %.2f / %.2f, %.2f, %.2f / rgb:%.2f %.2f %.2f\n",
					((t_plane *)m->obj[i])->normal.x,
					((t_plane *)m->obj[i])->normal.y,
					((t_plane *)m->obj[i])->normal.z,
					((t_plane *)m->obj[i])->position.x,
					((t_plane *)m->obj[i])->position.y,
					((t_plane *)m->obj[i])->position.z,
					((t_plane *)m->obj[i])->rgb.r,
					((t_plane *)m->obj[i])->rgb.g,
					((t_plane *)m->obj[i])->rgb.b);
		}
		else if (m->obj_type[i] == CMD_SQUARE)
		{
			printf("Square");
			printf(": %.2f, %.2f, %.2f / %.2f, %.2f, %.2f / %.2f / rgb:%.2f %.2f %.2f\n",
					((t_square *)m->obj[i])->center.x,
					((t_square *)m->obj[i])->center.y,
					((t_square *)m->obj[i])->center.z,
					((t_square *)m->obj[i])->orientation.x,
					((t_square *)m->obj[i])->orientation.y,
					((t_square *)m->obj[i])->orientation.z,
					((t_square *)m->obj[i])->sidesize,
					((t_square *)m->obj[i])->rgb.r,
					((t_square *)m->obj[i])->rgb.g,
					((t_square *)m->obj[i])->rgb.b);
		}
		else if (m->obj_type[i] == CMD_CYLINDER)
		{
			printf("Cylinder");
			printf(": %.2f, %.2f, %.2f / %.2f, %.2f, %.2f / %.2f / %.2f / rgb:%.2f %.2f %.2f\n",
					((t_cylinder *)m->obj[i])->center.x,
					((t_cylinder *)m->obj[i])->center.y,
					((t_cylinder *)m->obj[i])->center.z,
					((t_cylinder *)m->obj[i])->orientation.x,
					((t_cylinder *)m->obj[i])->orientation.y,
					((t_cylinder *)m->obj[i])->orientation.z,
					((t_cylinder *)m->obj[i])->diameter,
					((t_cylinder *)m->obj[i])->height,
					((t_cylinder *)m->obj[i])->rgb.r,
					((t_cylinder *)m->obj[i])->rgb.g,
					((t_cylinder *)m->obj[i])->rgb.b);
		}
		else if (m->obj_type[i] == CMD_TRIANGLE)
		{
			printf("Triangle");
			printf(": %.2f, %.2f, %.2f / %.2f, %.2f, %.2f / %.2f, %.2f, %.2f / rgb:%.2f %.2f %.2f\n",
					((t_triangle *)m->obj[i])->first.x,
					((t_triangle *)m->obj[i])->first.y,
					((t_triangle *)m->obj[i])->first.z,
					((t_triangle *)m->obj[i])->second.x,
					((t_triangle *)m->obj[i])->second.y,
					((t_triangle *)m->obj[i])->second.z,
					((t_triangle *)m->obj[i])->third.x,
					((t_triangle *)m->obj[i])->third.y,
					((t_triangle *)m->obj[i])->third.z,
					((t_triangle *)m->obj[i])->rgb.r,
					((t_triangle *)m->obj[i])->rgb.g,
					((t_triangle *)m->obj[i])->rgb.b);
		}
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

void	freeX(t_map *m)
{
	int		i;

	i = 0;
	while (i < m->obj_count)
	{
		free(m->obj[i]);
		m->obj[i] = NULL;
		i++;
	}
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
