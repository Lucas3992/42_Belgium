#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter() {}

ScalarConverter::ScalarConverter(const ScalarConverter& other) {
	(void)other;
}

ScalarConverter& ScalarConverter::operator=(const ScalarConverter& other) {
	(void)other;
	return *this;
}

ScalarConverter::~ScalarConverter() {}

int isPseudoLiteral(const std::string &literal) {
	if (literal == "nan" || literal == "+inf" || literal == "-inf" || literal == "inf")
		return 1;
	else if (literal == "nanf" || literal == "+inff" || literal == "-inff"|| literal == "inff")
		return 2;
	return 0;
}

void transformPseudoLiteral(const std::string &literal) {
	std::cout << "char: impossible\n" << "int: impossible\n";
	int r = isPseudoLiteral(literal);
	if (r == 1) {
		std::cout << "float: " << literal << "f\n";
		std::cout << "double: " << literal << std::endl;
	}
	else if (r == 2) {
		std::cout << "float: " << literal << std::endl;
		std::cout << "double: " << literal.substr(0, literal.size() -1) << std::endl;
	}
}

bool isValidInt(const std::string& literal) {
	int i = 0;
	int size = literal.size();

	if (literal[i] == '+' || literal[i] == '-')
		i++;
	if (i == size)
		return false;
	while (i < size) {
		if (!std::isdigit(literal[i]))
			return false;
		i++;
	}
	if (i == size)
		return true;
	return false;
}

bool isValidDouble(const std::string& literal) {
    int i = 0;
    int size = literal.size();
    int dot = 0;
    int digits = 0;

    if (literal[i] == '+' || literal[i] == '-')
        i++;
    if (i == size)
        return false;
    while (i < size) {
        if (std::isdigit(static_cast<unsigned char>(literal[i])))
            digits++;
        else if (literal[i] == '.' && dot == 0)
            dot++;
        else
            return false;
        i++;
    }
	if (dot == 1 && digits > 0)
		return true;
    return false;
}

Type detectType(const std::string &literal) {
	int size = literal.size();

	if (size == 1 && !std::isdigit(literal[0]))
		return CHAR;
	else if (isValidInt(literal))
		return INT;
	else if (size > 1 && literal[size -1] == 'f') {
		std::string tmp = literal.substr(0, size -1);
		if (isValidDouble(tmp))
			return FLOAT;
	}
	else if (isValidDouble(literal))
		return DOUBLE;
	return INVALID;
}

static void printChar(char c, bool overflow) {
	if (overflow)
		std::cout << "char: impossible\n";
	else if (!isprint(c))
		std::cout << "char: Non displayable\n";
	else
		std::cout << "char: '" << c << "'\n";
}

static void printInt(int i, bool overflow) {
	if (overflow)
		std::cout << "int: impossible\n";
	else
		std::cout << "int: " << i << "\n";
}

static void printFloat(float f, bool overflow) {
	if (overflow)
		std::cout << "float: impossible\n";
	else
		std::cout << "float: " << std::fixed << std::setprecision(1) << f << "f\n";
}

static void printDouble(double d, bool overflow) {
	if (overflow)
		std::cout << "double: impossible\n";
	else
		std::cout << "double: " << std::fixed << std::setprecision(1) << d << "\n";
}

void ScalarConverter::convert(const std::string& literal) {
	if (isPseudoLiteral(literal)) {
		transformPseudoLiteral(literal);
		return;
	}

	Type type = detectType(literal);

	switch (type) {
		case CHAR: {
			char c = literal[0];
			printChar(c, false);
			printInt(static_cast<int>(c), false);
			printFloat(static_cast<float>(c), false);
			printDouble(static_cast<double>(c), false);
			break;
		}
		case INT: {
			long tmp = strtol(literal.c_str(), NULL, 10);
			double d = strtod(literal.c_str(), NULL);
			printChar(static_cast<char>(tmp),
				tmp < std::numeric_limits<char>::min() || tmp > std::numeric_limits<char>::max());
			printInt(static_cast<int>(tmp),
				tmp < std::numeric_limits<int>::min() || tmp > std::numeric_limits<int>::max());
			printFloat(static_cast<float>(d),
				d < -std::numeric_limits<float>::max() || d > std::numeric_limits<float>::max());
			printDouble(d, false);
			break;
		}
		case FLOAT: {
			float f = strtof(literal.c_str(), NULL);
			printChar(static_cast<char>(f),
				f < std::numeric_limits<char>::min() || f > std::numeric_limits<char>::max());
			printInt(static_cast<int>(f),
				f < std::numeric_limits<int>::min() || f > std::numeric_limits<int>::max());
			printFloat(f, false);
			printDouble(static_cast<double>(f), false);
			break;
		}
		case DOUBLE: {
			double d = strtod(literal.c_str(), NULL);
			printChar(static_cast<char>(d),
				d < std::numeric_limits<char>::min() || d > std::numeric_limits<char>::max());
			printInt(static_cast<int>(d),
				d < std::numeric_limits<int>::min() || d > std::numeric_limits<int>::max());
			printFloat(static_cast<float>(d),
				d < -std::numeric_limits<float>::max() || d > std::numeric_limits<float>::max());
			printDouble(d, false);
			break;
		}
		default:
			std::cout << "char: impossible\n";
			std::cout << "int: impossible\n";
			std::cout << "float: impossible\n";
			std::cout << "double: impossible\n";
	}
}