#ifndef AMATERIA_HPP
# define AMATERIA_HPP

# include <iostream>
# include "ICharacter.hpp"

class ICharacter;

class AMateria {
    protected:
		std::string type;
    public:
		AMateria();
        AMateria(std::string const& t);
		AMateria(const AMateria& other);
		AMateria& operator=(const AMateria& other);
		virtual ~AMateria();

        std::string const& getType() const; // Returns the materia type

    	virtual AMateria *clone() const = 0;
    	virtual void use(ICharacter &target) = 0;
};

class Ice : public AMateria {
	public:
		Ice();
		Ice(const Ice& other);
		Ice& operator=(const Ice& other);
		~Ice();

		void use(ICharacter& target);
		Ice* clone() const;
};

class Cure : public AMateria {
	public:
		Cure();
		Cure(const Cure& other);
		Cure& operator=(const Cure& other);
		~Cure();

		Cure* clone() const;
		void use(ICharacter& target);
};


# define RED     "\033[31m"
# define GREEN   "\033[32m" 
# define BLUE    "\033[34m"
# define RESET   "\033[0m"

#endif