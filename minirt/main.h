#ifndef MAIN_H
# define MAIN_H
# include	<unistd.h>
# include	<math.h>
# include	"mlx.h"
# include	"mlx_int.h"
# include	"../gnl/get_next_line.h"

# define CMD_RESOLUTION	1
# define CMD_AMBIENT	2
# define CMD_CAMERA	3
# define CMD_LIGHT	4
# define CMD_SPHERE	11
# define CMD_PLANE	12
# define CMD_SQUARE	13
# define CMD_CYLINDER	14
# define CMD_TRIANGLE	15

typedef struct		s_vec
{
	double		x;
	double		y;
	double		z;
}			t_vec;

typedef struct		s_map
{
	int	window_x;
	int	window_y;

	t_vec	v_eye[5];
	t_vec	v_light[5];
	t_vec	v_sphere;
	t_vec	v_sphere2;
	double	sphereR;

	double kAmb; //ka 環境光反射係数
	double kDif; //kd 拡散反射係数
	double kSpe; //ks 鏡面反射係数
	double shininess; //alpha 光沢度
	double lightIntensity; //Ii 光源の光の強度
	double ambientIntensity; //Ialpha 環境光の強度
	
	char	objtype[200];
	void	*obj[200];
}			t_map;

/*objects*/
typedef struct		s_sphere
{
	t_vec		center;
	double		diameter;
	int			rgb;
}			t_sphere;

typedef struct		s_plane
{
	t_vec		normal;		//法線ベクトル
	t_vec		position;	//面が通る点の位置ベクトル
	int			rgb;
}			t_plane;

typedef struct		s_square
{
	t_vec		center;
	t_vec		orientation;
	double		sidesize;
	int		rgb;
}			t_square;

typedef struct		s_cylinder
{
	t_vec		center;
	t_vec		orientation;
	double		diameter;
	double		height;
	int		rgb;
}			t_cylinder;

typedef struct		s_triangle
{
	t_vec		first;
	t_vec		second;
	t_vec		third;
	int		rgb;
}			t_triangle;

int	readCmd1(int *i, char *line, t_map *m);
int	readCmd2(int *i, char *line, t_map *m);
void	readLine(char *line, t_map *m);
void	readFromFile(char *filename, t_map *m);

int		readInt(int *i, char *line);
double	readDouble(int *i, char *s);
int		readXyz(int *i, char *s, t_map *m);
int		readRgb(int *i, char *s, t_map *m);
void	skipSep(int *i, char *s);

void	ft_vecset(t_vec *v, double x, double y, double z);
t_vec	ft_vecadd(t_vec v, t_vec w);
t_vec	ft_vecsub(t_vec v, t_vec w);
t_vec	ft_vecmult(t_vec v, double k);
t_vec	ft_vecdiv(t_vec v, double k);

double	ft_vecinnerprod(t_vec v, t_vec w);
double	ft_vecnorm(t_vec v);
double	ft_vecnormsq(t_vec v);
t_vec	ft_vecnormalize(t_vec v);
void	ft_vecprint(t_vec *v);

#endif
