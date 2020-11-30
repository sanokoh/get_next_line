#include "get_next_line.h"

int				main(void)
{
	int			fd;
	char		*line;
	int			res;
	// int			count;

	fd = open("test_file7", O_RDONLY);
	// count = 0;
	res = 1;
	while (1)
	{
		if ((res = get_next_line(fd, &line)) == ERROR)
			return (printf("Error ocured.\n"));
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
