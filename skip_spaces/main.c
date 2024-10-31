#include <stdio.h>
#include <stdlib.h>

size_t	ft_strlen(char *s)
{
	size_t i;
	while(s[i] != '\0')
	{
		i++;
	}
	return i;
}

void    tab_to_space(char *s)
{
	int i;
        // char *r;
        i = 0;
		    // i = ft_strlen(s);
		    // r = malloc(i + 1);
	while(s[i])
	{
		if(s[i] == ' ')
	            s[i] = 'x';
	        i++;
	}
}

char*	process(char *s)
{
	int l;
	char *r;
	int i;
	int j;

	i = 0;
	j = 0;
	l = ft_strlen(s);
	r = malloc(l + 1);

	while (s[i] && s[i] == ' ')
		i++;

	while (s[i])
	{
		while (s[i] && s[i] == ' ' && s[i+1] == ' ')
			i++;
		r[j] = s[i];
		j++;
		i++;
	}
	r[i] = '\0';
	return r;
}

int	main(void)
{
	char* s1= "  hello there     how are you    ?     ";
	printf("%s\n", s1);
	printf("%s\n", process(s1));
	tab_to_space(s1);
	printf("%s\n", s1);
}
