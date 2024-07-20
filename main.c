#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"

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

// int main(void)
// {
// 	printf("------------\n");
//     int fd = open("test.txt", O_RDONLY);
// 	printf("------------\n");
//     close(fd);
//     char *line;

//     if (fd == -1)
//     {
//         perror("Error opening file\n");
//         return (1);
//     }
// 	printf("...%d...\n", fd);
// 	line = get_next_line(fd);
//     while (line != NULL)
//     {
//         printf("[[%s]]", line);
//         free(line);
//     }

//     if (line == NULL)
//     {
//         printf("get_next_line returned NULL as expected for an empty file.\n");
//     }

// 	// printf("------------");
//     return (0);
// }


// #include <fcntl.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include "get_next_line.h"

// void run_test_case(int fd, const char *description)
// {
//     char *line = get_next_line(fd);
//     printf("%s: %s\n", description, line ? line : "NULL");
//     if (line)
//         free(line);
// }

// int main(void)
// {
//     // Test case 1: Invalid file descriptor 1000
//     printf("Test case 1: Invalid file descriptor 1000\n");
//     run_test_case(1000, "gnl(1000, NULL)");

//     // Test case 2: Invalid file descriptor -1
//     printf("Test case 2: Invalid file descriptor -1\n");
//     run_test_case(-1, "gnl(-1, NULL)");

//     // Test case 3: Valid file descriptor, then close and call gnl again
//     int fd = open("test.txt", O_RDONLY);
//     if (fd == -1)
//     {
//         perror("Error opening file");
//         return 1;
//     }
    
//     printf("Test case 3: Valid file descriptor, then close and call gnl again\n");
//     run_test_case(fd, "gnl(fd, NULL) before close");
//     close(fd);
//     run_test_case(fd, "gnl(fd, NULL) after close");

//     return 0;
// }