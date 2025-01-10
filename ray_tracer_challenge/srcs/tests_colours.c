#include "../inc/ray_tracer.h"

void	tests_colours(void)
{

	//-------- Colours --------
	print_y("Colours are (red, green, blue) tuples\n");
	t_colour *c0 = create_colour(-0.5, 0.4, 1.7);
	ft_colour_printer(c0);
	ft_print_line('-');

    t_colour *c1 = create_colour(0.9, 0.6, 0.75);
    t_colour *c2 = create_colour(0.7, 0.1, 0.25);

	print_y("Adding colours\n");
    t_colour *c3 = add_colours(c1, c2);
    ft_colour_printer(c3);
    ft_print_line('-');

    print_y("Subtracting colours\n");
    t_colour *c4 = subtract_colours(c1, c2);
     ft_colour_printer(c4);
    ft_print_line('-');

    print_y("Multiplying a colour by a scalar\n");
    t_colour *c5 = create_colour(0.2, 0.3, 0.4);
    t_colour *c6 = multiply_colour_by(c5, 2);
    ft_colour_printer(c6);
    ft_print_line('-');

    print_y("Multiplying colours - hadamard_product\n");
    t_colour *c7 = create_colour(1, 0.2, 0.4);
    t_colour *c8 = create_colour(0.9, 1, 0.1);
    t_colour *c9 = hadamard_product(c7, c8);
    ft_colour_printer(c9);
    ft_print_line('-');

    free(c0);
    free(c1);
    free(c2);
    free(c3);
    free(c4);
    free(c5);
    free(c6);
    free(c7);
    free(c8);
    free(c9);
}