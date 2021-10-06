#include	"main.h"

double	ft_map(double x, int froma, int fromb, int toa, int tob)
{
	double	pos;
	double	ret;

	pos = (x - (double)froma) / ((double)fromb - (double)froma);
	ret = pos * ((double)tob - (double)toa) + (double)toa;
	return (ret);
}

int	get_endian(void)
{
	int		a;
	int		local_endian;

	a = 0x11223344;
	if (((unsigned char *)&a)[0] == 0x11)
		local_endian = 1;
	else
		local_endian = 0;
	return (local_endian);
}
