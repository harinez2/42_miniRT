#include	"main.h"

int	readInt(int *i, char *s)
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

double	readDouble(int *i, char *s)
{
	double	ret;
	double	dot;
	int		minus;

	skip_separater(i, s);
	ret = 0;
	dot = 0;
	minus = 1;
	if (s[*i] == '-')
	{
		minus = -1;
		(*i)++;
	}
	while (s[*i])
	{
		if (s[*i] == '.')
			dot = 10;
		else if ('0' <= s[*i] && s[*i] <= '9')
		{
			if (dot)
			{
				ret = ret + (s[*i] - '0') / dot;
				dot *= 10;
			}
			else
				ret = ret * 10 + s[*i] - '0';
		}
		else
			break ;
		(*i)++;
	}
	return (minus * ret);
}

t_vec	readXyz(int *i, char *s, t_map *m)
{
	t_vec	v;

	v.x = readDouble(i, s);
	if (s[(*i)++] != ',')
		print_error_exit(ERR_RD_INCORRECTFORMAT, m);
	v.y = readDouble(i, s);
	if (s[(*i)++] != ',')
		print_error_exit(ERR_RD_INCORRECTFORMAT, m);
	v.z = readDouble(i, s);
//printf("<xyz:%.2f, %.2f, %.2f>", v.x,v.y,v.z);
	return (v);
}

t_color	readRgb(int *i, char *s, t_map *m)
{
	t_color		c;

	c.r = readInt(i, s);
	if (s[(*i)++] != ',')
		print_error_exit(ERR_RD_INCORRECTFORMAT, m);
	else if (c.r < 0 || c.r > 255)
		print_error_exit(ERR_RD_OUTOFRANGE_RGB, m);
	c.g = readInt(i, s);
	if (s[(*i)++] != ',')
		print_error_exit(ERR_RD_INCORRECTFORMAT, m);
	else if (c.g < 0 || c.g > 255)
		print_error_exit(ERR_RD_OUTOFRANGE_RGB, m);
	c.b = readInt(i, s);
	if (c.b < 0 || c.b > 255)
		print_error_exit(ERR_RD_OUTOFRANGE_RGB, m);
	c.r = ft_map(c.r, 0, 255, 0, 1);
	c.g = ft_map(c.g, 0, 255, 0, 1);
	c.b = ft_map(c.b, 0, 255, 0, 1);
//printf("<rgb:%d,%d,%d>", r, g, b);
	//return (ft_color(c.r, c.g, c.b));
	return (c);
}

void	skip_separater(int *i, char *line)
{
	while (line[*i] != '\0' && (line[*i] == ' ' || line[*i] == '\t'))
		(*i)++;
}
