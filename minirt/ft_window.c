#include	"main.h"

int	key_win1(int key, void *p)
{
	(void)p;
	printf("Key in Win1 : %d\n", key);
	//キーコードはxevコマンドで調べる
	if (key == 0xFF1B)//esc
		exit(0);
	else if (key == 0x63)
		printf("c key pressed.\n");
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

	printf("Window1 creation: %dx%d \"Title 1\" ...", m->window_x, m->window_y);
	if (!(win1 = mlx_new_window(mlx, m->window_x, m->window_y, "Title1")))
	{
		printf(" !! KO !!\n");
		exit(1);
	}
	printf("OK\n");

	printf("Drawing sphere ...");
	draw_map_wnd(mlx, win1, m);
	printf("OK\n");
	mlx_key_hook(win1, key_win1, 0);
	mlx_hook(win1, 33, 0, (void *)close_win, 0);
	mlx_loop(mlx);
	//sleep(2);
}
