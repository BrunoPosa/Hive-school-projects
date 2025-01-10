#include <stdio.h>
#include "../libft/libft.h"

typedef struct s_rgb
{
	unsigned int r;
	unsigned int g;
	unsigned int b;
} t_rgb;


int main (void)
{
	char *test1="123,1,52";
	char *test2="255,0,0";
	char *test3="256,9,";
	char *test4="-1,3,3";
	char** r =  split_string = test1;
	// convert char**  to int;
	// check r[i] is >=0 <0 255;


	t_rgb   rgb;
	int		i = 0;
	char *temp;
	temp = malloc(4 * sizeof(char));

	while (test1[i] != 0 && test1[i] != ',')
	{
		temp[i  < 3] = ft_atoi(test1[i]);
		i++;
		temp='\n';
	}

	printf("%d, %d, %d\n", rgb.r, rgb.g, rgb.b);
	return (0);
}