#include "BitcoinExchange.hpp"

btc::btc() {}
btc::btc(const btc& o) : _map(o._map) {}
btc& btc::operator=(const btc& o) {
	if (this != &o) {
		_map = o._map;
	}
	return *this;
}
btc::~btc() {}
btc::btcException::btcException(const std::string& msg) : _msg("Error: " + msg) {}
btc::btcException::~btcException() throw() {}
const char* btc::btcException::what() const throw() {return _msg.c_str();}

void btc::checkDate(const std::string& year, const std::string& month, const std::string& day) const {
	int y = atoi(year.c_str());
	int m = atoi(month.c_str());
	int d = atoi(day.c_str());
	if (y < 0 || y > 2100)
		throw btcException("wrong year");
	if (m < 1 || m > 12)
		throw btcException("wrong month");
	int array[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0)
		array[1] = 29;
	if (d < 1 || d > array[m -1])
		throw btcException("wrong day");
}

bool btc::isValidDate(const std::string &date) const {
	if (date.size() != 10 || date[4] != '-' || date[7] != '-' || !isdigit(date[0]) || !isdigit(date[1]) || !isdigit(date[2]) || !isdigit(date[3]) || !isdigit(date[5]) || !isdigit(date[6]) || !isdigit(date[8]) || !isdigit(date[9]))
		return false;
	std::string year = date.substr(0, 4);
	std::string month = date.substr(5, 2);
	std::string day = date.substr(8, 2);
	checkDate(year, month, day);
	return true;
}

bool btc::isValidValue(const std::string &valueSTR, double& value) const {
	char* end;
	value = strtod(valueSTR.c_str(), &end);
	while (*end != '\0' && isspace(*end))
		end++;
	if (valueSTR.empty() || *end != '\0')
		return false;
	if (value < 0)
		throw btcException("not a positive number");
	if (value > 1000)
		throw btcException("too large a number");
	return true;
}

bool btc::isValidRate(const std::string& rateSTR, double& rate) const {
    char* end;
    rate = strtod(rateSTR.c_str(), &end);
    while (*end != '\0' && isspace(*end))
        end++;
    if (rateSTR.empty() || *end != '\0' || rate < 0)
        return false;
    return true;
}

float btc::getRateForDate(const std::string &date) const {
	std::map<std::string, float>::const_iterator it = _map.lower_bound(date);
	if (it != _map.end() && it->first == date)
		return it->second;
	if (it == _map.begin())
		throw btcException("no rate for this date");
	--it;
	return it->second;
}

void btc::expectPipe(std::string& line, size_t& pipePos) {
	pipePos = line.find(" | ");
	if (pipePos == std::string::npos)
		throw btcException("bad input => " + line);
}

void btc::loadDatabase(const std::string &file) {
	std::ifstream f(file.c_str());
	if (!f.is_open())
		throw btcException("could not open database");
	std::string line;
	std::getline(f, line);
	while (std::getline(f, line)) {
		size_t commaPos = line.find(',');
		if (commaPos == std::string::npos)
			throw btcException("bad input => " + line);
		std::string date = line.substr(0, commaPos);
		std::string rateSTR = line.substr(commaPos +1);
		double rate;
		if (!isValidDate(date) || !isValidRate(rateSTR, rate))
				continue;
		_map[date] = static_cast<float>(rate);
	}
	f.close();
}

void btc::processInput(const std::string &file) {
	std::ifstream f(file.c_str());
	if (!f.is_open())
		throw btcException("couldn't open file");
	std::string line;
	std::getline(f, line);
	while (std::getline(f, line)) {
		try {
			size_t pipePos;
			expectPipe(line, pipePos);
			std::string date = line.substr(0, pipePos);
			std::string valueSTR = line.substr(pipePos + 3);
			double value;
			if (!isValidDate(date) || !isValidValue(valueSTR, value))
				throw btcException("bad input => " + line);
			float rate = getRateForDate(date);
			std::cout << date << " => " << value << " = " << value * rate << std::endl;
		} catch (std::exception& e) {std::cerr << e.what() << std::endl;}
	}
	f.close();
}
