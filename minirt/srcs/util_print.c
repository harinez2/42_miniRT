#include	"main.h"

void	printerr(const char *msg)
{
	write(2, msg, ft_strlen(msg));
}
