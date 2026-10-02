#ifndef ZOMBIE_HPP
# define ZOMBIE_HPP

# include <iostream>
# include <cctype>

class Zombie {
	private:
		std::string	nameTag;
	public:
		Zombie();
		~Zombie();
		void	announce();
		void	setName(std::string name);
};

Zombie*	zombieHorde(int N, std::string name);

#endif