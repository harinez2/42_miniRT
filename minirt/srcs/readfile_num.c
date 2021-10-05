#include	"main.h"

int	read_int(int *i, char *s)
{
	int	ret;
	int	minus;

	skip_separater(i, s);
	ret = 0;
	minus = 1;
	if (s[*i] == '-')
	{
		minus = -1;
		(*i)++;
	}
	while ('0' <= s[*i] && s[*i] <= '9')
		ret = ret * 10 + s[(*i)++] - '0';
	return (minus * ret);
}

double	read_double(int *i, char *s, t_map *m)
{
	long long	int_part;
	long long	deci_part;
	int			ret;

	skip_separater(i, s);
	ret = ft_atoll(&s[*i], &int_part);
	if (ret == 0)
		print_error_exit(ERR_RD_INCORRECTFORMAT, m);
	*i += ret;
	deci_part = 0;
	ret = 0;
	if (s[*i] == '.')
	{
		(*i)++;
		ret = ft_atoll(&s[*i], &deci_part);
		*i += ret;
	}
	if (!is_whitespace(s[*i]) && s[*i] != '\0' && s[*i] != ',')
		print_error_exit(ERR_RD_INCORRECTFORMAT, m);
	return (int_part + deci_part * 0.1 * ret);
}

t_vec	read_xyz(int *i, char *s, t_map *m)
{
	t_vec	v;

	v.x = read_double(i, s, m);
	if (s[(*i)++] != ',')
		print_error_exit(ERR_RD_INCORRECTFORMAT, m);
	v.y = read_double(i, s, m);
	if (s[(*i)++] != ',')
		print_error_exit(ERR_RD_INCORRECTFORMAT, m);
	v.z = read_double(i, s, m);
	return (v);
}

t_color	read_rgb(int *i, char *s, t_map *m)
{
	t_color		c;

	c.r = read_int(i, s);
	if (s[(*i)++] != ',')
		print_error_exit(ERR_RD_INCORRECTFORMAT, m);
	else if (c.r < 0 || c.r > 255)
		print_error_exit(ERR_RD_OUTOFRANGE_RGB, m);
	c.g = read_int(i, s);
	if (s[(*i)++] != ',')
		print_error_exit(ERR_RD_INCORRECTFORMAT, m);
	else if (c.g < 0 || c.g > 255)
		print_error_exit(ERR_RD_OUTOFRANGE_RGB, m);
	c.b = read_int(i, s);
	if (c.b < 0 || c.b > 255)
		print_error_exit(ERR_RD_OUTOFRANGE_RGB, m);
	c.r = ft_map(c.r, 0, 255, 0, 1);
	c.g = ft_map(c.g, 0, 255, 0, 1);
	c.b = ft_map(c.b, 0, 255, 0, 1);
	return (c);
}

void	skip_separater(int *i, char *line)
{
	while (line[*i] != '\0' && (line[*i] == ' ' || line[*i] == '\t'))
		(*i)++;
}