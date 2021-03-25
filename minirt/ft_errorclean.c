#include "main.h"

void	ft_showErrorExit(int errNo, t_map *m)
{
	if (errNo == ERR_SYS_MALLOC)
		printf("Error\nFailed to allocate memory.\n");
	else if (errNo == ERR_SYS_FILEOPEN)
		printf("Error\nFailed to open file.\n");
	else if (errNo == ERR_SYS_FILEWRITE)
		printf("Error\nFailed to write file.\n");
	else if (errNo == ERR_RD_REDEFINED_R)
		printf("Error\nIncorrect file format.\n'R' is duplicate.");
	else if (errNo == ERR_RD_REDEFINED_A)
		printf("Error\nIncorrect file format.\n'A' is duplicate.");
	else if (errNo == ERR_RD_OUTOFRANGE_SCREEN)
		printf("Error\nSpecified resolution value out of range.");
	else if (errNo == ERR_RD_OUTOFRANGE_RGB)
		printf("Error\nSpecified rgb value out of range.");
	else if (errNo == ERR_RD_INCORRECTFORMAT)
		printf("Error\nIncorrect format.\n");
	else if (errNo == ERR_CHK_NO_R)
		printf("Error\n'R' is not specified.\n");
	else if (errNo == ERR_CHK_NO_A)
		printf("Error\n'A' is not specified.\n");
	else if (errNo == ERR_WND_MLXINIT)
		printf("Error\nMlx initialization failed.\n");
	else if (errNo == ERR_WND_WNDINIT)
		printf("Error\nWindow creation failed.\n");
	else
		printf("Error\nUnexpected error.");
	freeX(m);
	exit(errNo);
}

void	freeX(t_map *m)
{
	int		i;

	i = 0;
	while (i < m->obj_count)
	{
		free(m->obj[i]);
		m->obj[i] = NULL;
		i++;
	}
}
