#include	"main.h"

int	readInt(int *i, char *line)
{
	int	ret;

	ret = 0;
	while ('0' <= line[*i] && line[*i] <= '9')
		ret = ret * 10 + line[*i++] - '0';
	return (ret);
}

double	readDouble(int *i, char *s)
{
	double	ret;
	double	dot;
	int	minus;

	ret = 0;
	dot = 0;
	minus = 1;
	if (s[*i] == '-')
	{
		minus = -1;
		i++;
	}
	while (s[*i])
	{
		if (s[*i] == '.')
			dot = 10;
		else if ('0' <= s[*i] && s[*i] <= '9')
			if (dot)
			{
				ret = ret + (s[*i] - '0') / dot;
				dot *= 10;
			}
			else
				ret = ret * 10 + s[*i] - '0';
		else
			break;
		i++;
	}
	return (minus * ret);
}

int	readXyz(int *i, char *s, t_map *m)
{
	double	d;

	d = readDouble(i, s);
	if (s[*i++] != ',')
		return (-1);
	d = readDouble(i, s);
	if (s[*i++] != ',')
		return (-1);
	d = readDouble(i, s);
	if (0)
		return (-1);
	(void)d;
	(void)*m;
	return (0);
}

int	readRgb(int *i, char *s, t_map *m)
{
	int	j;

	j = readInt(i, s);
	if (j < 0 || j > 255 || s[*i++] != ',')
		return (-1);
	j = readInt(i, s);
	if (j < 0 || j > 255 || s[*i++] != ',')
		return (-1);
	j = readInt(i, s);
	if (j < 0 || j > 255)
		return (-1);
	(void)*m;
	return (0);
}
