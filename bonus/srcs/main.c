#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line_bonus.h"

int main()
{
	int fd = open("test.txt", O_RDONLY);
	char *line1 = get_next_line(fd);
	char *line2 = get_next_line(fd);
	char *line3 = get_next_line(fd);
	printf("line1: [%s]\n", line1);
	printf("line2: [%s]\n", line2);
	printf("line3: [%s]\n", line3);
	free(line1);
	free(line2);
	free(line3);
	system("leaks a.out");
	return 0;
}

__attribute__((destructor))
static void destructor() {
    system("leaks -q a.out");
}
