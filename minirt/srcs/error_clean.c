#include "main.h"

static int	print_error_msg_fileread(int errNo)
{
	if (errNo == ERR_RD_REDEFINED_R)
		printf("Error\nIncorrect file format: 'R' is duplicate.\n");
	else if (errNo == ERR_RD_REDEFINED_A)
		printf("Error\nIncorrect file format: 'A' is duplicate.\n");
	else if (errNo == ERR_RD_OUTOFRANGE)
		printf("Error\nSpecified value out of range.\n");
	else if (errNo == ERR_RD_INCORRECTFORMAT)
		printf("Error\nIncorrect format.\n");
	else if (errNo == ERR_RD_TOOMUCH_CAM_SPECIFIED)
		printf("Error\nToo much 'C' is specified.\n");
	else if (errNo == ERR_RD_TOOMUCH_LIT_SPECIFIED)
		printf("Error\nToo much 'L' is specified.\n");
	else if (errNo == ERR_RD_TOOMUCH_OBJ_SPECIFIED)
		printf("Error\nToo much objects are specified.\n");
	else if (errNo == ERR_CHK_NO_A)
		printf("Error\n'A' is not specified.\n");
	else
		return (0);
	return (1);
}

static void	print_error_msg(int errNo)
{
	if (errNo == ERR_SYS_MALLOC)
		printf("Error\nFailed to allocate memory.\n");
	else if (errNo == ERR_SYS_FILENAME)
		printf("Error\nUnrecognied parameter. File extension should be '.rt'.\n");
	else if (errNo == ERR_SYS_FILEOPEN)
		printf("Error\nFailed to open file.\n");
	else if (errNo == ERR_SYS_FILEWRITE)
		printf("Error\nFailed to write file.\n");
	else if (errNo == ERR_WND_MLXINIT)
		printf("Error\nMlx initialization failed.\n");
	else if (errNo == ERR_WND_WNDINIT)
		printf("Error\nWindow creation failed.\n");
	else
		printf("Error\nUnexpected error.\n");
}

void	print_error_exit(int errNo, t_map *m)
{
	if (print_error_msg_fileread(errNo) == 0)
		print_error_msg(errNo);
	free_map(m);
	exit(errNo);
}
