#include	"main.h"

int	readInt(int *i, char *line)
{
	int	ret;
	int	minus;

	skipSep(i, line);
	ret = 0;
	minus = 1;
	if (line[*i] == '-')
	{
		minus = -1;
		(*i)++;
	}
	while ('0' <= line[*i] && line[*i] <= '9')
		ret = ret * 10 + line[(*i)++] - '0';
	return (minus * ret);
}

double	readDouble(int *i, char *line)
{
	double	ret;
	double	dot;
	int	minus;

	skipSep(i, line);
	ret = 0;
	dot = 0;
	minus = 1;
	if (line[*i] == '-')
	{
		minus = -1;
		(*i)++;
	}
	while (line[*i])
	{
		if (line[*i] == '.')
			dot = 10;
		else if ('0' <= line[*i] && line[*i] <= '9')
			if (dot)
			{
				ret = ret + (line[*i] - '0') / dot;
				dot *= 10;
			}
			else
				ret = ret * 10 + line[*i] - '0';
		else
			break;
		(*i)++;
	}
	return (minus * ret);
}

int	readXyz(int *i, char *s, t_vec *v)
{
	double	x;
	double	y;
	double	z;

	x = readDouble(i, s);
	if (s[(*i)++] != ',')
		return (-1);
	y = readDouble(i, s);
	if (s[(*i)++] != ',')
		return (-1);
	z = readDouble(i, s);
	if (0)
		return (-1);
	if (v != NULL)
		ft_vecset(v, x, y, z);
printf("<xyz:%.2f, %.2f, %.2f>", x,y,z);
	return (0);
}

int	readRgb(int *i, char *s, t_color *c)
{
	int	r;
	int	g;
	int	b;

	r = readInt(i, s);
	if (r < 0 || r > 255 || s[(*i)++] != ',')
		return (-1);
	g = readInt(i, s);
	if (g < 0 || g > 255 || s[(*i)++] != ',')
		return (-1);
	b = readInt(i, s);
	if (b < 0 || b > 255)
		return (-1);
	if (c != NULL)
	{
		c->r = ft_map(r, 0, 255, 0, 1);
		c->g = ft_map(g, 0, 255, 0, 1);
		c->b = ft_map(b, 0, 255, 0, 1);
	}
printf("<rgb:%d,%d,%d>", r, g, b);
	return (0);
}

void	skipSep(int *i, char *line)
{
	while (line[*i] != '\0' && (line[*i] == ' ' || line[*i] == '\t'))
		(*i)++;
}