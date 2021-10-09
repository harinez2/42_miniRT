#ifndef STRUCTS_H
# define STRUCTS_H

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

// ambItsty		Ialpha / ambient(environment) intensity
// kAmb			reflection coefficient of environment light
// kDif			reflection coefficient of spreading light
// kSpe			reflection coefficient of mirroring light
// shininess	alpha lightness
typedef struct s_map
{
	void		*mlx;
	void		*win;
	int			window_x;
	int			window_y;

	int			cam_cnt;
	t_camera	cam[MAX_CAMERA_COUNT];

	int			curr_cam_num;
	t_camera	curr_cam;
	double		distance_cam_scr;
	t_vec		v_basevec_scrx;
	t_vec		v_basevec_scry;

	int			lit_cnt;
	t_light		lit[MAX_LIGHT_COUNT];

	double		ambItsty;
	t_color		kAmb;

	t_color		kDif;
	t_color		kSpe;
	double		shininess;

	int			obj_count;
	int			obj_type[MAX_OBJ_COUNT];
	void		*obj[MAX_OBJ_COUNT];

	int			bmp;
	int			dsp;
	int			endian;
}	t_map;

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
	t_vec		center;
	t_vec		orientation;
	double		sidesize;
	t_color		rgb;
	t_triangle	tr_a;
	t_triangle	tr_b;
}	t_square;

// Bitmap ***********************************************************

# pragma pack(2)

//	bfType		file type (must be "BM")
//	bfOffBits	offset between the beginning of the file and image info
typedef struct s_bmp_file_header {
	uint16_t	bfType;
	uint32_t	bfSize;
	uint16_t	bfReserved1;
	uint16_t	bfReserved2;
	uint32_t	bfOffBits;
}	t_bmp_file_header;

# pragma pack()

// biPlanes				num of pic(usually 1)
// biXPelsPerMeter		width resolution
// biYPelsPerMeter		height resolution
// biClrUsed			used color num in color palette
// biClrImportant		important color num in color palette
typedef struct s_bmp_info_header {
	uint32_t	biSize;
	int32_t		biWidth;
	int32_t		biHeight;
	uint16_t	biPlanes;
	uint16_t	biBitCount;
	uint32_t	biCompression;
	uint32_t	biSizeImage;
	int32_t		biXPelsPerMeter;
	int32_t		biYPelsPerMeter;
	uint32_t	biClrUsed;
	uint32_t	biClrImportant;
}	t_bmp_info_header;

// color information of RGBA
typedef struct s_color_rgba {
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;
}	t_color_rgba;

/**
 * @brief pixcel information(union)
 * Show either RGBA, gray scale, or color index.
 * It's impossible to define which expression format is used by itself.
 * c	RGBA
 * g	gray scale
 * i	color index
 */
typedef union u_pixcel {
	t_color_rgba	c;
	uint8_t			g;
	uint8_t			i;
}	t_pixcel;

typedef struct s_image {
	uint32_t		width;
	uint32_t		height;
	uint16_t		color_type;
	uint16_t		palette_num;
	t_color_rgba	*palette;
	t_pixcel		**map;
}	t_image;

#endif
