#include "../inc/file_to_list.h"

int	only_legal_chars_n(char *s, char *legal, int n)
{
	int	i;

	i = -1;
	while(s[++i] && i < n)
	{
		if (ft_strchr(legal, s[i]) == NULL)
		{
			printf("i=%d\n", i);
            printf("%s\n", s);
			return (0);
		}
		n--;
	}
	return (1);
}

int	only_legal_chars(char *s, char *legal)
{
	int	i;

	i = -1;
	while(s[++i])
	{
		if (ft_strchr(legal, s[i]) == NULL)
		{
			printf("i=%d\n", i);
            printf("%s\n", s);
			return (0);
		}
	}
	return (1);
}

int	list_legality_check(t_list **l, char *legal)
{
    t_list *current = *l;

    while (current)
	{	
			
		if(!only_legal_chars(current->s, legal))
		{
			printf("KO - illegal char!\n");
			return 0;
		}
		current = current->next;
	}
	printf("OK - File has only legal chars.\n");
	return 1;
}

