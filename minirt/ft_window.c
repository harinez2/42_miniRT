#include	"main.h"

int	key_win1(int key, t_map *m)
{
	//キーコードはxevコマンドで調べる
	if (key == 0xFF1B)//esc
	{
		printf("ESC key pressed.\n");
		exit(0);
	}
	else if (key == 0x63)//c key
	{

		m->ceye_num++;
		if (m->ceye_num == m->eye_count)
			m->ceye_num = 0;
		m->v_ceye = m->v_eye[m->ceye_num];
		draw_map_wnd(m->mlx, m->win, m);
		printf("c key pressed: cameranum = %d ", m->ceye_num);
		printf("(%.2f, %.2f, %.2f)\n", m->v_ceye.x, m->v_ceye.y, m->v_ceye.z);
	}
	else if (key == 0xff52)//Up key
	{
		m->v_ceye.y = m->v_ceye.y + 1;
		draw_map_wnd(m->mlx, m->win, m);
		printf("Up key pressed: cameranum = %d ", m->ceye_num);
		printf("(%.2f, %.2f, %.2f)\n", m->v_ceye.x, m->v_ceye.y, m->v_ceye.z);
	}
	else if (key == 0xff54)//Down key
	{
		m->v_ceye.y = m->v_ceye.y - 1;
		draw_map_wnd(m->mlx, m->win, m);
		printf("Up key pressed: cameranum = %d ", m->ceye_num);
		printf("(%.2f, %.2f, %.2f)\n", m->v_ceye.x, m->v_ceye.y, m->v_ceye.z);
	}
	else if (key == 0xff51)//Left key
	{
		m->v_ceye.x = m->v_ceye.x + 1;
		draw_map_wnd(m->mlx, m->win, m);
		printf("Up key pressed: cameranum = %d ", m->ceye_num);
		printf("(%.2f, %.2f, %.2f)\n", m->v_ceye.x, m->v_ceye.y, m->v_ceye.z);
	}
	else if (key == 0xff53)//Right key
	{
		m->v_ceye.x = m->v_ceye.x - 1;
		draw_map_wnd(m->mlx, m->win, m);
		printf("Up key pressed: cameranum = %d ", m->ceye_num);
		printf("(%.2f, %.2f, %.2f)\n", m->v_ceye.x, m->v_ceye.y, m->v_ceye.z);
	}
	else if (key == 0x66)//f key
	{
		m->v_ceye.z = m->v_ceye.z - 1;
		draw_map_wnd(m->mlx, m->win, m);
		printf("f key pressed: cameranum = %d ", m->ceye_num);
		printf("(%.2f, %.2f, %.2f)\n", m->v_ceye.x, m->v_ceye.y, m->v_ceye.z);
	}
	else if (key == 0x62)//b key
	{
		m->v_ceye.z = m->v_ceye.z + 1;
		draw_map_wnd(m->mlx, m->win, m);
		printf("b key pressed: cameranum = %d ", m->ceye_num);
		printf("(%.2f, %.2f, %.2f)\n", m->v_ceye.x, m->v_ceye.y, m->v_ceye.z);
	}
	return (0);
}

void	close_win()
{

	printf("window close button pressed.\n");
	exit(0);
}

int	draw_map_wnd(void *mlx, void *win, t_map *m)
{
	int	x;
	int	y;
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
