#include	"main.h"

double	calc_t(double A, double B, double D)
{
	double	t1;
	double	t2;
	double	t;

	t = -1;
	if (D == 0)
		t = -B / (2 * A);
	else if (D > 0)
	{
		t1 = (-B - sqrt(D)) / (2 * A);
		t2 = (-B + sqrt(D)) / (2 * A);
		if (t1 > 0 && t2 > 0)
			t = fmin(t1, t2);
		else
			t = fmax(t1, t2);
	}
	return (t);
}
