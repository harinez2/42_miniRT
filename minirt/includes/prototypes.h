/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonishi <yonishi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 17:41:17 by yonishi           #+#    #+#             */
/*   Updated: 2022/06/18 17:41:17 by yonishi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPES_H
# define PROTOTYPES_H

// error_clean.c
void		print_error_exit(int errNo, t_map *m);
// main.c
int			main(int argc, char **argv);
// map.c
void		init_map(t_map *m);
void		arrange_constant_values(t_map *m);
void		free_map(t_map *m);
// map_print.c
void		print_m(t_map *m);
// map_print_objs.c
void		print_cylinder(t_cylinder *tc);
void		print_plane(t_plane *tp);
void		print_sphere(t_sphere *ts);
void		print_square(t_square *ts);
void		print_triangle(t_triangle *tt);
// map_print_objs2d.c
void		print_cone(t_cone *tc);
// obj_cone.c
t_color		get_color_by_rt_cone(t_map *m, int hit_i, t_cone *tc);
// obj_cone_getdistance.c
double		get_distance_to_cone(
				t_vec v_from, t_vec v_to, t_map *m, t_cone *tc);
// obj_cylinder.c
t_color		get_color_by_rt_cylinder(t_map *m, int hit_i, t_cylinder *tc);
// obj_cylinder_getdistance.c
double		get_distance_to_cylinder(
				t_vec v_from, t_vec v_to, t_map *m, t_cylinder *tc);
// obj_plane.c
double		get_distance_to_plane(
				t_vec v_from, t_vec v_to, t_map *m, t_plane *tp);
t_color		get_color_by_rt_plane(t_map *m, int hit_i, t_plane *tp);
// obj_sphere.c
double		get_distance_to_sphere(
				t_vec v_from, t_vec v_to, t_map *m, t_sphere *ts);
t_color		get_color_by_rt_sphere(t_map *m, int hit_i, t_sphere *ts);
// obj_square.c
void		ft_init_square(t_square *ts);
double		get_distance_to_square(
				t_vec v_from, t_vec v_to, t_map *m, t_square *ts);
t_color		get_color_by_rt_square(t_map *m, int hit_i, t_square *ts);
// obj_triangle.c
void		ft_init_triangle(t_triangle *tt);
double		get_distance_to_triangle(
				t_vec v_from, t_vec v_to, t_map *m, t_triangle *tt);
t_color		get_color_by_rt_triangle(t_map *m, int hit_i, t_triangle *tt);
// obj_util.c
void		set_ambient_reflection_color(t_map *m, t_color *color);
t_color		adjust_color_level(t_color *base_color, double innprod);
void		add_diffuse_reflection_color(
				t_map *m, int lit_i, t_color *color, t_color *add_color);
void		add_specular_reflection_color(
				t_map *m, int lit_i, t_color *color, t_color *add_color);
double		calc_minimum_t(double A, double B, double D);
// output_bitmap.c
int			write_bmp(t_map *m);
// output_window.c
int			draw_map_on_window(t_map *m);
void		display_window(t_map *m);
// output_window_handler.c
int			keypress_handler(int key, t_map *m);
void		close_win_hanlder(t_map *m, int called_by);
// readfile.c
void		read_config_file(char *filename, t_map *m);
// readfile_config.c
int			read_file_resolution(int *i, char *line, t_map *m);
int			read_file_ambient(int *i, char *line, t_map *m);
// readfile_config_camera.c
int			read_file_camera(int *i, char *line, t_map *m);
// readfile_config_light.c
int			read_file_light(int *i, char *line, t_map *m);
// readfile_num.c
int			read_int(int *i, char *s, t_map *m);
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
// readfile_objs2d.c
int			read_file_cone(int *i, char *line, t_map *m);
// readfile_validate.c
int			is_eol(int *i, char *line);
int			is_normalized(t_vec *v);
void		validate_parameters(t_map *m);
// screen_init.c
void		init_screen_values(t_map *m);
// screen_raytrace.c
int			get_minimum_distance_to_obj(
				t_vec v_from, t_vec v_to, t_map *m, double *hit_t);
t_color		get_color_on_screen(t_map *m, int x, int y);
// util_color.c
int			ft_color(int red, int green, int blue);
void		set_color(t_color *c, double red, double green, double blue);
t_color		set_rgb_inrange(t_color c);
void		ft_colorprint(t_color *c);
// util_lib.c
int			ft_strncmp(char *s1, char *s2, unsigned int n);
int			is_whitespace(const char c);
int			ft_atoll(char *s, long long *retnum, int *neg_flg);
// util_lib_mem.c
void		*ft_memset(void *b, int c, size_t n);
void		*ft_memcpy(void *dst, const void *src, size_t n);
// util_print.c
void		printerr(const char *msg);
// util_render.c
double		adjust_range(double x, t_minmax from, t_minmax to);
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
