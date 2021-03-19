#ifndef MAIN_H
# define MAIN_H
# include	<unistd.h>
# include	<math.h>
# include	<stdint.h>
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

# define MAX_OBJ_COUNT	200

typedef struct		s_vec
{
	double		x;
	double		y;
	double		z;
}			t_vec;

typedef struct		s_color
{
	double	r;
	double	g;
	double	b;
}			t_color;

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

typedef struct		s_map
{
	int	window_x;
	int	window_y;

	t_vec	v_eye[5];
	t_vec	v_light[5];
	t_plane	pl;
	t_vec	v_sphere[5];
	double	sphereR[5];

	t_color	kAmb; //ka 環境光反射係数
	t_color	kDif; //kd 拡散反射係数
	t_color	kSpe; //ks 鏡面反射係数

	double shininess; //alpha 光沢度
	double ambientIntensity; //Ialpha 環境光の強度
	double lightIntensity; //Ii 光源の光の強度
	
	int	obj_count;
	int	obj_type[MAX_OBJ_COUNT];
	void	*obj[MAX_OBJ_COUNT];
}			t_map;

/* for bmp file
 */
# define FILE_TYPE		0x4D42    /**< "BM"をリトルエンディアンで解釈した値 */
# define FILE_HEADER_SIZE	14 /**< BMPファイルヘッダサイズ */
# define INFO_HEADER_SIZE	40 /**< Windowsヘッダサイズ */
# define DEFAULT_HEADER_SIZE	(FILE_HEADER_SIZE + INFO_HEADER_SIZE)

#pragma pack(2)
typedef struct BITMAPFILEHEADER {
	uint16_t bfType;      /**< ファイルタイプ、必ず"BM" */
	uint32_t bfSize;      /**< ファイルサイズ */
	uint16_t bfReserved1; /**< リザーブ */
	uint16_t bfReserved2; /**< リサーブ */
	uint32_t bfOffBits;   /**< 先頭から画像情報までのオフセット */
}		BITMAPFILEHEADER;

#pragma pack()
typedef struct BITMAPINFOHEADER {
	uint32_t biSize;         /**< この構造体のサイズ */
	int32_t biWidth;         /**< 画像の幅 */
	int32_t biHeight;        /**< 画像の高さ */
	uint16_t biPlanes;       /**< 画像の枚数、通常1 */
	uint16_t biBitCount;     /**< 一色のビット数 */
	uint32_t biCompression;  /**< 圧縮形式 */
	uint32_t biSizeImage;    /**< 画像領域のサイズ */
	int32_t biXPelsPerMeter; /**< 画像の横方向解像度情報 */
	int32_t biYPelsPerMeter; /**< 画像の縦方向解像度情報*/
	uint32_t biClrUsed;      /**< カラーパレットのうち実際に使っている色の個数 */
	uint32_t biClrImportant; /**< カラーパレットのうち重要な色の数 */
}		BITMAPINFOHEADER;

#define COLOR_TYPE_INDEX 0   /**< インデックスカラー方式 */
#define COLOR_TYPE_GRAY  1   /**< グレースケール方式 */
#define COLOR_TYPE_RGB   2   /**< RGB方式 */
#define COLOR_TYPE_RGBA  3   /**< RGBA方式 */

/**
 * @brief 色情報
 * RGBAの色情報を保持する構造体
 */
typedef struct color_t {
	uint8_t r; /**< Red */
	uint8_t g; /**< Green */
	uint8_t b; /**< Blue */
	uint8_t a; /**< Alpha */
}		color_t;

/**
 * @brief 画素情報
 * 共用体になっており、
 * RGBA値、グレースケール、カラーインデックス、のいずれかを表現する。
 * 単体ではどの表現形式になっているかを判断することはできない。
 */
typedef union pixcel_t {
	color_t c; /**< RGBA */
	uint8_t g; /**< グレースケール */
	uint8_t i; /**< カラーインデックス */
}		pixcel_t;

typedef struct image_t {
	uint32_t width;       /**< 幅 */
	uint32_t height;      /**< 高さ */
	uint16_t color_type;  /**< 色表現の種別 */
	uint16_t palette_num; /**< カラーパレットの数 */
	color_t *palette;     /**< カラーパレットへのポインタ */
	pixcel_t **map;       /**< 画像データ */
}	image_t;

double	ft_map(double x, int froma, int fromb, int toa, int tob);

int	readCmd1(int *i, char *line, t_map *m);
int	readCmd2(int *i, char *line, t_map *m);
void	readLine(char *line, t_map *m);
void	readFromFile(char *filename, t_map *m);

int		readInt(int *i, char *line);
double	readDouble(int *i, char *s);
int		readXyz(int *i, char *s, t_vec *v);
int		readRgb(int *i, char *s, t_color *c);
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
