#include "../inc/ray_tracer.h"

int init_canvas(t_colour **canvas, int x, int y, t_colour *init_value)
{
    int i;
    int j;
    
    i = 0;
    j = 0;

    while(i < y)
    {
        while(j < x)
        {
            canvas[i][j] = *init_value;
            j++;
        }
        i++;
        j = 0;
    }
    return 0; 
}

// x = horizontal, y = vertical
t_colour **create_canvas(int x, int y)
{
    int i;
    int j;
    t_colour **canvas;
    // t_colour *init_value = create_colour(0, 0, 0);
    // t_colour *init_value = create_colour(1, 0.8, 0.6);

    i = 0;
    j = 0;
    canvas = (t_colour **)malloc(x * sizeof(t_colour *));

    if (canvas == NULL)
    {
        printf("Malloc failed!\n");
        return NULL;
    }

    while(i < x)
    {
        canvas[i] = (t_colour *)malloc(y * sizeof(t_colour));
        if (canvas[i] == NULL)
        {
            printf("Malloc failed for row %d!\n", i);
            while(j < i)
            {
                free(canvas[j]);
                j++;
            }
            free(canvas);
            return NULL;
        }
        i++;
    }
    // init_canvas(canvas, x, y, init_value);
    return canvas;
}

// this is unused
size_t  x_of_canvas(t_colour **canvas)
{
    size_t i = 0;
    while(canvas[i])
        i++;
    return i;
}
// this is wonky donky
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
        float r = value * 255.0f;
        float fractol = value - (int)value;
        if (fractol >= 0.5)
            r += 0.5;
        return (unsigned int)r;
    }
}
void canvas_to_print(t_colour **canvas, int x, int y)
{
    int i, j;
    i = 0;
    j = 0;

    printf("P3\n%d %d\n255\n", x, y);
    while (i < y)
    {
        while (j < x)
        {
            if (j == 0)
            {
                printf("%d %d %d",
                    float_to_uint(canvas[i][j].r),
                    float_to_uint(canvas[i][j].g),
                    float_to_uint(canvas[i][j].b));
                    j++;
            }
            printf(" %d %d %d",
                float_to_uint(canvas[i][j].r),
                float_to_uint(canvas[i][j].g),
                float_to_uint(canvas[i][j].b));
            j++;
        }
        printf("\n");
        j = 0;
        i++;
    }
}

void canvas_to_ppm(char *filename, t_colour **canvas, int y, int x)
{
    int i, j;
    i = 0;
    j = 0;

    FILE *fp = fopen(filename, "w");
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
