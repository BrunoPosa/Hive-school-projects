#include "../inc/ray_tracer.h"

int    ft_strlen(char *s)
{
    int i = 0;

    while (*s++)
        i++;

    return i;
}

char *ft_strjoin(char* a, char *b)
{
    int i = ft_strlen(a);
    int j = ft_strlen(b);
    int k = 0;

    char *c = malloc(sizeof(char) * (i + j + 1));
    if (!c)
    {
        free(c);
        return NULL;
    }
    while(*a)
    {
        c[k++] = *a++;

    }
    while(*b)
    {
        c[k++] = *b++;
    }

    c[k] = '\0';
    return c;
}
// #include <stdio.h>
// int main(void)
// {
//     char *a="te";
//     char *b="st";

//     char *c = ft_strjoin(a, b);
//     printf("%s",c);
// }
