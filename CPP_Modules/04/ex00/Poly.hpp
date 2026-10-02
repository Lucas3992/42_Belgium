#ifndef POLY_HPP
# define POLY_HPP

# include <string>
# include <iostream>

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
public:
    Dog();
    Dog(const Dog& other);
    Dog& operator=(const Dog& other);
    ~Dog();
    virtual void makeSound() const;
};

class Cat: public Animal {
public:
    Cat();
    Cat(const Cat& other);
    Cat& operator=(const Cat& other);
    ~Cat();
    virtual void makeSound() const;
};

#endif