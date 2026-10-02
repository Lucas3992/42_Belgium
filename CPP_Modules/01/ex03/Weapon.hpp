#ifndef WEAPON_H
# define WEAPON_H

# include <iostream>

class Weapon {
    private:
        std::string type;
    public:
        Weapon(std::string	weaponName);
        const std::string&	getType();
        void 				setType(const std::string& newType);
};

#endif