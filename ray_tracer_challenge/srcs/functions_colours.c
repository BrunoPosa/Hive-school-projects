#include "../inc/ray_tracer.h"

t_colour   *add_colours(t_colour *a, t_colour *b)
{
    t_colour *p;
    p = malloc(sizeof(t_colour));
    if(!a || !b || !p)
        return NULL;
    p->r = a->r + b-> r;
    p->g = a->g + b-> g;   
    p->b = a->b + b-> b;    

    return p;
}
t_colour   *subtract_colours(t_colour *a, t_colour *b)
{
    t_colour *p;
    p = malloc(sizeof(t_colour));
    if(!a || !b || !p)
        return NULL;
    p->r = a->r - b-> r;
    p->g = a->g - b-> g;   
    p->b = a->b - b-> b;    

    return p;
}
t_colour   *multiply_colour_by(t_colour *a, float scaler)
{
    t_colour *p;
    p = malloc(sizeof(t_colour));
    if(!a || !p)
        return NULL;
    p->r = a->r * scaler;
    p->g = a->g * scaler;   
    p->b = a->b * scaler;    

    return p;
}

t_colour   *multiply_colours(t_colour *a, t_colour *b)
{
    t_colour *p;
    p = malloc(sizeof(t_colour));
    if(!a || !b || !p)
        return NULL;
    p->r = a->r * b-> r;
    p->g = a->g * b-> g;   
    p->b = a->b * b-> b;    

    return p;
}