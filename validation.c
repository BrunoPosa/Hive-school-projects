#include "philo.h"

static int	my_isdigit(int c)
{
	if (c >= 48 && c <= 57)
	{
		return (1);
	}
	return (0);
}

static size_t	my_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

static int	aredigits(char **s)
{
	int i;

	i = 0;
	while (*(++s))
	{
		i = 0;
		if ((*s)[i] == '\0')
			return (0);
		while ((*s)[i])
		{
			if (my_isdigit((*s)[i++]) == 0)
				return (0);
		}
	}
	return (1);
}

static int	islenok(char **s)
{
	if (my_strlen(s[1]) > 4
		|| my_strlen(s[2]) > 4
		|| my_strlen(s[3]) > 4
		|| my_strlen(s[4]) > 4)
		return (0);
	if (s[5])
	{
		if (my_strlen(s[5]) > 4)
			return (0);
	}
	return (1);
}

int	validator(int argc, char **args)
{
	if (argc < 5 || argc > 6)
		return (errs(EARGC));
	if (aredigits(args) != 1 || islenok(args) != 1)
		return (errs(EARG));
	return (1);
}