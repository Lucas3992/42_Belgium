#ifndef WRONG_HPP
# define WRONG_HPP

# include <iostream>

class WrongAnimal {
	protected:
		std::string	type;
	public:
		WrongAnimal();
		WrongAnimal(const WrongAnimal &other);
		WrongAnimal& operator=(const WrongAnimal& other);
		~WrongAnimal();

		std::string	getType() const;
		void		makeSound() const;
};

class WrongCat: public WrongAnimal {
	public:
		WrongCat();
		WrongCat(const WrongCat& other);
		WrongCat& operator=(const WrongCat& other);
		~WrongCat();

		void	makeSound() const;
};

# define RED     "\033[31m"
# define RESET   "\033[0m"

#endif