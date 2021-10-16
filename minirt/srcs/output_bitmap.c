#include	"main.h"

static void	set_bmp_header(uint8_t *header_buffer, int stride, t_map *m)
{
	t_bmp_file_header	*file;
	t_bmp_info_header	*info;

	file = (t_bmp_file_header *)header_buffer;
	info = (t_bmp_info_header *)(header_buffer + FILE_HEADER_SIZE);
	file->bfType = FILE_TYPE;
	file->bfSize = DEFAULT_HEADER_SIZE + stride * m->window_y;
	file->bfReserved1 = 0;
	file->bfReserved2 = 0;
	file->bfOffBits = DEFAULT_HEADER_SIZE;
	info->biSize = INFO_HEADER_SIZE;
	info->biWidth = m->window_x;
	info->biHeight = m->window_y;
	info->biPlanes = 1;
	info->biBitCount = 24;
	info->biCompression = 0;
	info->biSizeImage = stride * m->window_y;
	info->biXPelsPerMeter = 0;
	info->biYPelsPerMeter = 0;
	info->biClrUsed = 0;
	info->biClrImportant = 0;
}

static int	draw_map_bmp(int fd, uint8_t *buffer, int stride, t_map *m)
{
	int		x;
	int		y;
	uint8_t	*row;
	t_color	c;

	y = 0;
	while (y < m->window_y)
	{
		row = buffer;
		x = 0;
		while (x < m->window_x)
		{
			c = get_color_on_screen(m, x, y);
			*row++ = c.b;
			*row++ = c.g;
			*row++ = c.r;
			x++;
		}
		if (write(fd, buffer, stride) <= 0)
		{
			free(buffer);
			return (-1);
		}
		y++;
	}
	return (0);
}

static int	write_bmp_simple_stream(int fd, t_map *m)
{
	uint8_t		header_buffer[DEFAULT_HEADER_SIZE];
	int			stride;
	uint8_t		*buffer;

	stride = (m->window_x * 3 + 3) / 4 * 4;
	buffer = malloc(stride);
	if (!buffer)
		return (-1);
	set_bmp_header(header_buffer, stride, m);
	if (write(fd, header_buffer, DEFAULT_HEADER_SIZE) <= 0)
	{
		free(buffer);
		return (-1);
	}
	memset(buffer, 0, stride);
	draw_map_bmp(fd, buffer, stride, m);
	free(buffer);
	return (0);
}

int	write_bmp(t_map *m)
{
	int		ret;
	char	*filename;
	int		fd;

	filename = "out.bmp";
	ret = -1;
	fd = open(filename, O_CREAT | O_WRONLY);
	if (fd < 0)
	{
		perror(filename);
		return (ret);
	}
	ret = write_bmp_simple_stream(fd, m);
	close(fd);
	return (ret);
}
