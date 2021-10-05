#include	"main.h"

void	ft_putstr(const char *s)
{
	write(STDIN_FILENO, s, ft_strlen(s));
}
