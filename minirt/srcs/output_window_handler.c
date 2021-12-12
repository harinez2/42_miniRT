#include	"main.h"

static void	print_keyname_and_cameracfg(int key, t_map *m)
{
	if (key == KEY_C)
		printf("c key");
	else if (key == KEY_UP)
		printf("Up key");
	else if (key == KEY_DOWN)
		printf("Down key");
	else if (key == KEY_LEFT)
		printf("Left key");
	else if (key == KEY_RIGHT)
		printf("Right key");
	else if (key == KEY_F)
		printf("f key");
	else if (key == KEY_B)
		printf("b key");
	if (m->dsp)
	{
		printf(" pressed.\n");
		printf("Current camera status: %d ", m->curr_cam_num);
		printf("(%.2f, %.2f, %.2f)\n",
			m->curr_cam.pos.x, m->curr_cam.pos.y, m->curr_cam.pos.z);
	}
}

static void	change_current_camera(t_map *m)
{
	m->curr_cam_num++;
	if (m->curr_cam_num == m->cam_cnt)
		m->curr_cam_num = 0;
	m->curr_cam = m->cam[m->curr_cam_num];
}

// memo: key code can be searched with xev command
int	keypress_handler(int key, t_map *m)
{
	if (key == KEY_ESC)
		close_win_hanlder(m, KEY_ESC);
	if (key == KEY_C)
		change_current_camera(m);
	else if (key == KEY_UP)
		m->curr_cam.pos.y += 1;
	else if (key == KEY_DOWN)
		m->curr_cam.pos.y -= 1;
	else if (key == KEY_LEFT)
		m->curr_cam.pos.x -= 1;
	else if (key == KEY_RIGHT)
		m->curr_cam.pos.x += 1;
	else if (key == KEY_F)
		m->curr_cam.pos.z -= 1;
	else if (key == KEY_B)
		m->curr_cam.pos.z += 1;
	else
		return (0);
	if (m->dsp)
		print_keyname_and_cameracfg(key, m);
	draw_map_on_window(m);
	return (0);
}

void	close_win_hanlder(t_map *m, int called_by)
{
	if (m->dsp)
	{
		if (called_by == KEY_ESC)
			printf("ESC key pressed.\n");
		else
			printf("Window close button pressed.\n");
	}
	free_map(m);
	exit(0);
}
