#include "Harl.hpp"

int main(int ac, char **av)
{
    std::string level;
    Harl        h;

    if (ac != 2)
        return 1;
    level = av[1];
    h.complain(level);
    return 0;
}
