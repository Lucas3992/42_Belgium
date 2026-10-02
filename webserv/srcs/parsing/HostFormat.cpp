# include "Parsing.hpp"

static bool hasThreeDots(std::string host) {
	int dotCount = 0;
	for (int i = 0; host[i]; i++) {
		if (host[i] == '.')
			dotCount++;
	}
	if (dotCount == 3)
		return true;
	return false;
}

static void splitInFour(std::string host, std::string numbers[4]) {
	size_t pos;
	int i = 0;
	while (i < 3) {
		pos = host.find('.');
		numbers[i] = host.substr(0, pos);
		host = host.erase(0, pos +1);
		i++;
	}
	numbers[i] = host;
}

static bool isOneEmpty(std::string numbers[4]) {
	for (int i = 0; i < 4; i++) {
		if (numbers[i].empty())
			return true;
	}
	return false;
}

static bool areAllDigits(std::string numbers[4]) {
	for (int i = 0; i < 4; i++) {
		int j = 0;
		while (numbers[i][j]) {
			if (!isdigit(numbers[i][j]))
				return false;
			j++;
		}
	}
	return true;
}

static bool isInRange(std::string numbers[4]) {
	long n[4];
	for (int i = 0; i < 4; i++) {
        if (numbers[i].size() > 3)
            return false;
			char* end;
		n[i] = strtol(numbers[i].c_str(), &end, 10);
		if (*end != '\0')
            return false;
        if (n[i] < 0 || n[i] > 255)
            return false;
	}
    return true;
}

void Parser::checkHostFormat(std::string host) {
	if (host == "localhost")
		return;
	std::string numbers[4];
	if (!hasThreeDots(host))
		throw ParserException("host format: number.number.number.number");
	splitInFour(host, numbers);
	if (isOneEmpty(numbers) || !areAllDigits(numbers))
		throw ParserException("host format: number.number.number.number");
    if (!isInRange(numbers))
        throw ParserException("invalid host: numbers must be between 0 and 255");
}
