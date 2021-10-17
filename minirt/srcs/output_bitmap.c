#include	"main.h"

// file header (14 byte)
// pos	size	name		desc
// 0	2	bfType			'BM'
// 2	4	bfSize			file size(byte)
// 6	2	bfReserved1		(reserved)
// 8	2	bfReserved2		(reserved)
// 10	4	bfOffBits		offset(byte) from file top to img data
//
// info header (40 byte)
// pos	size	name		desc
// 14	4	biSize			info header size
// 18	4	biWidth			img width(piexl)
// 22	4	biHeight		img height(pixel)
// 26	2	biPlanes		plane num(always 1)
// 28	2	biBitCount		color bit
// 30	4	biCompression	compression format
// 34	4	biSizeImage		img data size
// 38	4	biXPelsPerMeter	x resolution in pixel
// 42	4	biYPelsPerMeter	y resolution in pixel
// 46	4	biClrUsed		stored palette num
// 50	4	biClrImportant	important color num
static void	set_bmp_header(uint8_t *header_buffer, int stride, t_map *m)
{
	int	i;

	ft_memcpy(header_buffer, "BM", 2);
	i = DEFAULT_HEADER_SIZE + stride * m->window_y;
	ft_memcpy(header_buffer + 2, &i, 4);
	ft_memset(header_buffer + 6, 0, 2);
	ft_memset(header_buffer + 8, 0, 2);
	i = DEFAULT_HEADER_SIZE;
	ft_memcpy(header_buffer + 10, &i, 4);
	i = INFO_HEADER_SIZE;
	ft_memcpy(header_buffer + 14, &i, 4);
	ft_memcpy(header_buffer + 18, &(m->window_x), 4);
	ft_memcpy(header_buffer + 22, &(m->window_y), 4);
	i = 1;
	ft_memcpy(header_buffer + 26, &i, 2);
	i = 24;
	ft_memcpy(header_buffer + 28, &i, 2);
	ft_memset(header_buffer + 30, 0, 4);
	i = stride * m->window_y;
	ft_memcpy(header_buffer + 34, &i, 4);
	ft_memset(header_buffer + 38, 0, 4);
	ft_memset(header_buffer + 42, 0, 4);
	ft_memset(header_buffer + 46, 0, 4);
	ft_memset(header_buffer + 50, 0, 4);
}

static int	draw_map_on_bmp(int fd, uint8_t *buffer, int stride, t_map *m)
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
			return (-1);
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
	draw_map_on_bmp(fd, buffer, stride, m);
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
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC);
	if (fd < 0)
	{
		perror(filename);
		return (ret);
	}
	ret = write_bmp_simple_stream(fd, m);
	close(fd);
	return (ret);
}
