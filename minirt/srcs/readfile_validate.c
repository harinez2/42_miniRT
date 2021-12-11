#include	"main.h"

static void	validate_ACL(t_map *m)
{
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
