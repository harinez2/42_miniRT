#include	"main.h"

/* color
 * specify color value between 0-255 for each params
 */
int 	ft_color(int red, int green, int blue)
{
	int	c;

	c = (red << 16) + (green << 8) + blue;
	return (c);
}

void	set_color(t_color *c, double red, double green, double blue)
{
	c->r = red;
	c->g = green;
	c->b = blue;
	return ;
}

t_color	set_rgb_inrange(t_color c)
{
	if (c.r > 255)
		c.r = 255;
	if (c.r < 0)
		c.r = 0;
	if (c.g > 255)
		c.g = 255;
	if (c.g < 0)
		c.g = 0;
	if (c.b > 255)
		c.b = 255;
	if (c.b < 0)
		c.b = 0;
	return (c);
}