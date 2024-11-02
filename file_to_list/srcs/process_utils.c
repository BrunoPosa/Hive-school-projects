#include "../inc/file_to_list.h"

int len_until_space(char *s)
{
    int i;

    i = 0;
    while (s[i] && s[i] != ' '
                    && s[i] != '\n'
                    && s[i] != '\0')
                    // or EOF?
        i++;
    return (i);
}

