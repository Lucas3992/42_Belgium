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

		bool operator>(Fixed const &other) const;
		bool operator<(Fixed const &other) const;
		bool operator>=(Fixed const &other) const;
		bool operator<=(Fixed const &other) const;
		bool operator==(Fixed const &other) const;
		bool operator!=(Fixed const &other) const;

		Fixed operator-(Fixed const &other) const;
		Fixed operator+(Fixed const &other) const;
		Fixed operator*(Fixed const &other) const;
		Fixed operator/(Fixed const &other) const;

		Fixed &operator++();
		Fixed operator++(int);
		Fixed &operator--();
		Fixed operator--(int);

		static Fixed&		min(Fixed& a, Fixed& b);
		static Fixed const& min(Fixed const& a, Fixed const& b);
		static Fixed&		max(Fixed& a, Fixed& b);
		static Fixed const&	max(Fixed const& a, Fixed const& b);
};

std::ostream& operator<<(std::ostream& stream, const Fixed& f);

#endif