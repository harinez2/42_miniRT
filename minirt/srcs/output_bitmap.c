#include	"main.h"

void	set_bmp_header(uint8_t *header_buffer, int stride, t_map *m)
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

int	draw_map_bmp(FILE *fp, uint8_t *buffer, int stride, t_map *m)
{
	int		x;
	int		y;
	uint8_t	*row;
	t_vec	v_w;
	t_color	c;

	v_w.z = 0;
	y = 0;
	while (y < m->window_y)
	{
		row = buffer;
		v_w.y = ft_map(y, 0, m->window_y - 1, -1, 1);
		x = 0;
		while (x < m->window_x)
		{
			v_w.x = ft_map(x, 0, m->window_x - 1, -1, 1);
			c = decide_color(v_w, m);
			*row++ = c.b;
			*row++ = c.g;
			*row++ = c.r;
			x++;
		}
		if (fwrite(buffer, stride, 1, fp) != 1)
		{
			free(buffer);
			return (-1);
		}
		y++;
	}
	return (0);
}

int	write_bmp_simple_stream(FILE *fp, t_map *m)
{
	uint8_t		header_buffer[DEFAULT_HEADER_SIZE];
	int			stride;
	uint8_t		*buffer;

	stride = (m->window_x * 3 + 3) / 4 * 4;
	buffer = malloc(stride);
	if (!buffer)
		return (-1);
	set_bmp_header(header_buffer, stride, m);
	if (fwrite(header_buffer, DEFAULT_HEADER_SIZE, 1, fp) != 1)
	{
		free(buffer);
		return (-1);
	}
	memset(buffer, 0, stride);
	draw_map_bmp(fp, buffer, stride, m);
	free(buffer);
	return (0);
}

int	write_bmp(t_map *m)
{
	int		ret;
	char	*filename;
	FILE	*fp;

	filename = "out.bmp";
	ret = -1;
	fp = fopen(filename, "wb");
	if (fp == NULL)
	{
		perror(filename);
		return (ret);
	}
	ret = write_bmp_simple_stream(fp, m);
	fclose(fp);
	return (ret);
}
