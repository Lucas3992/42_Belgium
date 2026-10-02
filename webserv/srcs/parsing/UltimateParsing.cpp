#include "Parsing.hpp"

void Parser::ultimateParsing(std::string argv) {
	_depth = 0;
	checkConfigFile(argv);
	std::ifstream file(argv.c_str());
	if (!file.is_open())
		throw ParserException("can't open config file");
	while (std::getline(file, _currentLine)) {
		_i = 0;
		handleComs();
		skipSpace();
		if (_i >= _currentLine.size())
			continue;
		switch (_depth) {
		case 0:
			expectServer();
			break;
		case 1:
			detectServerDirective(readToken());
			break;
		default:
			detectLocationDirective(readToken());
			break;
		}
	}
	if (_depth != 0)
		throw ParserException("missing }");
	validate();
}

void Parser::validate() {
	if (_config.empty())
		throw ParserException("empty config file");
	for (std::vector<t_config>::iterator it = _config.begin(); it != _config.end(); it++) {
		checkServInfo(*it);
		for (std::vector<t_location>::iterator lit = it->locations.begin(); lit != it->locations.end(); lit++)
			checkLocInfo(*lit);
	}
}