#ifndef FIXED_HPP
# define FIXED_HPP

# include <iostream>
# include <math.h>

class Fixed {
    private:
        int                 value;
        static const int    fract = 8;
    public:
        Fixed();
        Fixed(const int n);
        Fixed(const float fl);
		Fixed(const Fixed& src);
		Fixed& operator=(const Fixed& src);
        ~Fixed();
        int 	getRawBits() const;
        void	setRawBits(int const raw);
        int     toInt() const;
        float   toFloat() const;
};

std::ostream& operator<<(std::ostream& stream, const Fixed& f);

#endif