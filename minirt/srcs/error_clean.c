#include "main.h"

static int	print_error_msg_fileread(int errNo)
{
	if (errNo == ERR_RD_REDEFINED_R)
		printerr("Error\nIncorrect file format: 'R' is duplicate.\n");
	else if (errNo == ERR_RD_REDEFINED_A)
		printerr("Error\nIncorrect file format: 'A' is duplicate.\n");
	else if (errNo == ERR_RD_OUTOFRANGE)
		printerr("Error\nSpecified value out of range.\n");
	else if (errNo == ERR_RD_INCORRECTFORMAT)
		printerr("Error\nIncorrect format.\n");
	else if (errNo == ERR_RD_TOOMUCH_CAM_SPECIFIED)
		printerr("Error\nToo much 'C' is specified.\n");
	else if (errNo == ERR_RD_TOOMUCH_LIT_SPECIFIED)
		printerr("Error\nToo much 'L' is specified.\n");
	else if (errNo == ERR_RD_TOOMUCH_OBJ_SPECIFIED)
		printerr("Error\nToo much objects are specified.\n");
	else if (errNo == ERR_CHK_NO_A)
		printerr("Error\n'A' is not specified.\n");
	else
		return (0);
	return (1);
}

static void	print_error_msg(int errNo)
{
	if (errNo == ERR_SYS_MALLOC)
		printerr("Error\nFailed to allocate memory.\n");
	else if (errNo == ERR_SYS_FILENAME)
		printerr(
			"Error\nUnrecognied parameter. File extension should be '.rt'.\n");
	else if (errNo == ERR_SYS_FILEOPEN)
		printerr("Error\nFailed to open file.\n");
	else if (errNo == ERR_SYS_FILEWRITE)
		printerr("Error\nFailed to write file.\n");
	else if (errNo == ERR_WND_MLXINIT)
		printerr("Error\nMlx initialization failed.\n");
	else if (errNo == ERR_WND_WNDINIT)
		printerr("Error\nWindow creation failed.\n");
	else
		printerr("Error\nUnexpected error.\n");
}

void	print_error_exit(int errNo, t_map *m)
{
	if (print_error_msg_fileread(errNo) == 0)
		print_error_msg(errNo);
	free_map(m);
	exit(errNo);
}
