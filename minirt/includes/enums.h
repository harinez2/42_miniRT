#ifndef ENUMS_H
#define ENUMS_H

enum e_cmds
{
	CMD_NONE,
	CMD_RESOLUTION,
	CMD_AMBIENT,
	CMD_CAMERA,
	CMD_LIGHT,
	CMD_SPHERE,
	CMD_PLANE,
	CMD_SQUARE,
	CMD_CYLINDER,
	CMD_TRIANGLE
};

enum e_errors
{
	ERR_UNKNOWN,
	ERR_SYS_MALLOC,
	ERR_SYS_FILEOPEN,
	ERR_SYS_FILEWRITE,
	ERR_RD_REDEFINED_R,
	ERR_RD_REDEFINED_A,
	ERR_RD_OUTOFRANGE_SCREEN,
	ERR_RD_OUTOFRANGE_RGB,
	ERR_RD_INCORRECTFORMAT,
	ERR_CHK_NO_R,
	ERR_CHK_NO_A,
	ERR_WND_MLXINIT,
	ERR_WND_WNDINIT
};

enum e_keys
{
	KEY_C		= 0x63,
	KEY_UP		= 0xff52,
	KEY_DOWN	= 0xff54,
	KEY_LEFT	= 0xff51,
	KEY_RIGHT	= 0xff53,
	KEY_F		= 0x66,
	KEY_B		= 0x62,
	KEY_ESC		= 0xFF1B
};

#endif