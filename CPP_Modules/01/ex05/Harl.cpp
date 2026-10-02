#include "Harl.hpp"

void Harl::debug()
{
    std::cout   << "I love having extra bacon for my 7XL-double-cheese-"
                << "triple-pickle-special-ketchup burger. I really do!\n";
}

void Harl::info()
{
    std::cout   << "I cannot believe adding extra bacon costs more money."
                << " You didn't put enough bacon in my burger!"
                << " If you did, I wouldn't be asking for more!\n";
}

void Harl::warning()
{ 
    std::cout	<< "I think I deserve to have some extra bacon for free."
                << " I've been coming for years, whereas you started working"
                << " here just last month.\n";
}

void Harl::error()
{ 
    std::cout   << "This is unacceptable! I want to speak to the manager now.\n";
}


Harl::Harl() {}

void Harl::complain(std::string level)
{
	void		(Harl::*actions[4])();
	std::string	levels[4];

	actions[0] = &Harl::debug;
	actions[1] = &Harl::info;
	actions[2] = &Harl::warning;
	actions[3] = &Harl::error;
	levels[0] = "DEBUG";
	levels[1] = "INFO";
	levels[2] = "WARNING";
	levels[3] = "ERROR";

	for (int i = 0; i < 4; i++)
	{
		if (levels[i] == level)
		{
			(this->*actions[i])();
			return;
		}
	}
}
