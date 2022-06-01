#include	"main.h"

static void	calc_distance_cam_scr(t_map *m)
{
	double	tan_theta_div_two;

	if (m->dsp)
		ft_vecprint_with_name("  curr_cam.orien            ",
			&m->curr_cam.orien);
	tan_theta_div_two = (double)tan(ft_degree_to_rad(m->curr_cam.fov) / 2);
	if (m->dsp)
		printf("  tan_theta_div_two          : %.2f\n", tan_theta_div_two);
	m->scr.distance_cam_scr = (double)m->window_x / tan_theta_div_two / 2;
	if (m->dsp)
		printf("  distance_cam_scr           : %.2f\n", m->scr.distance_cam_scr);
}

// unitvec x is a unit vector which the z-axis vec is zero.
static void	calc_screen_unitvec_x(t_map *m)
{
	double	scrx_x;
	double	scrx_y;

	if (m->curr_cam.orien.y < 0)
		scrx_x = -1;
	else if (m->curr_cam.orien.y == 0 && m->curr_cam.orien.x != 0)
		scrx_x = 0;
	else
		scrx_x = 1;
	if (m->curr_cam.orien.y == 0 && m->curr_cam.orien.x == 0)
		scrx_y = 0;
	else if (m->curr_cam.orien.y == 0 && m->curr_cam.orien.x < 0)
		scrx_y = 1;
	else if (m->curr_cam.orien.y == 0 && m->curr_cam.orien.x > 0)
		scrx_y = -1;
	else if (m->curr_cam.orien.x == 0)
		scrx_y = 0;
	else if (m->curr_cam.orien.y > 0)
		scrx_y = -1 * m->curr_cam.orien.y / m->curr_cam.orien.x;
	else
		scrx_y = m->curr_cam.orien.y / m->curr_cam.orien.x;
	// if (m->curr_cam.orien.x == 0 && m->curr_cam.orien.y >= 0)
	// 	m->scr.unitvec_scrx = ft_vec(1, 0, 0);
	// else if (m->curr_cam.orien.x == 0 && m->curr_cam.orien.y < 0)
	// 	m->scr.unitvec_scrx = ft_vec(-1, 0, 0);
	// else if (m->curr_cam.orien.y == 0 && m->curr_cam.orien.x > 0)
	// 	m->scr.unitvec_scrx = ft_vec(0, -1, 0);
	// else if (m->curr_cam.orien.y == 0 && m->curr_cam.orien.x < 0)
	// 	m->scr.unitvec_scrx = ft_vec(0, 1, 0);
	// else
	// {
	// 	m->scr.unitvec_scrx.x = 1;
	// 	m->scr.unitvec_scrx.y
	// 		= -1 * m->curr_cam.orien.x / m->curr_cam.orien.y;
	// 	m->scr.unitvec_scrx.z = 0;
	// }
	m->scr.unitvec_scrx = ft_vec(scrx_x, scrx_y, 0);
	if (m->dsp)
		ft_vecprint_with_name("  unitvec_scrx              ",
			&m->scr.unitvec_scrx);
	m->scr.unitvec_scrx = ft_vecnormalize(m->scr.unitvec_scrx);
	if (m->dsp)
		ft_vecprint_with_name("  unitvec_scrx(normalized)  ",
			&m->scr.unitvec_scrx);
}

// unitvec y is a unit vector which the x-axis vec is zero.
static void	calc_screen_unitvec_y(t_map *m)
{
	if (m->curr_cam.orien.z == 0)
		m->scr.unitvec_scry = ft_vec(0, 0, 1);
	else
		m->scr.unitvec_scry
			= ft_veccrossprod(m->scr.unitvec_scrx, m->curr_cam.orien);
	if (m->dsp)
		ft_vecprint_with_name("  unitvec_scry              ",
			&m->scr.unitvec_scry);
	m->scr.unitvec_scry = ft_vecnormalize(m->scr.unitvec_scry);
	if (m->dsp)
		ft_vecprint_with_name("  unitvec_scry(normalized)  ",
			&m->scr.unitvec_scry);
}

void	init_screen_values(t_map *m)
{
	if (m->dsp)
		printf("\n>>>>> Calculating screen parameter...\n");
	calc_distance_cam_scr(m);
	calc_screen_unitvec_x(m);
	calc_screen_unitvec_y(m);
}
