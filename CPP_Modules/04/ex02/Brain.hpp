#ifndef BRAIN_HPP
# define BRAIN_HPP

# include <iostream>

class Brain {
private:
    std::string ideas[100];
public:
    Brain();
    Brain(const Brain& other);
    Brain& operator=(const Brain& other);
    ~Brain();
};

# define GREEN   "\033[32m" 
# define RESET   "\033[0m"

#endif