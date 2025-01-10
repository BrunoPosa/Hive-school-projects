
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

int main(void)
{
    char *line;
    int    fd;

    //fd = open("/home/tvalimak/francinette/tests/get_next_line/fsoares/43_with_nl.txt", O_RDONLY);
	//fd = open("/home/tvalimak/francinette/tests/get_next_line/gnlTester/files/43_with_nl", O_RDONLY);
	//fd = open("/Users/tvalimak/francinette/tests/get_next_line/fsoares/1char.txt", O_RDONLY);
    fd = open("/Users/tvalimak/get_next_line/get_next_line.c", O_RDONLY);
	//fd = open("/Users/tvalimak/francinette/tests/get_next_line/fsoares/one_line_no_nl.txt", O_RDONLY);
	//fd = open("/Users/tvalimak/francinette/tests/get_next_line/fsoares/only_nl.txt", O_RDONLY);
	//fd = open("/Users/tvalimak/francinette/tests/get_next_line/fsoares/multiple_nl.txt", O_RDONLY);
	line = get_next_line(fd);
    printf("GNL 1: %s", line);
    printf("GNL 2: %s", get_next_line(fd));
    printf("GNL 3: %s", get_next_line(fd));
    printf("GNL 4: %s", get_next_line(fd));
    printf("GNL 5: %s", get_next_line(fd));
    printf("GNL 6: %s", get_next_line(fd));
    printf("GNL 7: %s", get_next_line(fd));
    printf("GNL 8: %s", get_next_line(fd));
    printf("GNL 9: %s", get_next_line(fd));
    printf("GNL10: %s", get_next_line(fd));
    printf("GNL11: %s", get_next_line(fd));
    printf("GNL12: %s", get_next_line(fd));
	free (line);
    close(fd);
}
