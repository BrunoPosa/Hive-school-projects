#include "../inc/ray_tracer.h"

void	tests_canvas(void)
{

	//-------- Canvas --------
	

    // print_y("Create canvas\n");
    // t_colour **c = create_canvas(10, 20);
    // printf("here is position [2][2] initialised to 0,0,0:\n");
    // ft_colour_printer(&c[2][2]);
    // ft_print_line('-');

    // print_y("Writing pixels to a canvas\n");
    // t_colour *red = create_colour(1, 0, 0);
    // write_pixel(c, 2, 3, red);
    // printf("pixel in position [2][3] is now red, while others are black\n");
    // ft_colour_printer(&c[2][2]);
    // ft_colour_printer(&c[2][3]);
    // ft_colour_printer(&c[2][4]);
    // ft_print_line('-');

    // print_y("Can we find out the size of our canvas?\n");
    // printf("x = 10, y = 20 is the target\n");
    // printf("x = %zu, y = %zu\n", x_of_canvas(c), y_of_canvas(c));
    // printf("we are doing this by i/2-1 which doesn't work because of rounding\n");


    print_y("Canvas to PPY\n");
    t_colour **canvas0 = create_canvas(5, 3);
    t_colour *c1 = create_colour(1.5, 0, 0);
    t_colour *c2 = create_colour(0, 0.5, 0);
    t_colour *c3 = create_colour(-0.5, 0, 1);
    ft_colour_printer(c1);
    ft_colour_printer(c2);
    ft_colour_printer(c3);
    write_pixel(canvas0, 0, 0, c1);
    write_pixel(canvas0, 2, 1, c2);
    write_pixel(canvas0, 4, 2, c3);
    canvas_to_print(canvas0, 5, 3);
    ft_print_line('-');

    // print_y("Testing float_to_uint\n");
    // printf("0.0f should be 0, 1.0f should be 255\n");
    // printf("1.5f should be 255, 0.5f should be 128, -0.5f should be 0\n");
    // printf("%d %d %d\n", float_to_uint(1.5), float_to_uint(0.5), float_to_uint(-0.5));
    // ft_print_line('-');
    // canvas_to_print(canvas0, 5, 3);
    // canvas_to_ppm("output1.ppm", canvas0, 5, 3);
    // ft_print_line('-');

    // print_y("Splitting long lines in PPM files\n");
    // t_colour **canvas1 = create_canvas(10, 2);
    // t_colour *init_value = create_colour(1, 0.8, 0.6);
    // init_canvas(canvas1, 10, 2, init_value);
    // canvas_to_print(canvas1, 10, 2);
    // canvas_to_ppm("long_lines.ppm", canvas1, 10, 2);



  
}