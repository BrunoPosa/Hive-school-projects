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

void ft_ftoa(float n, char *res, int afterpoint)
{
	int ipart = (int)n;
	float fpart = n - (float)ipart;
	int i = 0;

	if (n < 0)
	{
		res[i++] = '-';
		ipart = -ipart;
		fpart = -fpart;
	}
	if (ipart == 0)
		res[i++] = '0';
	else
	{
		while (ipart)
		{
			res[i++] = ipart % 10 + '0';
			ipart = ipart / 10;
		}
	}
	if (fpart != 0)
	{
		res[i++] = '.';
		fpart = fpart * pow(10, afterpoint);
		ipart = (int)fpart;
		while (afterpoint--)
		{
			res[i++] = ipart % 10 + '0';
			ipart = ipart / 10;
		}
	}
	res[i] = '\0';
}

void	ft_tuple_print(t_tuple *t)
{
	ft_putstring("x: ");
	ft_putstring(ft_ftoa(t->x));
	ft_putstring("\ny: ");
	ft_putstring(ft_ftoa(t->y));
	ft_putstring("\nz: ");
	ft_putstring(ft_ftoa(t->z));
	ft_putstring("\nw: ");
	if (t->w == VECTOR)
		ft_putstring("VECTOR\n");
	else
		ft_putstring("POINT\n");
}