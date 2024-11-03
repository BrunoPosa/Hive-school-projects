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

int count_commas(char *s, int target)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while (s[i])
    {
        if (s[i] == ',')
            count++;
        i++;
    }
    if (target == -1)
        return (count);
    if (count != target)
        return (0);
    return (1);
}

