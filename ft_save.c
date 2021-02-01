#include "ft_save.h"

int	**ft_init_buffer(int width, int height)
{
	int	**ret;
	int	idx;

	idx = 0;
	if (!(ret = (int **)malloc(sizeof(int *) * (height + 1))))
		return (0);
	while (idx < height)
	{
		if (!(ret[idx] = (int *)malloc(sizeof(int) * (width + 1))))
		{
			ft_free_buffer(ret, idx);
			return (0);
		}
		idx++;
	}
	ret[height] = 0;
	return (ret);
}

void	ft_free_buffer(int **del, int height)
{
	int	i;

	i = 0;
	while (i < height)
		free(del[i++]);
	free(del);
}

/*
** bitmap file header
** header[2] : bfSize
** header[10] = total header size
** bitmap info header
** header[14] = bitmap info header size
** header[18] = width(pixel)
** header[22] = height(pixel)
** header[26] = always 1
** header[28] = bits per pixel ; 32 bits (4 bytes)
*/
int	ft_save_bmp(char *filename, int **target, int width, int height)
{
	unsigned char	header[54];
	int				row_padding;
	int				idx;
	int				fd;

	idx = 0;
	while (idx < HEADERSIZE)
		header[idx++] = 0;
	header[0] = 'B';
	header[1] = 'M';
	header[10] = HEADERSIZE;
	header[14] = 40;
	header[26] = 1;
	header[28] = 32;

	*(int *)(header + 18) = width;
	*(int *)(header + 22) = height;
	row_padding = (4 - width % 4) % 4;
	header[2] = 54 + (height * ((width * sizeof(int)) + row_padding));
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	write(fd, header, HEADERSIZE);
	while (height >= 0)
	{
		write(fd, target[height], width * sizeof(int));
		write(fd, "000", row_padding);
		height--;
	}
	close(fd);
	return (0);
}
