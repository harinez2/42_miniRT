#include	"main.h"

int	is_eol(int *i, char *line)
{
	if (line[*i] == '\r' || line[*i] == '\n' || line[*i] == '\0')
		return (1);
	else
		return (0);
}

int	is_normalized(t_vec *v)
{
	if (v->x < -1 - EPSILON || 1 + EPSILON < v->x
		|| v->y < -1 - EPSILON || 1 + EPSILON < v->y
		|| v->z < -1 - EPSILON || 1 + EPSILON < v->z)
		return (0);
	else
		return (1);
}

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
