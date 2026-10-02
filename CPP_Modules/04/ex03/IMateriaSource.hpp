#ifndef IMATERIASOURCE_HPP
# define IMATERIASOURCE_HPP

# include "AMateria.hpp"

class IMateriaSource {
	public:
		IMateriaSource();
		IMateriaSource(const IMateriaSource& other);
		IMateriaSource& operator=(const IMateriaSource& other);
		virtual ~IMateriaSource();

		virtual void learnMateria(AMateria* m) = 0;
		virtual AMateria* createMateria(std::string const& type) = 0;
};

class MateriaSource : public IMateriaSource {
	private:
		AMateria* slots[4];
	public:
		MateriaSource();
		MateriaSource(const MateriaSource& other);
		MateriaSource& operator=(const MateriaSource& other);
		virtual ~MateriaSource();

		void learnMateria(AMateria* m);
		AMateria* createMateria(std::string const& type);
};

#endif