#include "get_next_line.h"

int main(void)
{
	int fd;
	int rc;
	int res;
	char s[1000];

	rc = -1;
	fd = open("test.txt", O_RDONLY);
	printf("%d\n", fd);
	while (rc != 0)
	{
		rc = read(fd, s, 900);
		// printf("%d\n", rc);
		printf("%s\n", s);
	}
	close(fd);
	return 0;
}
