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

int	readXyz(int *i, char *s, t_map *m)
{
	double	d;

	d = readDouble(i, s);
printf("<xyz:%.2f,", d);
	if (s[(*i)++] != ',')
		return (-1);
	d = readDouble(i, s);
printf("%.2f,", d);
	if (s[(*i)++] != ',')
		return (-1);
	d = readDouble(i, s);
printf("%.2f> ", d);
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
printf("<rgb:%d,", j);
	if (j < 0 || j > 255 || s[(*i)++] != ',')
		return (-1);
	j = readInt(i, s);
printf("%d,", j);
	if (j < 0 || j > 255 || s[(*i)++] != ',')
		return (-1);
	j = readInt(i, s);
printf("%d> ", j);
	if (j < 0 || j > 255)
		return (-1);
	(void)*m;
	return (0);
}

void	skipSep(int *i, char *line)
{
	while (line[*i] != '\0' && (line[*i] == ' ' || line[*i] == '\t'))
		(*i)++;
}