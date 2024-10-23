#include "../inc/ray_tracer.h"

int init_canvas(t_colour **img, int x, int y)
{
    int i;
    int j;
    
    i = 0;
    j = 0;

    while(i < x)
    {
        while(j < y)
        {
            img[i][j] = *create_colour(0, 0, 0);
            j++;
        }
        i++;
    }
    return 0; 
}

// x = horizontal, y = vertical
t_colour **create_canvas(int x, int y)
{
    int i;
    int j;
    t_colour **img;

    i = 0;
    j = 0;
    img = (t_colour **)malloc(x * sizeof(t_colour *));

    if (img == NULL)
    {
        printf("Malloc failed!\n");
        return NULL;
    }

    while(i < x)
    {
        img[i] = (t_colour *)malloc(y * sizeof(t_colour));
        if (img[i] == NULL)
        {
            printf("Malloc failed for row %d!\n", i);
            while(j < i)
            {
                free(img[j]);
                j++;
            }
            free(img);
            return NULL;
        }
        i++;
    }

    init_canvas(img, x, y);
    return img;
}
