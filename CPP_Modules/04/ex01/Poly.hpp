#ifndef POLY_HPP
# define POLY_HPP

# include <string>
# include <iostream>
# include "Brain.hpp"

class Animal {
protected:
    std::string type;
public:
    Animal();
    Animal(const Animal& other);
    Animal& operator=(const Animal& other);
    virtual ~Animal();
    std::string getType() const;
    virtual void makeSound() const;
};

class Dog: public Animal {
private:
    Brain* brain;
public:
    Dog();
    Dog(const Dog& other);
    Dog& operator=(const Dog& other);
    ~Dog();
    virtual void makeSound() const;
};

class Cat: public Animal {
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
# define BLUE    "\033[34m"
# define RESET   "\033[0m"

#endif