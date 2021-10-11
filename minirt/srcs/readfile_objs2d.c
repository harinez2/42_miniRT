#include	"main.h"

int	read_file_cone(int *i, char *line, t_map *m)
{
	(*i) += 2;
	m->obj_type[m->obj_count] = CMD_CONE;
	m->obj[m->obj_count] = (t_cone *)malloc(sizeof(t_cone));
	((t_cone *)m->obj[m->obj_count])->vertex = read_xyz(i, line, m);
	((t_cone *)m->obj[m->obj_count])->normal = read_xyz(i, line, m);
	((t_cone *)m->obj[m->obj_count])->theta = read_double(i, line, m);
	((t_cone *)m->obj[m->obj_count])->rgb = read_rgb(i, line, m);
	m->obj_count++;
	return (CMD_CONE);
}
