#include "../inc/file_to_list.h"

char    *skip_space(char *s)
{
	if (!s)
		return (NULL);
	while(*s == ' ')
			s++;
	return (s);
}

// sturct->content = skip_space(stuct->content);
int	does_file_end_with_rt(char *filename)
{
	int len;

	len = ft_strlen(filename);
	if (len < 3)
		return (0);
	if (ft_strncmp(&filename[len - 3], ".rt", 3))
		return (0);
	return (1);
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
		while (s[i] && (s[i] == ' ' && s[i+1] == ' '))
			i++;
		r[j] = s[i];
		j++;
		i++;
	}
	r[i] = '\0';
	return r;
}

char*	process2(char *s)
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
		while (s[i] && (s[i] == '\t' && s[i+1] == '\t'))
			i++;
		r[j] = s[i];
		j++;
		i++;
	}
	r[i] = '\0';
	return r;
}

// void    tab_to_space(char *s)
// {
//     int i;
//     // char *r;

//     i = 0;
//     // i = ft_strlen(s);
//     // r = malloc(i + 1);
//     while(s[i])
//     {
//         if(s[i] == '\t')
//             s[i] = ' ';
//         i++
//     }
// }