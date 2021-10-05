#ifndef CONSTANTS_H
# define CONSTANTS_H

# define PI				3.14159265359

# define MAX_OBJ_COUNT		200
# define MAX_CAMERA_COUNT	30
# define MAX_LIGHT_COUNT	30

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
