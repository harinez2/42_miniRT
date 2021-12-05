#include	"main.h"

void	print_cone(t_cone *tc)
{
	printf("Cone  : ");
	ft_vecprint(&tc->vertex);
	printf(" / ");
	ft_vecprint(&tc->normal);
	printf(" (theta:%.2f) / ", tc->theta);
	ft_colorprint(&tc->rgb);
	printf("\n");
}
