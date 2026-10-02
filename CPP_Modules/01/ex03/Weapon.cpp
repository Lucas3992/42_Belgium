#include "Weapon.hpp"

Weapon::Weapon(std::string weaponName) : type(weaponName) {}

const std::string& Weapon::getType()
{
	return type;
}

void Weapon::setType(const std::string& newType)
{
	type = newType;
}
