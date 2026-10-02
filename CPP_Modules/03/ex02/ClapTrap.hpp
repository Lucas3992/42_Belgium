#ifndef CLAPTRAP_HPP
# define CLAPTRAP_HPP

# include <iostream>

class ClapTrap {
    protected:
        std::string		name;
        int	hp;
		int	ep;
		int	ad;
        int maxHp;
    public:
		ClapTrap();
        ClapTrap(const std::string name);
        ClapTrap(const ClapTrap& other);
        ClapTrap& operator=(const ClapTrap& other);
        ~ClapTrap();

        void attack(const std::string &target);
        void takeDamage(unsigned int amount);
        void beRepaired(unsigned int amount);

		void setAd(unsigned int newAd);
		};

#endif