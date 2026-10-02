#ifndef FIXED_HPP
# define FIXED_HPP

# include <iostream>
//int value cest le float * 2^fract donc * 256
class Fixed {
    private:
        int                 value;
        static const int    fract = 8;
    public:
        Fixed();
		Fixed(const Fixed& src);
		Fixed& operator=(const Fixed& src);
        ~Fixed();
        int 	getRawBits() const;
        void	setRawBits(int const raw);
};

#endif