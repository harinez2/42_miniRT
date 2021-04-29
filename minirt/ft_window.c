#include	"main.h"

void	print_keyname(int key)
{
	if (key == 0x63)//c key
		printf("c key");
	else if (key == 0xff52)//Up key
		printf("Up key");
	else if (key == 0xff54)//Down key
		printf("Down key");
	else if (key == 0xff51)//Left key
		printf("Left key");
	else if (key == 0xff53)//Right key
		printf("Right key");
	else if (key == 0x66)//f key
		printf("f key");
	else if (key == 0x62)//b key
		printf("b key");
}

int	key_win1(int key, t_map *m)
{
	//キーコードはxevコマンドで調べる
	if (key == 0xFF1B)//esc
	{
		printf("ESC key pressed.\n");
		exit(0);
	}
	if (key == 0x63)//c key
	{
		m->ceye_num++;
		if (m->ceye_num == m->eye_count)
			m->ceye_num = 0;
		m->v_ceye = m->v_eye[m->ceye_num];
		m->v_corientation = m->v_eye_orientation[m->ceye_num];
	}
	else if (key == 0xff52)//Up key
		m->v_ceye.y = m->v_ceye.y + 1;
	else if (key == 0xff54)//Down key
		m->v_ceye.y = m->v_ceye.y - 1;
	else if (key == 0xff51)//Left key
		m->v_ceye.x = m->v_ceye.x - 1;
	else if (key == 0xff53)//Right key
		m->v_ceye.x = m->v_ceye.x + 1;
	else if (key == 0x66)//f key
		m->v_ceye.z = m->v_ceye.z - 1;
	else if (key == 0x62)//b key
		m->v_ceye.z = m->v_ceye.z + 1;
	else
		return (0);
	print_keyname(key);
	printf(" pressed: cameranum = %d ", m->ceye_num);
	printf("(%.2f, %.2f, %.2f)\n", m->v_ceye.x, m->v_ceye.y, m->v_ceye.z);
	draw_map_wnd(m->mlx, m->win, m);
	return (0);
}

void	close_win()
{
	printf("window close button pressed.\n");
	exit(0);
}

int	draw_map_wnd(void *mlx, void *win, t_map *m)
{
	int		x;
	int		y;
	t_vec	v_w;
	t_color	color;

	printf("\n");
	
	double scr_width = 2;
	double scr_height = scr_width * m->window_y / m->window_x;
	printf("scr_height: %.2f\n", scr_height);

	printf("45deg: %.2f\n", tan(PI/4.0));//45deg
	printf("tan: %.2f\n", (double)tan(PI * m->eye_fov[m->ceye_num] / 2 / 180));
	printf("d: %.2f\n", scr_width / (double)tan(PI * m->eye_fov[m->ceye_num] / 2 / 180) / 2);
	//double d = m->window_x / tan(PI * m->eye_fov[m->ceye_num] / 180 / 2) / 2;
	double d = scr_width / (double)tan(PI * m->eye_fov[m->ceye_num] / 180 / 2) / 2;
	printf("d: %.2f\n", d);

	printf("m->v_corientation: ");
	ft_vecprint(&m->v_corientation);
	printf("\n");
	t_vec C = ft_vecmult(m->v_corientation, d);
	printf("C: ");
	ft_vecprint(&C);
	printf("\n");
	
	double cxcy = (double)sqrtl(C.x * C.x + C.y * C.y);
	printf("cxcy: %.2f\n", cxcy);

	t_vec U;
	if (C.x == 0 && C.y >= 0)
	{
		U = ft_vec(1, 0, 0);
		printf("pattern a\n");
	}
	else if (C.x == 0 && C.y < 0)
	{
		U = ft_vec(-1, 0, 0);
		printf("pattern b\n");
	}
	else if (C.y == 0 && C.x > 0)
	{
		U = ft_vec(0, -1, 0);
		printf("pattern c\n");
	}
	else if (C.y == 0 && C.x < 0)
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
	printf("U: ");
	ft_vecprint(&U);
	printf("\n");


	// U = ft_vecnormalize(U);
	// printf("U(normalized): ");
	// ft_vecprint(&U);
	// printf("\n");

	t_vec V;
	//ft_vecset(&V, m->v_corientation.y / cxcy, -1 * m->v_corientation.x / cxcy, 0);
	//V = ft_veccrossprod(U, C);
	V = ft_veccrossprod(C, U);
	V = ft_vecnormalize(V);
	printf("V: ");
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

			v_w.x = m->v_ceye.x + C.x +
				xpos * U.x - ypos * V.x;
			v_w.y = m->v_ceye.y + C.y +
				xpos * U.y - ypos * V.y;

	// printf("v_w: ");
	// ft_vecprint(&v_w);
	// printf("\n");


			color = decide_color(v_w, m);
			mlx_pixel_put(mlx, win, x, y, ft_color(color.r, color.g, color.b));
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
	void	*mlx;
	void	*win1;

	if (!(mlx = mlx_init()))
	{
		write(1, "Error\nInitialization failed.\n", 29);
		exit(1);
	}
	printf("Mlx init OK (use_xshm:%d, pshm_format:%d).\n",((t_xvar *)mlx)->use_xshm,((t_xvar *)mlx)->pshm_format);
	m->mlx = mlx;

	printf("Window1 creation: %dx%d \"Title 1\" ...", m->window_x, m->window_y);
	if (!(win1 = mlx_new_window(mlx, m->window_x, m->window_y, "Title1")))
	{
		printf(" !! KO !!\n");
		exit(1);
	}
	printf("OK\n");
	m->win = win1;

	printf("Drawing sphere ...");
	draw_map_wnd(mlx, win1, m);
	printf("OK\n");
	mlx_key_hook(win1, key_win1, m);
	mlx_hook(win1, 33, 0, (void *)close_win, 0);
	mlx_loop(mlx);
	//sleep(2);
}
