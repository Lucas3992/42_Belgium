#include "Parsing.hpp"

void Parser::skipSpace() {
while (_i < _currentLine.size() && isspace(_currentLine[_i]))
		_i++;
}

static bool isSemiColon(char c) {
	return (c == ';');
}

static bool isObracket(char c) {
	return (c == '{');
}

static bool isCbracket(char c) {
	return (c == '}');
}

static bool isValidChar(char c) {
	if (isspace(c) || isSemiColon(c) || isObracket(c) || isCbracket(c))
		return false;
	return true;
}

std::string Parser::readToken() {
    skipSpace();
    std::string ret = "";
    if (_i < _currentLine.size() && 
        (isObracket(_currentLine[_i]) || isCbracket(_currentLine[_i]))) {
        ret += _currentLine[_i];
        _i++;
        return ret;
    }
    while (_i < _currentLine.size() && isValidChar(_currentLine[_i])) {
        ret += _currentLine[_i];
        _i++;
    }
    return ret;
}

void Parser::expectSemicolon() {
	skipSpace();
	if (isSemiColon(_currentLine[_i]))
		_i++;
	else
		throw ParserException("expected ;");
}

void Parser::expectServer() {
	std::string token = readToken();
	if (token != "server")
		throw ParserException("format: server {...}");
	expectObracket();
}

void Parser::expectObracket() {
	skipSpace();
	if (_i >= _currentLine.size() || _currentLine[_i] != '{')
		throw ParserException("{ expected");
	_depth++;
	_i++;
}

void Parser::handlePath() {
    std::string token = readToken();
    if (token.empty())
        throw ParserException("/ expected");
    if (token[0] != '/' && token[0] != '*')
        throw ParserException("/ expected");
    _lTmp.path = token;
}

bool Parser::checkSlash(std::string& s) {
	if (s.empty())
		return true;
	if (s[0] != '/' && (!(s[0] == '.' && s.size() > 1 && s[1] == '/')))
		return false;
	return true;
}

void Parser::handleComs() {
	size_t com = _currentLine.find('#');
	if (com == std::string::npos)
		return;
	_currentLine = _currentLine.substr(0, com);
}

void Parser::checkConfigFile(std::string argv) {
	for (int i = 0; argv[i]; i++) {
		if (!isprint(argv[i]))
			throw ParserException("format config file: printablechar.conf");
	}
	if (argv.size() < 5)
		throw ParserException("format config file: printablechar.conf");
	size_t found = argv.rfind(".conf");
	if ((found == std::string::npos) || (found != argv.size() -5))
		throw ParserException("format config file: printablechar.conf");
}