#ifndef PROTOTYPEDEFS_H
# define PROTOTYPEDEFS_H

void	check_is_allparam_specified(t_map *m);
int		readCmd1(int *i, char *line, t_map *m);
int		readCmd2(int *i, char *line, t_map *m);
int		readLine(char *line, t_map *m);
void	readFromFile(char *filename, t_map *m);

int		readInt(int *i, char *s);
double	readDouble(int *i, char *s);
t_vec	readXyz(int *i, char *s, t_map *m);
t_color	readRgb(int *i, char *s, t_map *m);
void	skipSep(int *i, char *s);

t_vec	ft_vecinit(double x, double y, double z);
void	ft_vecset(t_vec *v, double x, double y, double z);
t_vec	ft_vec(double x, double y, double z);
t_vec	ft_vecadd(t_vec v, t_vec w);
t_vec	ft_vecsub(t_vec v, t_vec w);
t_vec	ft_vecmult(t_vec v, double k);
t_vec	ft_vecdiv(t_vec v, double k);

double	ft_vecinnerprod(t_vec v, t_vec w);
t_vec	ft_veccrossprod(t_vec v, t_vec w);
double	ft_veccrossprod_sign(t_vec v1, t_vec v2, t_vec v3);
double	ft_vecnorm(t_vec v);
double	ft_vecnormsq(t_vec v);
t_vec	ft_vecnormalize(t_vec v);
void	ft_vecprint(t_vec *v);

double	get_nearest_obj(t_vec v_w, t_vec vstart, int i, t_map *m);
t_color	ray_trace_obj(t_vec v_w, t_map *m, int i, double t);
int		get_minimum_t(t_vec v_w, t_vec vstart, t_map *m, double *hit_t);
t_color	decide_color(t_vec v_w, t_map *m);

double	get_nearest_sphere(t_vec v_w, t_vec v_eye, t_sphere *ts);
t_color	ray_trace_sphere(t_vec v_w, t_map *m, t_sphere *ts, double t);
void	print_sphere(t_sphere *ts);

double	get_nearest_plane(t_vec v_w, t_vec v_eye, t_plane *tp);
t_color	ray_trace_plane(t_vec v_w, t_map *m, t_plane *tp, double t);
void	print_plane(t_plane *tp);

void	ft_init_square(t_square *ts);
double	get_nearest_square(t_vec v_w, t_vec v_eye, t_square *ts);
t_color	ray_trace_square(t_vec v_w, t_map *m, t_square *ts, double t);
void	print_square(t_square *ts);

void	ft_init_triangle(t_triangle *tt);
double	get_nearest_triangle(t_vec v_w, t_vec v_eye, t_triangle *tt);
t_color	ray_trace_triangle(t_vec v_w, t_map *m, t_triangle *tt, double t);
void	print_triangle(t_triangle *tt);

double	get_nearest_cylinder(t_vec v_w, t_vec v_eye, t_cylinder *tc);
t_color	ray_trace_cylinder(t_vec v_w, t_map *m, t_cylinder *tc, double t);
void	print_cylinder(t_cylinder *tc);

void	ft_showErrorExit(int errNo, t_map *m);
void	freeX(t_map *m);

void	print_keyname(int key);
int		key_win1(int key, t_map *m);
void	close_win(void);
int		draw_map_wnd(void *mlx, void *win, t_map *m);
void	display_window(t_map *m);

void	set_bmp_header(uint8_t *header_buffer, int stride, t_map *m);
int		draw_map_bmp(FILE *fp, uint8_t *buffer, int stride, t_map *m);
int		write_bmp_simple_stream(FILE *fp, t_map *m);
int		write_bmp(t_map *m);

int		ft_color(int red, int green, int blue);
void	set_color(t_color *c, double red, double green, double blue);
t_color	set_rgb_inrange(t_color c);
void	ft_colorprint(t_color *c);

double	ft_map(double x, int froma, int fromb, int toa, int tob);
void	print_m(t_map *m);
int		decide_endian(void);

#endif
