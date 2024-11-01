#include "../inc/file_to_list.h"

char    *skip_space(char *s)
{
    if (!s)
        return (NULL);
    while(*s == ' ')
            s++;
    return (s);
}

// sturct->s = skip_space(stuct->s);

