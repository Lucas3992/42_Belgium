#include <cctype>
#include <iostream>

int main(int ac, char **av)
{
	char c;

	if (ac == 1)
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *";
	else
	{
		for (int i = 1; av[i]; i++)
		{
			for (int j = 0; av[i][j]; j++)
			{
				c = std::toupper((unsigned char)av[i][j]);
				std::cout << c;
			}
		}
	}
	std::cout << "\n";
	return 0;
}
