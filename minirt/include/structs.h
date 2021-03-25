#ifndef STRUCTS_H
# define STRUCTS_H

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
	t_color		rgb;
}			t_sphere;

typedef struct		s_plane
{
	t_vec		normal;		//法線ベクトル
	t_vec		position;	//面が通る点の位置ベクトル
	t_color		rgb;
}			t_plane;

typedef struct		s_cylinder
{
	t_vec		center;
	t_vec		orientation;
	double		diameter;
	double		height;
	t_color		rgb;
}			t_cylinder;

typedef struct		s_triangle
{
	t_vec		first;
	t_vec		second;
	t_vec		third;
	t_color		rgb;
	t_plane		plane;
}			t_triangle;

typedef struct		s_square
{
	t_vec		center;
	t_vec		orientation;
	double		sidesize;
	t_color		rgb;
	t_triangle	tr_a;
	t_triangle	tr_b;
}			t_square;

typedef struct		s_map
{
	void	*mlx;
	void	*win;
	int	window_x;
	int	window_y;

	int	eye_count;
	int	ceye_num;
	t_vec	v_ceye;
	t_vec	v_eye[MAX_CAMERA_COUNT];
	t_vec	v_eye_orientation[MAX_CAMERA_COUNT];
	double	eye_fov[MAX_CAMERA_COUNT];

	int	light_count;
	t_vec	v_light[MAX_LIGHT_COUNT];
	double	light_brightness[MAX_LIGHT_COUNT];
	t_color	light_rgb[MAX_LIGHT_COUNT];

	t_color	kAmb; //ka 環境光反射係数
	t_color	kDif; //kd 拡散反射係数
	t_color	kSpe; //ks 鏡面反射係数

	double shininess; //alpha 光沢度
	double ambItsty; //Ialpha 環境光の強度(ambient intensity)
	double lightItsty[MAX_LIGHT_COUNT]; //Ii 光源の光の強度
	
	int	obj_count;
	int	obj_type[MAX_OBJ_COUNT];
	void	*obj[MAX_OBJ_COUNT];
}			t_map;

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

#endif
