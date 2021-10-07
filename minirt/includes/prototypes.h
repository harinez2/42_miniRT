#ifndef PROTOTYPES_H
# define PROTOTYPES_H

// error_clean.c
void		print_error_exit(int errNo, t_map *m);
void		free_map(t_map *m);
// lib_ft.c
int			ft_strncmp(char *s1, char *s2, unsigned int n);
int			is_whitespace(const char c);
int			ft_atoll(char *s, long long *retnum);
// main.c
void		init_m(t_map *m);
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
double		calc_sphere_diffuse_reflection(
				t_map *m, t_color *color, t_vec v_tpos, int i, t_sphere *ts);
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
// obj_util.c
double		calc_t(double A, double B, double D);
// output_bitmap.c
void		set_bmp_header(uint8_t *header_buffer, int stride, t_map *m);
int			draw_map_bmp(FILE *fp, uint8_t *buffer, int stride, t_map *m);
int			write_bmp_simple_stream(FILE *fp, t_map *m);
int			write_bmp(t_map *m);
// output_window.c
int			draw_map_on_window(t_map *m);
void		display_window(t_map *m);
// output_window_handler.c
int			keypress_handler(int key, t_map *m);
void		close_win_hanlder(t_map *m, int called_by);
// raytracer.c
double		get_nearest_obj(t_vec v_w, t_vec vstart, int i, t_map *m);
t_color		ray_trace_obj(t_vec v_w, t_map *m, int i, double t);
int			get_minimum_t_for_shadow(
				t_vec v_w, t_vec vstart, t_map *m, double *hit_t);
t_color		decide_color_with_raytracing(t_vec v_w, t_map *m);
// readfile.c
void		read_config_file(char *filename, t_map *m);
// readfile_config.c
int			read_file_resolution(int *i, char *line, t_map *m);
int			read_file_ambient(int *i, char *line, t_map *m);
int			read_file_camera(int *i, char *line, t_map *m);
int			read_file_light(int *i, char *line, t_map *m);
// readfile_num.c
int			read_int(int *i, char *s);
double		read_double(int *i, char *s, t_map *m);
t_vec		read_xyz(int *i, char *s, t_map *m);
t_color		read_rgb(int *i, char *s, t_map *m);
void		skip_separater(int *i, char *line);
// readfile_objs.c
int			read_file_sphere(int *i, char *line, t_map *m);
int			read_file_plane(int *i, char *line, t_map *m);
int			read_file_square(int *i, char *line, t_map *m);
int			read_file_cylinder(int *i, char *line, t_map *m);
int			read_file_triangle(int *i, char *line, t_map *m);
// util_color.c
int			ft_color(int red, int green, int blue);
void		set_color(t_color *c, double red, double green, double blue);
t_color		set_rgb_inrange(t_color c);
void		ft_colorprint(t_color *c);
// util_print_m.c
void		print_m(t_map *m);
// util_render.c
double		ft_map(double x, int froma, int fromb, int toa, int tob);
int			get_endian(void);
double		ft_degree_to_rad(double degree);
// util_vector.c
t_vec		ft_vecinit(double x, double y, double z);
void		ft_vecset(t_vec *v, double x, double y, double z);
t_vec		ft_vec(double x, double y, double z);
void		ft_vecprint(t_vec *v);
void		ft_vecprint_with_name(char *vecname, t_vec *v);
// util_vector_calc.c
t_vec		ft_vecadd(t_vec v, t_vec w);
t_vec		ft_vecsub(t_vec v, t_vec w);
t_vec		ft_vecmult(t_vec v, double k);
t_vec		ft_vecdiv(t_vec v, double k);
// util_vector_calcprod.c
double		ft_vecinnerprod(t_vec v, t_vec w);
t_vec		ft_veccrossprod(t_vec v, t_vec w);
double		ft_veccrossprod_sign(t_vec v1, t_vec v2, t_vec v3);
// util_vector_normalize.c
double		ft_vecnorm(t_vec v);
double		ft_vecnormsq(t_vec v);
t_vec		ft_vecnormalize(t_vec v);

#endif
