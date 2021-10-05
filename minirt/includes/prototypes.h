#ifndef PROTOTYPES_H
# define PROTOTYPES_H

// error_clean.c
void		print_error_exit(int errNo, t_map *m);
void		free_map(t_map *m);
// lib_ft.c
void		ft_putstr(const char *s);
// main.c
void		init_m(t_map *m);
void		set_default_value(t_map *m);
int			main(int argc, char **argv);
// obj_cylinder.c
double		get_nearest_cylinder(t_vec v_w, t_vec v_eye, t_cylinder *tc);
t_color		ray_trace_cylinder(t_vec v_w, t_map *m, t_cylinder *tc, double t);
void		print_cylinder(t_cylinder *tc);
// obj_plane.c
double		get_nearest_plane(t_vec v_w, t_vec v_eye, t_plane *tp);
t_color		ray_trace_plane(t_vec v_w, t_map *m, t_plane *tp, double t);
void		print_plane(t_plane *tp);
// obj_sphere.c
double		get_nearest_sphere(t_vec v_w, t_vec v_eye, t_sphere *ts);
double		calc_sphere_diffuse_reflection(t_map *m, t_color *color, t_vec v_tpos, int i, t_sphere *ts);
void		calc_specular_reflection(t_map *m, t_color *color, t_vec v_tpos, int i,
				t_sphere *ts, t_vec v_de);
t_color		ray_trace_sphere(t_vec v_w, t_map *m, t_sphere *ts, double t);
void		print_sphere(t_sphere *ts);
// obj_square.c
void		ft_init_square(t_square *ts);
double		get_nearest_square(t_vec v_w, t_vec v_eye, t_square *ts);
t_color		ray_trace_square(t_vec v_w, t_map *m, t_square *ts, double t);
void		print_square(t_square *ts);
// obj_triangle.c
void		ft_init_triangle(t_triangle *tt);
double		get_nearest_triangle(t_vec v_w, t_vec v_eye, t_triangle *tt);
t_color		ray_trace_triangle(t_vec v_w, t_map *m, t_triangle *tt, double t);
void		print_triangle(t_triangle *tt);
// output_bitmap.c
void		set_bmp_header(uint8_t *header_buffer, int stride, t_map *m);
int			draw_map_bmp(FILE *fp, uint8_t *buffer, int stride, t_map *m);
int			write_bmp_simple_stream(FILE *fp, t_map *m);
int			write_bmp(t_map *m);
// output_window.c
void		print_keyname(int key);
int			key_win1(int key, t_map *m);
void		close_win(void);
int			draw_map_wnd(void *mlx, void *win, t_map *m);
int			draw_map_wnd(void *mlx, void *win, t_map *m);
void		display_window(t_map *m);
// raytracer.c
double		get_nearest_obj(t_vec v_w, t_vec vstart, int i, t_map *m);
t_color		ray_trace_obj(t_vec v_w, t_map *m, int i, double t);
int			get_minimum_t_for_shadow(t_vec v_w, t_vec vstart, t_map *m, double *hit_t);
t_color		decide_color(t_vec v_w, t_map *m);
// reader_file.c
void		read_config_file(char *filename, t_map *m);
// reader_num.c
int			readInt(int *i, char *s);
double		readDouble(int *i, char *s);
t_vec		readXyz(int *i, char *s, t_map *m);
t_color		readRgb(int *i, char *s, t_map *m);
void		skip_separater(int *i, char *line);
// util_color.c
int 	ft_color(int red, int green, int blue);
void		set_color(t_color *c, double red, double green, double blue);
t_color		set_rgb_inrange(t_color c);
void		ft_colorprint(t_color *c);
// util_render.c
double		ft_map(double x, int froma, int fromb, int toa, int tob);
void		print_m(t_map *m);
int			decide_endian(t_map *m);
// util_vec_op1.c
t_vec		ft_vecinit(double x, double y, double z);
void		ft_vecset(t_vec *v, double x, double y, double z);
t_vec		ft_vec(double x, double y, double z);
t_vec		ft_vecadd(t_vec v, t_vec w);
t_vec		ft_vecsub(t_vec v, t_vec w);
t_vec		ft_vecmult(t_vec v, double k);
t_vec		ft_vecdiv(t_vec v, double k);
// util_vec_op2.c
double		ft_vecinnerprod(t_vec v, t_vec w);
t_vec		ft_veccrossprod(t_vec v, t_vec w);
double		ft_veccrossprod_sign(t_vec v1, t_vec v2, t_vec v3);
double		ft_vecnorm(t_vec v);
double		ft_vecnormsq(t_vec v);
t_vec		ft_vecnormalize(t_vec v);
void		ft_vecprint(t_vec *v);

#endif
