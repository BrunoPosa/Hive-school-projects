#include "../inc/file_to_list.h"

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
	//the commented was just a test, but it seems not to be needed
	p->r = a->r - b-> r;// fmax(EPSILON, a->r - b-> r);
	p->g = a->g - b-> g; //fmax(EPSILON, a->g - b-> g);
	p->b = a->b - b-> b;//fmax(EPSILON, a->b - b-> b);

	return p;
}
t_colour   *multiply_colour_by(t_colour *a, float scaler)
{
	t_colour *p;

	p = NULL;
	p = malloc(sizeof(t_colour));
	if(!a || !p)
		return NULL;
	p->r = a->r * scaler;
	p->g = a->g * scaler;   
	p->b = a->b * scaler;    

	return p;
}

t_colour   *hadamard_product(t_colour *a, t_colour *b)
{
	t_colour *p;
	p = malloc(sizeof(t_colour));
	if(!a || !b || !p)
		return NULL;
	//normalize
	p->r = (a->r / 255.0) * (b->r / 255.0) * 255.0;
	p->g = (a->g / 255.0) * (b->g / 255.0) * 255.0;
	p->b = (a->b / 255.0) * (b->b / 255.0) * 255.0;
	//chatgpt suggests following instead, as it's more efficient:
	//     p->r = fmax(fmin(a->r * b->r / 255.0, 255.0), 0.01);
    // p->g = fmax(fmin(a->g * b->g / 255.0, 255.0), 0.01);
    // p->b = fmax(fmin(a->b * b->b / 255.0, 255.0), 0.01);
	return p;
}
