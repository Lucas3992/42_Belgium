#ifndef ICHARACTER_HPP
# define ICHARACTER_HPP

# include <iostream>
# include "AMateria.hpp"

class AMateria;
class Floor;

class ICharacter {
    public:
        ICharacter();
        ICharacter(const ICharacter& other);
        ICharacter& operator=(const ICharacter& other);
        virtual ~ICharacter();

        virtual std::string const &getName() const = 0;
		
    	virtual void equip(AMateria *m) = 0;
    	virtual void unequip(int idx) = 0;
    	virtual void use(int idx, ICharacter &target) = 0;
};

class Character : public ICharacter {
    private:
        std::string const name;
        AMateria* inventory[4];
        static Floor floor;
    public:
        Character();
        Character(std::string const& name);
        Character(const Character& other);
        Character& operator=(const Character& other);
        ~Character();

        std::string const& getName() const ;
    	void equip(AMateria *m);
    	void unequip(int idx);
    	void use(int idx, ICharacter& target);
};

class Floor {
    private:
        AMateria* limit[4];
        int index;
    public:
        Floor();
        Floor(const Floor& other);
        Floor& operator=(const Floor& other);
        ~Floor();

        void drop(AMateria* m);
};

#endif
