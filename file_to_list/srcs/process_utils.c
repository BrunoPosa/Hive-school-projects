#include "../inc/file_to_list.h"

int len_until_space(char *s)
{
    int i;

    i = 0;
    if (!s)
        return (0);
    while (s[i] && s[i] != ' '
                    && s[i] != '\n'
                    && s[i] != '\0')
                    // or EOF?
        i++;
    return (i);
}

int count_commas(char *s, int target)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while (s[i])
    {
        if (s[i] == ',')
            count++;
        i++;
    }
    if (target == -1)
        return (count);
    if (count != target)
        return (0);
    return (1);
}

/**
 * Returns the number of commas separated by characters in s.
 * Returns -1 if:
 *   - comma is the first or last character in s,
 *   - two commas are consecutive,
 *   - s is null.
 */
int	count_commas_between(char *s)
{
	int	comma;
	int i;

	comma = 0;
	i = 0;
	if (!s)
		return (-1);
	while (s[i] && i < __INT_MAX__)
	{
		if (s[i] == ',')
		{
			if (i == 0 || s[i + 1] == '\0'
				|| (s[i + 1] == ','))
				return (-1);
			comma++;
		}
		i++;
	}
	return (comma);
}

void	free_array(char **s)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}