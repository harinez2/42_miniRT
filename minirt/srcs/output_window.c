#include	"main.h"

void	calc_distance_cam_scr(t_map *m)
{
	double	tan_theta_div_two;

	if (m->dsp)
		ft_vecprint_with_name("  curr_cam.orien            ", &m->curr_cam.orien);
	tan_theta_div_two = (double)tan(ft_degree_to_rad(m->curr_cam.fov) / 2);
	if (m->dsp)
		printf("  tan_theta_div_two          : %.2f\n", tan_theta_div_two);
	m->scr.distance_cam_scr = (double)m->window_x / tan_theta_div_two / 2;
	if (m->dsp)
		printf("  distance_cam_scr           : %.2f\n", m->scr.distance_cam_scr);
}

// unitvec x is a unit vector which the z-axis vec is zero.
void	calc_screen_unitvec_x(t_map *m)
{
	if (m->curr_cam.orien.x == 0 && m->curr_cam.orien.y >= 0)
		m->scr.unitvec_scrx = ft_vec(1, 0, 0);
	else if (m->curr_cam.orien.x == 0 && m->curr_cam.orien.y < 0)
		m->scr.unitvec_scrx = ft_vec(-1, 0, 0);
	else if (m->curr_cam.orien.y == 0 && m->curr_cam.orien.x > 0)
		m->scr.unitvec_scrx = ft_vec(0, -1, 0);
	else if (m->curr_cam.orien.y == 0 && m->curr_cam.orien.x < 0)
		m->scr.unitvec_scrx = ft_vec(0, 1, 0);
	else
	{
		m->scr.unitvec_scrx.x = 1;
		m->scr.unitvec_scrx.y
			= -1 * (m->curr_cam.orien.x * m->scr.unitvec_scrx.x) / m->curr_cam.orien.y;
		m->scr.unitvec_scrx.z = 0;
	}
	if (m->dsp)
		ft_vecprint_with_name("  unitvec_scrx              ", &m->scr.unitvec_scrx);
	m->scr.unitvec_scrx = ft_vecnormalize(m->scr.unitvec_scrx);
	if (m->dsp)
		ft_vecprint_with_name("  unitvec_scrx(normalized)  ", &m->scr.unitvec_scrx);
}

// unitvec y is a unit vector which the x-axis vec is zero.
void	calc_screen_unitvec_y(t_map *m)
{
	if (m->curr_cam.orien.z == 0)
		m->scr.unitvec_scry = ft_vec(0, 0, 1);
	else
		m->scr.unitvec_scry = ft_veccrossprod(m->scr.unitvec_scrx, m->curr_cam.orien);
	if (m->dsp)
		ft_vecprint_with_name("  unitvec_scry              ", &m->scr.unitvec_scry);
	m->scr.unitvec_scry = ft_vecnormalize(m->scr.unitvec_scry);
	if (m->dsp)
		ft_vecprint_with_name("  unitvec_scry(normalized)  ", &m->scr.unitvec_scry);
}

static void	put_pixel_based_on_ray(t_map *m, int  x, int y)
{
	t_vec		v_w;
	t_color		color;
	const int	print_foreach = 100;

	v_w.x = m->curr_cam.orien.x * m->scr.distance_cam_scr
		+ (x - m->window_x / 2) * m->scr.unitvec_scrx.x 
		+ (y - m->window_y / 2) * m->scr.unitvec_scry.x;
	v_w.y = m->curr_cam.orien.y * m->scr.distance_cam_scr
		+ (x - m->window_x / 2) * m->scr.unitvec_scrx.y
		+ (y - m->window_y / 2) * m->scr.unitvec_scry.y;
	v_w.z = m->curr_cam.orien.z * m->scr.distance_cam_scr
		+ (x - m->window_x / 2) * m->scr.unitvec_scrx.z
		+ (y - m->window_y / 2) * m->scr.unitvec_scry.z;
	color = decide_color_with_raytracing(v_w, m);
	mlx_pixel_put(m->mlx, m->win, x, y, ft_color(color.r, color.g, color.b));
	if (m->dsp && x % print_foreach == 0 && y % print_foreach == 0)
	{
		if (x == 0)
			printf("\n");
		printf("  v_w : ");
		ft_vecprint(&v_w);
		printf("  /  %.2f, %.2f, %.2f\n", color.r, color.g, color.b);
	}
}

int	draw_map_on_window(t_map *m)
{
	int		x;
	int		y;

	y = 0;
	while (y < m->window_y)
	{
		x = 0;
		while (x < m->window_x)
		{
			put_pixel_based_on_ray(m, x, y);
			x++;
		}
		y++;
	}
	return (0);
}

static void	shrink_window_max_size(t_map *m)
{
	int		screen_x;
	int		screen_y;

	mlx_get_screen_size(m->mlx, &screen_x, &screen_y);
	if (m->dsp)
		printf("  screen_x:%d, screen_y:%d\n", screen_x, screen_y);
	if (m->window_x > screen_x)
		m->window_x = screen_x;
	if (m->window_y > screen_y)
		m->window_y = screen_y;
}

void	display_window(t_map *m)
{
	if (m->dsp)
		printf(">>>>> Displaying window...\n");
	m->mlx = mlx_init();
	if (!(m->mlx))
		print_error_exit(ERR_WND_MLXINIT, m);
	if (m->dsp)
		printf("  Mlx init OK (use_xshm:%d, pshm_format:%d).\n",
			((t_xvar *)m->mlx)->use_xshm, ((t_xvar *)m->mlx)->pshm_format);
	shrink_window_max_size(m);
	m->win = mlx_new_window(m->mlx, m->window_x, m->window_y, "miniRT");
	if (!(m->win))
		print_error_exit(ERR_WND_WNDINIT, m);
	if (m->dsp)
		printf("  Window creation OK.\n  Drawing objects ...\n");
	draw_map_on_window(m);
	mlx_key_hook(m->win, keypress_handler, m);
	mlx_hook(m->win, 33, 0, (void *)close_win_hanlder, m);
	mlx_loop(m->mlx);
}
