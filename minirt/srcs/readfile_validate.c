#include	"main.h"

static void	validate_ACL(t_map *m)
{
	// if (m->window_x <= 0 || INT_MAX < m->window_x)
	// 	print_error_exit(ERR_RD_OUTOFRANGE, m);
	// if (m->window_y <= 0 || INT_MAX < m->window_y)
	// 	print_error_exit(ERR_RD_OUTOFRANGE, m);
	if (m->ambItsty == -1)
		print_error_exit(ERR_CHK_NO_A, m);

}

static void	validate_objs(t_map *m)
{
	(void)m;
}

void	validate_parameters(t_map *m)
{
	validate_ACL(m);
	validate_objs(m);
}
