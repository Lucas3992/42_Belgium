#include "ICharacter.hpp"

ICharacter::ICharacter() {}

ICharacter::ICharacter(const ICharacter &other) {
	(void)other;
}

ICharacter &ICharacter::operator=(const ICharacter &other) {
	(void)other;
	return *this;
}

ICharacter::~ICharacter() {}

Character::Character() : name("unknown") {
	for (int i = 0; i < 4; i++)
		inventory[i] = 0;
}

Character::Character(std::string const &n) : name(n) {
	for (int i = 0; i < 4; i++)
		inventory[i] = 0;
}

Character::Character(const Character &other) : ICharacter(other), name(other.name) {
	for (int i = 0; i < 4; i++) {
		if (other.inventory[i])
			inventory[i] = other.inventory[i]->clone();
		else
			inventory[i] = 0;
	}
}

Character &Character::operator=(const Character &other) {
	if (this != &other) {
		for (int i = 0; i < 4; i++) {
			delete inventory[i]; // dabord delete sinon ecrase et donc leak
			if (other.inventory[i])
				inventory[i] = other.inventory[i]->clone();
			else
				inventory[i] = 0;
		}
	}
	return *this;
}

Character::~Character() {
	for (int i = 0; i < 4; i++)
		delete inventory[i];
}

std::string const &Character::getName() const {
	return name;
}

void Character::equip(AMateria *m) {
	if (!m)
		return;
	for (int i = 0; i < 4; i++) {
		if (inventory[i] == m)//deja possedee
			return ;
	}
	for (int i = 0; i < 4; i++) {
		if (!inventory[i]) {
			inventory[i] = m;//slot libre donc on equipe
			return ;
		}
	}
	floor.drop(m);
	std::cout << RED << name << " dropped " << m->getType() << " on the floor because inventory is full\n" << RESET;
}

void Character::unequip(int idx) {
	if ((idx < 0 || idx > 3) || !inventory[idx])
		return;
	floor.drop(inventory[idx]);
	std::cout << name << " dropped " << inventory[idx]->getType() << " to the floor\n";
	inventory[idx] = NULL;
}

void Character::use(int idx, ICharacter &target) {
	if (idx < 0 || idx > 3) {
		std::cout << RED << "Index must be between 0 and 3\n" << RESET;
		return;
	}
	if (!inventory[idx]) {
		std::cout << RED << "Empty slot\n" << RESET;
		return;
	}
	inventory[idx]->use(target);
}

Floor::Floor() : index(0) {
	for (int i = 0; i < 4; i++)
		limit[i] = 0;
}

Floor::Floor(const Floor &other) : index(other.index) {
	for (int i = 0; i < 4; i++)
		limit[i] = 0;
	for (int i = 0; i < 4; i++)
	{
		if (other.limit[i])
			limit[i] = other.limit[i]->clone();
	}
}

Floor &Floor::operator=(const Floor &other) {
	if (this != &other) {
		for (int i = 0; i < 4; i++)
		{
			delete limit[i]; // dabord delete sinon ecrase et donc leak
			if (other.limit[i])
				limit[i] = other.limit[i]->clone();
			else
				limit[i] = 0;
		}
		index = other.index;
	}
	return *this;
}

Floor::~Floor() {
	for (int i = 0; i < 4; i++)
		delete limit[i];
}

Floor Character::floor; // cree une seule fois le sol commun avant le main

void Floor::drop(AMateria *m) {
	if (!m)
		return;
	if (limit[index])
		delete limit[index];
	limit[index] = m;
	index = (index + 1) % 4;
}
