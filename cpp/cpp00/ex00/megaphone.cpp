#include <iostream>

int main(int ac, char **av)
{
	int	i = 1;
	int	k = 0;


	if (!av)
		return (1);

	if (ac == 1)
	{
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *\n";
		return (0);
	}
	while (av && av[i])
	{
		k = 0;
		while (av && av[i][k])
		{
			av[i][k] = std::toupper((unsigned char)av[i][k]);
			k++;
		}
		i++;
	}

	i = 0;
	while (av && av[++i])
		std::cout << av[i] << ' ';

	std::cout << '\n';
	return (0);
}
