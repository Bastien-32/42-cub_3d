#include "cub3d.h"

void	go_to_end_fd(int fd, char *line)
{
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

