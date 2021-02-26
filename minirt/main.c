
#include	<unistd.h>
#include	<math.h>
#include	"mlx.h"
#include	"mlx_int.h"

#define	WIN1_SX		242
#define	WIN1_SY		242
#define	IM1_SX		42
#define	IM1_SY		42
#define	IM3_SX		242
#define	IM3_SY		242

void	*mlx;
void	*win1;
void    *win2;
void    *win3;
void    *im1;
void	*im2;
void	*im3;
void	*im4;
int	bpp1;
int	bpp2;
int	bpp3;
int	bpp4;
int	sl1;
int	sl2;
int	sl3;
int	sl4;
int	endian1;
int	endian2;
int	endian3;
int	endian4;
char	*data1;
char	*data2;
char	*data3;
char	*data4;
int	xpm1_x;
int	xpm1_y;

int	local_endian;

int	color_map_1(void *win,int w,int h);
int	color_map_2(unsigned char *data,int bpp,int sl,int w,int h,int endian, int type);

int	expose_win1(void *p)
{
	(void) p;

	mlx_put_image_to_window(mlx,win1,im3,0,0);
	return (0);
}

int	expose_win2(void *p)
{
	(void) p;

	mlx_put_image_to_window(mlx,win2,im4,0,0);
	mlx_put_image_to_window(mlx,win2,im2,0,0);
	return (0);
}

int	key_win1(int key,void *p)
{
	(void) p;

	printf("Key in Win1 : %d\n",key);
	if (key==0xFF1B)
		exit(0);
	return (0);
}

int	key_win2(int key,void *p)
{
	(void) p;

	printf("Key in Win2 : %d\n",key);
	if (key==0xFF1B)
		exit(0);
	return (0);
}

int	key_win3(int key,void *p)
{
	(void) p;

	printf("Key in Win3 : %d\n",key);
	if (key==0xFF1B)
		mlx_destroy_window(mlx,win3);
	return (0);
}

int	mouse_win1(int button,int x,int y, void *p)
{
	(void) p;

	printf("Mouse in Win1, button %d at %dx%d.\n",button,x,y);
	return (0);
}

int	mouse_win2(int button,int x,int y, void *p)
{
	(void) p;

	printf("Mouse in Win2, button %d at %dx%d.\n",button,x,y);
	return (0);
}

int	mouse_win3(int x,int y, void *p)
{
	(void) p;

	printf("Mouse moving in Win3, at %dx%d.\n",x,y);
	return (0);
}

/*
** Vector funcs
**/
typedef struct		s_vec
{
	double		x;
	double		y;
	double		z;
}			t_vec;

void	ft_vecset(t_vec *v, double x, double y, double z)
{
	v->x = x;
	v->y = y;
	v->z = z;
}

t_vec	ft_vecadd(t_vec v, t_vec w)
{
	t_vec ret;

	ret.x = v.x + w.x;
	ret.y = v.y + w.y;
	ret.z = v.z + w.z;
	return (ret);
}

t_vec	ft_vecsub(t_vec v, t_vec w)
{
	t_vec ret;

	ret.x = v.x - w.x;
	ret.y = v.y - w.y;
	ret.z = v.z - w.z;
	return (ret);
}

/* Multiply of scalar
*/
t_vec	ft_vecmult(t_vec v, int k)
{
	t_vec ret;

	ret.x = v.x * k;
	ret.y = v.y * k;
	ret.z = v.z * k;
	return (ret);
}

/* Divided by scalar
*/
t_vec	ft_vecdiv(t_vec v, double k)
{
	t_vec ret;

	ret.x = v.x / k;
	ret.y = v.y / k;
	ret.z = v.z / k;
	return (ret);
}

/* Inner product
*/
double	ft_vecinnerprod(t_vec v, t_vec w)
{
	double	ret;

	ret = v.x * w.x;
	ret += v.y * w.y;
	ret += v.z * w.z;
	return (ret);
}

/* Norm (length of the vec)
*/
double	ft_vecnorm(t_vec v)
{
	double	ret;

	ret = v.x * v.x;
	ret += v.y * v.y;
	ret += v.z * v.z;
	return (sqrt(ret));
}

/* Norm square (norm is the length of the vec)
*/
double	ft_vecnormsq(t_vec v)
{
	double	ret;

	ret = v.x * v.x;
	ret += v.y * v.y;
	ret += v.z * v.z;
	return (ret);
}

void	ft_vecprint(t_vec *v)
{
	printf("[vector] (%f, %f, %f)\n", v->x, v->y, v->z);
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

int	decide_color(t_vec v_w, t_vec v_eye, t_vec v_sphere, double sphereR, t_vec v_light, double lightIntensity, double ambientIntensity)
{
	t_vec	v_de;
	t_vec	v_tmp;
	int	color;
	
	double kAmb = 0.01;
	double kDif = 0.69;
	double kSpe = 0.3;
	double shininess = 8;

	v_de = ft_vecsub(v_w, v_eye);
	v_tmp = ft_vecsub(v_eye, v_sphere);
	double A = ft_vecnormsq(v_de);
	double B = 2 * ft_vecinnerprod(v_de, v_tmp);
	double C = ft_vecnormsq(v_tmp) - sphereR * sphereR;
	double D = B * B - 4 * A * C;
	double t = -1;

	if (D == 0)
		t = -B / (2 * A);
	else if (D > 0)
	{
		double t1 = (-B - sqrt(D)) / (2 * A);
		double t2 = (-B + sqrt(D)) / (2 * A);
		t = t1 > 0 && t2 > 0 ? fmin(t1, t2) : fmax(t1, t2);
	}

	color = ft_color(255, 255, 255);
	if (t >= 0)
	{
		double radianceAmb = kAmb * ambientIntensity;

		t_vec v_tpos = ft_vecadd(v_eye, ft_vecmult(v_de, t));

		t_vec v_lightDir = ft_vecsub(v_light, v_tpos);
		v_lightDir = ft_vecdiv(v_lightDir, ft_vecnorm(v_lightDir));
		
		t_vec v_sphereN = ft_vecsub(v_tpos, v_sphere);
		v_sphereN = ft_vecdiv(v_sphereN, ft_vecnorm(v_sphereN));

		double naiseki = ft_vecinnerprod(v_sphereN, v_lightDir);
//printf("%.2f ", naiseki);
		double nlDot = 0;
		if (naiseki > 0)
			nlDot = ft_map(naiseki, 0, 1, 0, 255);
		else
			nlDot = ft_map(0, 0, 1, 0, 255);
//printf("%.2f ", nlDot);
		double radianceDif = kDif * lightIntensity * naiseki;
		double radianceSpe = 0.0f;
		if (nlDot > 0)
		{
			t_vec refDir = ft_vecsub(ft_vecmult(v_sphereN, 2 * naiseki), v_lightDir); 
			t_vec invEyeDir = ft_vecmult(v_de, -1);
			double vrDot = ft_vecinnerprod(invEyeDir, refDir);
			radianceSpe = kSpe * lightIntensity * pow(vrDot, shininess);
		}

		double rSum = radianceAmb + radianceDif + radianceSpe;
		color = ft_color(rSum, 0, 0);
		//color = ft_color(nlDot, 0, 0);
	}
	return (color);
}

/*
** Sphere
**/
int	draw_sphere(void *win, int w, int h)
{
	int	x;
	int	y;
	t_vec	v_eye;
	t_vec	v_sphere;
	t_vec	v_light;
	t_vec	v_w;
	double	sphereR;
	int	color;

	ft_vecset(&v_eye, 0, 0, -5);
	ft_vecset(&v_sphere, 0, 0, 5);
	ft_vecset(&v_light, -5, 5, -5);
	sphereR = 1.0;
	double lightIntensity = 1.0;
	double ambientIntensity = 0.1;

	v_w.z = 0;
	y = 0;
	while (y < h)
	{
		v_w.y = ft_map(y, 0, h-1, 1, -1);
		x = 0;
		while (x < w)
		{
			v_w.x = ft_map(x, 0, w-1, -1, 1);
			color = decide_color(v_w, v_eye, v_sphere, sphereR, v_light, lightIntensity, ambientIntensity);
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
int	main()
{
	decide_endian();

	if (!(mlx = mlx_init()))
	{
		write(1, "Error\nInitialization failed.\n", 29);
		exit(1);
	}
	printf("Mlx init OK (use_xshm:%d, pshm_format:%d).\n",((t_xvar *)mlx)->use_xshm,((t_xvar *)mlx)->pshm_format);

	printf("Window1 creation: %dx%d \"Title 1\" ...",WIN1_SX,WIN1_SY);
	if (!(win1 = mlx_new_window(mlx,WIN1_SX,WIN1_SY,"Title1")))
	{
		printf(" !! KO !!\n");
		exit(1);
	}
	printf("OK\n");

	printf("Drawing sphere ...");
	draw_sphere(win1,WIN1_SX,WIN1_SY);
	printf("OK\n");
	mlx_key_hook(win1,key_win1,0);
	mlx_loop(mlx);
	//sleep(2);
	exit(0);



	sleep(2);

	printf(" => Clear Window ...");
	mlx_clear_window(mlx,win1);
	printf("OK\n");
	sleep(2);

	printf(" => Image1 ZPixmap %dx%d ...",IM1_SX,IM1_SY);
	if (!(im1 = mlx_new_image(mlx,IM1_SX,IM1_SY)))
	{
		printf(" !! KO !!\n");
		exit(1);
	}
	data1 = mlx_get_data_addr(im1,&bpp1,&sl1,&endian1);
	printf("OK (bpp1: %d, sizeline1: %d endian: %d type: %d)\n",bpp1,sl1,endian1,
		((t_img *)im1)->type);

	printf(" => Fill Image1 ...");
	color_map_2((unsigned char *)data1,bpp1,sl1,IM1_SX,IM1_SY,endian1, 1);
	printf("OK (pixmap : %d)\n",(int)((t_img *)im1)->pix);

	printf(" => Put Image1 ...");
	mlx_put_image_to_window(mlx,win1,im1,20,20);
	printf("OK\n");
	sleep(2);

	printf(" => Destroy Image1 ... ");
	mlx_destroy_image(mlx, im1);
	printf("OK\n");
	sleep(2);

	printf(" => Image3 ZPixmap %dx%d ...",IM3_SX,IM3_SY);
	if (!(im3 = mlx_new_image(mlx,IM3_SX,IM3_SY)))
	{
		printf(" !! KO !!\n");
		exit(1);
	}
	data3 = mlx_get_data_addr(im3,&bpp3,&sl3,&endian3);
	printf("OK (bpp3 %d, sizeline3 %d endian3 %d type %d)\n",bpp3,sl3,endian3,
		((t_img *)im3)->type);

	printf(" => Fill Image3 ...");
	color_map_2((unsigned char *)data3,bpp3,sl3,IM3_SX,IM3_SY,endian3, 1);
	printf("OK (pixmap : %d)\n",(int)((t_img *)im3)->pix);

	printf(" => Put Image3 ...");
	mlx_put_image_to_window(mlx,win1,im3,20,20);
	printf("OK\n");
	sleep(2);

	printf(" => String ...");
	mlx_string_put(mlx,win1,5,WIN1_SY/2,0xFF99FF,"String output");
	mlx_string_put(mlx,win1,15,WIN1_SY/2+20,0x00FFFF,"MinilibX test");
	printf("OK\n");
	sleep(2);

	printf(" => Xpm from file ...");
	if (!(im2 = mlx_xpm_file_to_image(mlx,"open.xpm",&xpm1_x,&xpm1_y)))
	{
		printf(" !! KO !!\n");
		exit(1);
	}
	data2 = mlx_get_data_addr(im2,&bpp2,&sl2,&endian2);
	printf("OK (xpm %dx%d)(img bpp2: %d, sizeline2: %d endian: %d type: %d)\n",
		xpm1_x,xpm1_y,bpp2,sl2,endian2,((t_img *)im2)->type);
	sleep(2);

	printf(" => Put xpm ...");
	mlx_put_image_to_window(mlx,win1,im2,0,0);
	mlx_put_image_to_window(mlx,win1,im2,100,100);
	printf("OK\n");
	sleep(2);

	printf(" => 2nd window,");
	win2 = mlx_new_window(mlx,WIN1_SX,WIN1_SY,"Title2");
	if (!(im4 = mlx_new_image(mlx,IM3_SX, IM3_SY)))
	{
		printf(" !! KO !!\n");
		exit(1);
	}
	data4 = mlx_get_data_addr(im4,&bpp4,&sl4,&endian4);
	color_map_2((unsigned char *)data4,bpp4,sl4,IM3_SX,IM3_SY,endian4, 2);

	printf(" 3rd window, Installing hooks ...");
	win3 = mlx_new_window(mlx,WIN1_SX,WIN1_SY,"Title3");
	mlx_expose_hook(win1,expose_win1,0);
	mlx_mouse_hook(win1,mouse_win1,0);
	mlx_key_hook(win1,key_win1,0);
	mlx_expose_hook(win2,expose_win2,0);
	mlx_mouse_hook(win2,mouse_win2,0);
	mlx_key_hook(win2,key_win2,0);
	mlx_key_hook(win3,key_win3,0);

	mlx_hook(win3, MotionNotify, PointerMotionMask, mouse_win3, 0);

	printf("OK\nNow in Loop. Just play. Esc in 3 to destroy, 1&2 to quit.\n");

	mlx_loop(mlx);
}

int	color_map_1(void *win,int w,int h)
{
	int	x;
	int	y;
	int	color;

	x = 0;
	while (x < w)
	{
		y = 0;
		while (y < h)
		{
			color = (x*255)/w+((((w-x)*255)/w)<<16)+(((y*255)/h)<<8);
			mlx_pixel_put(mlx,win,x,y,color);
			y++;
		}
		x++;
	}
	return (0);
}

int	color_map_2(unsigned char *data,int bpp,int sl,int w,int h,int endian, int type)
{
	int	x;
	int	y;
	int	opp;
	int	dec;
	int	color;
	int	color2;
	unsigned char *ptr;

	opp = bpp/8;
	printf("(opp : %d) ",opp);
	y = h;
	while (y--)
	{
		ptr = data+y*sl;
		x = w;
		while (x--)
		{
			if (type==2)
				color = (y*255)/w+((((w-x)*255)/w)<<16)+(((y*255)/h)<<8);
			else
				color = (x*255)/w+((((w-x)*255)/w)<<16)+(((y*255)/h)<<8);
			color2 = mlx_get_color_value(mlx,color);
			dec = opp;
			while (dec--)
			{
				if (endian==local_endian)
				{
					if (endian)
						*(ptr+x*opp+dec) = ((unsigned char *)(&color2))[4-opp+dec];
					else
						*(ptr+x*opp+dec) = ((unsigned char *)(&color2))[dec];
				}
				else
				{
					if (endian)
						*(ptr+x*opp+dec) = ((unsigned char *)(&color2))[opp-1-dec];
					else
						*(ptr+x*opp+dec) = ((unsigned char *)(&color2))[3-dec];
				}
			}
		}
	}
	return (0);
}
