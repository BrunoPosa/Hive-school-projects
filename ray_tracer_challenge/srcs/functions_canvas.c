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

unsigned int float_to_uint(float value)
{
    if (value < 0.0f)
    {
        return 0;
    }
    
    else if (value > 1.0f)
    {
        return 255;
    }
    
    else
    {
        return (unsigned int)(value * 255.0f);
    }
}

void canvas_to_ppm(t_colour **canvas, int x, int y)
{
    int i, j;
    i = 0;
    j = 0;

    FILE *fp = fopen("example.ppm", "w");
    if (fp == NULL)
    {
        perror("Error opening file");
        return;
    }

    fprintf(fp, "P3\n%d %d\n255\n", x, y);
    while (i < y)
    {
        while (j < x)
        {
            if (j == 0)
            {
                fprintf(fp, "%d %d %d",
                    float_to_uint(canvas[i][j].r),
                    float_to_uint(canvas[i][j].g),
                    float_to_uint(canvas[i][j].b));
                    j++;
            }
            fprintf(fp, " %d %d %d",
                float_to_uint(canvas[i][j].r),
                float_to_uint(canvas[i][j].g),
                float_to_uint(canvas[i][j].b));
            j++;
        }
        fprintf(fp, "\n");
        j = 0;
        i++;
    }
    fclose(fp);
}
