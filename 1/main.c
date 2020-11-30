#include "get_next_line.h"

int				main(void)
{
	int			fd;
	char		*line;
	int			res;
	// int			count;

	fd = open("test.txt", O_RDONLY);
	// count = 0;
	res = 1;
	while (1)
	{
		res = get_next_line(fd, &line);
		if (res == 1)
		{
			// printf("count: %d\n", count);
			// count++;
			printf("%s\n", line);
		}
		else if (res == -1)
		{
			printf("ERROR\n");
		}
		else
		{
			free(line);
			break ;
		}
		free(line);
	}
	return (0);
}
