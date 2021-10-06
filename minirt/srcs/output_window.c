#include	"main.h"

// memo: 45deg = PI / 4.0
//       tan(PI / 4.0) == 1
int	draw_map_on_window(t_map *m)
{
	double	scr_width;
	//double	scr_height;
	double	distance_cam_scr;
	int		x;
	int		y;
	t_vec	v_w;
	t_color	color;
	t_vec	C;
	t_vec	U;
	t_vec	V;

	scr_width = 2;
	// scr_height = scr_width * m->window_y / m->window_x;

	//printf("  tan: %.2f\n", (double)tan(PI * m->eye_fov[m->ceye_num] / 2 / 180));
	// printf("  d: %.2f\n", scr_width / (double)tan(PI * m->eye_fov[m->ceye_num] / 2 / 180) / 2);
	distance_cam_scr = scr_width / (double)tan(PI * m->eye_fov[m->ceye_num] / 180 / 2) / 2;
	printf("  d: %.2f\n", distance_cam_scr);

	printf("  m->v_corientation: ");
	ft_vecprint(&m->v_corientation);
	printf("\n");

	C = ft_vecmult(m->v_corientation, distance_cam_scr);
	printf("  C: ");
	ft_vecprint(&C);
	printf("\n");

	// double cxcy = (double)sqrtl(C.x * C.x + C.y * C.y);
	// printf("cxcy: %.2f\n", cxcy);

	if (C.x == 0 && C.z >= 0)
	{
		U = ft_vec(1, 0, 0);
		printf("pattern a\n");
	}
	else if (C.x == 0 && C.z < 0)
	{
		U = ft_vec(-1, 0, 0);
		printf("pattern b\n");
	}
	else if (C.z == 0 && C.x > 0)
	{
		U = ft_vec(0, -1, 0);
		printf("pattern c\n");
	}
	else if (C.z == 0 && C.x < 0)
	{
		U = ft_vec(0, 1, 0);
		printf("pattern d\n");
	}
	else
	{
		U.x = 1;
		U.y = 0;
		U.z = -1 * (C.x * U.x) / C.z;
	}
	//ft_vecset(&U, -1 * C.y / cxcy, C.x / cxcy, 0);
	printf("  U: ");
	ft_vecprint(&U);
	printf("\n");

	// U = ft_vecnormalize(U);
	// printf("U(normalized): ");
	// ft_vecprint(&U);
	// printf("\n");

	//ft_vecset(&V, m->v_corientation.y / cxcy, -1 * m->v_corientation.x / cxcy, 0);
	//V = ft_veccrossprod(U, C);
	V = ft_veccrossprod(C, U);
	V = ft_vecnormalize(V);
	printf("  V: ");
	ft_vecprint(&V);
	printf("\n");

	v_w.z = 0;
	y = 0;
	while (y < m->window_y)
	{
		//v_w.y = ft_map(y, 0, m->window_y - 1, 1, -1);
		double ypos = ft_map(y, 0, m->window_y - 1, 0, 2);
		x = 0;
		while (x < m->window_x)
		{
			//v_w.x = ft_map(x, 0, m->window_x - 1, -1, 1);
			double xpos = ft_map(x, 0, m->window_x - 1, 0, 2);

			// v_w.x = m->v_ceye.x + C.x +
			// 	(x - m->window_x / 2) * U.x - (y - m->window_y / 2) * V.x;
			// v_w.y = m->v_ceye.y + C.y +
			// 	(x - m->window_x / 2) * U.y - (y - m->window_y / 2) * V.y;

			v_w.x = m->v_ceye.x + C.x + xpos * U.x - ypos * V.x;
			v_w.y = m->v_ceye.y + C.y + xpos * U.y - ypos * V.y;

	// printf("v_w: ");
	// ft_vecprint(&v_w);
	// printf("\n");

			color = decide_color(v_w, m);
			mlx_pixel_put(m->mlx, m->win, x, y, ft_color(color.r, color.g, color.b));
			x++;
		}
		y++;
	}
	return (0);
}

/*
int	draw_map_wnd(void *mlx, void *win, t_map *m)
{
	int		x;
	int		y;
	t_vec	v_w;
	t_color	color;

	v_w.z = 0;
	y = 0;
	while (y < m->window_y)
	{
		v_w.y = ft_map(y, 0, m->window_y - 1, 1, -1);
		x = 0;
		while (x < m->window_x)
		{
			v_w.x = ft_map(x, 0, m->window_x - 1, -1, 1);
			color = decide_color(v_w, m);
			mlx_pixel_put(mlx, win, x, y, ft_color(color.r, color.g, color.b));
			x++;
		}
		y++;
	}
	return (0);
}
*/

void	display_window(t_map *m)
{
	if (m->dsp)
		printf(">>>>> Displaying window...\n");
	m->mlx = mlx_init();
	if (!(m->mlx))
		print_error_exit(ERR_WND_MLXINIT, m);
	if (m->dsp)
		printf("Mlx init OK (use_xshm:%d, pshm_format:%d).\n",
			((t_xvar *)m->mlx)->use_xshm, ((t_xvar *)m->mlx)->pshm_format);
	m->win = mlx_new_window(m->mlx, m->window_x, m->window_y, "miniRT");
	if (!(m->win))
		print_error_exit(ERR_WND_WNDINIT, m);
	if (m->dsp)
		printf("Window creation OK.\nDrawing objects ...\n");
	draw_map_on_window(m->mlx, m->win, m);
	mlx_key_hook(m->win, keypress_handler, m);
	mlx_hook(m->win, 33, 0, (void *)close_win_hanlder, m);
	mlx_loop(m->mlx);
}
