#include "../inc/ray_tracer.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstring(char *s)
{
	int	i = 0;

	while(s[i] != '\0')
	{
		ft_putchar(s[i]);
		i++;
	}
}

char *float_to_ascii(float value)
{
    int int_part = (int)value;
    int decimal_part = (int)((value - int_part) * 1000); // Adjust precision as needed
    char *str = malloc(sizeof(char) * (12 + 3)); // Allocate memory for string

    if (str == NULL) {
        return NULL; // Handle memory allocation failure
    }

	sprintf(str, "%d.%03d", int_part, decimal_part);

    return str;
}

void	ft_tuple_print(t_tuple *t)
{
	ft_putstring("x: ");
	ft_putstring((char*)float_to_ascii(t->x));
	ft_putstring("\ny: ");
	ft_putstring((char*)float_to_ascii(t->y));
	ft_putstring("\nz: ");
	ft_putstring((char*)float_to_ascii(t->z));
	ft_putstring("\nw: ");
	if (t->w == VECTOR)
		ft_putstring("VECTOR\n");
	else
		ft_putstring("POINT\n");
}