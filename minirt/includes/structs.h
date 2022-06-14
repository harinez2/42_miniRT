#ifndef STRUCTS_H
# define STRUCTS_H

// Primitive values ************************************************

typedef struct s_vec
{
	double		x;
	double		y;
	double		z;
}	t_vec;

typedef struct s_color
{
	double	r;
	double	g;
	double	b;
}	t_color;

typedef struct s_camera
{
	t_vec	pos;
	t_vec	orien;
	double	fov;
}	t_camera;

typedef struct s_light
{
	t_vec	pos;
	double	itsty;
	t_color	rgb;
}	t_light;

typedef struct s_screen
{
	double		distance_cam_scr;
	t_vec		unitvec_scrx;
	t_vec		unitvec_scry;
}	t_screen;

typedef struct s_curr_cam_dir
{
	t_vec	v_w;
	t_vec	v_de;
	t_vec	v_tpos;
	t_vec	v_tpos_norm;
}	t_curr_cam_dir;

// Map data ***************************************************

// ambItsty		Ialpha / ambient(environment) intensity
// kAmb			reflection coefficient of environment light
// kDif			reflection coefficient of spreading light
// kSpe			reflection coefficient of mirroring light
// shininess	alpha lightness
typedef struct s_map
{
	void			*mlx;
	void			*win;
	void			*image;
	char			*imgdata;
	int				bits_per_pixel;
	int				line_len;
	int				window_x;
	int				window_y;

	int				cam_cnt;
	t_camera		cam[MAX_CAMERA_COUNT];

	int				curr_cam_num;
	t_camera		curr_cam;
	t_screen		scr;
	t_curr_cam_dir	camdir;

	int				lit_cnt;
	t_light			lit[MAX_LIGHT_COUNT];

	double			ambItsty;
	t_color			kAmb;
	t_color			kDif;
	t_color			kSpe;
	double			shininess;

	int				obj_count;
	int				obj_type[MAX_OBJ_COUNT];
	void			*obj[MAX_OBJ_COUNT];

	int				bmp;
	int				dsp;
	int				endian;
}	t_map;

// Calculation structure ******************************************

typedef struct s_minmax
{
	double		min;
	double		max;
}	t_minmax;

typedef struct s_calc_crossing
{
	t_vec		v_de;
	double		A;
	double		B;
	double		C;
	double		D;
	double		t;
}	t_calc_crossing;

typedef struct s_calc_light
{
	t_vec	v_lightDir;
	t_vec	v_n;
	t_vec	refDir;
	t_vec	invEyeDir;
	double	naiseki;
	double	vrDot;
	double	vrDotPow;
}	t_calc_light;

typedef struct s_multivec
{
	t_vec		a;
	t_vec		b;
	t_vec		c;
	t_vec		d;
}	t_multivec;

typedef struct s_multdouble
{
	double		a;
	double		b;
	double		c;
}	t_multdouble;

// Objects ***********************************************************

typedef struct s_sphere
{
	t_vec		center;
	double		diameter;
	t_color		rgb;
}	t_sphere;

// normal		normal(housen) vector
// position		position vector which across the plane
typedef struct s_plane
{
	t_vec		normal;
	t_vec		position;
	t_color		rgb;
}	t_plane;

typedef struct s_cylinder
{
	t_vec		center;
	t_vec		orientation;
	double		diameter;
	double		height;
	t_color		rgb;
	int			secondcrosst_flg;
}	t_cylinder;

typedef struct s_triangle
{
	t_vec		first;
	t_vec		second;
	t_vec		third;
	t_color		rgb;
	t_plane		plane;
}	t_triangle;

typedef struct s_square
{
	t_vec		centr;
	t_vec		orientation;
	double		sidesiz;
	t_color		rgb;
	t_triangle	tr_a;
	t_triangle	tr_b;
}	t_square;

typedef struct s_cone
{
	t_vec		vertex;
	t_vec		normal;
	double		theta;
	t_color		rgb;
}	t_cone;

#endif
