#ifndef POLY_HPP
# define POLY_HPP

# include <string>
# include <iostream>
# include "Brain.hpp"

class AAnimal {
protected:
    std::string type;
public:
    AAnimal();
    AAnimal(const AAnimal& other);
    AAnimal& operator=(const AAnimal& other);
    virtual ~AAnimal();

    std::string getType() const;
    virtual void makeSound() const = 0;
};

class Dog: public AAnimal {
private:
    Brain* brain;
public:
    Dog();
    Dog(const Dog& other);
    Dog& operator=(const Dog& other);
    ~Dog();
    virtual void makeSound() const;
};

class Cat: public AAnimal {
private:
    Brain* brain;
public:
    Cat();
    Cat(const Cat& other);
    Cat& operator=(const Cat& other);
    ~Cat();
    virtual void makeSound() const;
};

# define RED     "\033[31m"
# define YELLOW  "\033[33m"
# define RESET   "\033[0m"

#endif