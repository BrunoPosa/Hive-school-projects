#include "../inc/file_to_list.h"

int find_len_until_illegal(char *s)
{
    int i;

    i = 0;
    while (s[i] && s[i] != ' ')
        i++;
    return (i);
}

