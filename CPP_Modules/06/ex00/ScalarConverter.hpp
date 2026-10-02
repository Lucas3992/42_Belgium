#ifndef SCALARCONVERTER_HPP
# define SCALARCONVERTER_HPP

# include <iostream>
# include <limits>
# include <cmath>
# include <iomanip>
# include <cerrno>

enum Type {
	CHAR,
	INT,
	FLOAT,
	DOUBLE,
	INVALID,
};

class ScalarConverter {
	private:
		ScalarConverter();
		ScalarConverter(const ScalarConverter& other);
		ScalarConverter& operator=(const ScalarConverter& other);
		~ScalarConverter();
	public:
		static void convert(const std::string &literal);

};

#endif