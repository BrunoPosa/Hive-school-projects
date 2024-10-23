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

size_t  x_of_canvas(t_colour **canvas)
{
    size_t i = 0;
    while(canvas[i])
        i++;
    return i;
}

size_t  y_of_canvas(t_colour **canvas)
{
    size_t i = 0;
    print_r("WARNING Y_OF_CANVAS IS WONKY DONKY\n");
    while(canvas[0][i].r == 0)
        i++;
    return (i/2 - 1);
}

// char *line_of_canvas()
// {
//     //make a line of tuples in to x,x,x in a string.
// }


// char    *canvas_to_ppm(t_colour **canvas)
// {
//     size_t i = x_of_canvas(canvas);

//     char *s1="P3\n5 3\n255";

//     char **s2[x]

//     s2 = malloc(sizeof(char) * x_of_canvas * y_of_canvas * )

//     while(i)




//     return (ft_strjoin(s1, s2));

// }