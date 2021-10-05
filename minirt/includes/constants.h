#ifndef CONSTANTS_H
# define CONSTANTS_H

# define PI				3.14159265359
# define CMD_RESOLUTION	1
# define CMD_AMBIENT	2
# define CMD_CAMERA		3
# define CMD_LIGHT		4
# define CMD_SPHERE		11
# define CMD_PLANE		12
# define CMD_SQUARE		13
# define CMD_CYLINDER	14
# define CMD_TRIANGLE	15
# define CMD_NONE		0

# define ERR_SYS_MALLOC				-1
# define ERR_SYS_FILEOPEN			-2
# define ERR_SYS_FILEWRITE			-3
# define ERR_RD_REDEFINED_R			-11
# define ERR_RD_REDEFINED_A			-12
# define ERR_RD_OUTOFRANGE_SCREEN	-13
# define ERR_RD_OUTOFRANGE_RGB		-14
# define ERR_RD_INCORRECTFORMAT		-15
# define ERR_CHK_NO_R				-21
# define ERR_CHK_NO_A				-22
# define ERR_WND_MLXINIT			-31
# define ERR_WND_WNDINIT			-32

# define MAX_OBJ_COUNT		200
# define MAX_CAMERA_COUNT	30
# define MAX_LIGHT_COUNT	30

// key map
# define KEY_C		0x63
# define KEY_UP		0xff52
# define KEY_DOWN	0xff54
# define KEY_LEFT	0xff51
# define KEY_RIGHT	0xff53
# define KEY_F		0x66
# define KEY_B		0x62
# define KEY_ESC	0xFF1B

// for bmp file
# define FILE_TYPE				0x4D42	// value of "BM" in little endian
# define FILE_HEADER_SIZE		14
# define INFO_HEADER_SIZE		40
# define DEFAULT_HEADER_SIZE	54	// FILE_HEADER_SIZE + INFO_HEADER_SIZE

# define COLOR_TYPE_INDEX	0
# define COLOR_TYPE_GRAY	1
# define COLOR_TYPE_RGB		2
# define COLOR_TYPE_RGBA	3

#endif
