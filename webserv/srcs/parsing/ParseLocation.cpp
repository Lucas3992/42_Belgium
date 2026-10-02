#include "Parsing.hpp"

void Parser::parseMethods() {
    size_t before = _lTmp.methods.size();
    while (_i < _currentLine.size() && _currentLine[_i] != ';') {
        std::string token = readToken();
        if (!token.empty())
            _lTmp.methods.push_back(token);
    }
    expectSemicolon();
    if (_lTmp.methods.size() == before)
        throw ParserException("methods are only GET, POST or DELETE");
}

void Parser::parseAutoindex() {
	std::string state = readToken();
	if (state == "on")
		_lTmp.autoindex = true;
	else if (state == "off")
		_lTmp.autoindex = false;
	else
		throw ParserException("autoindex must be on or off");
	expectSemicolon();
}

void Parser::parseLocationMaxBodySize() {
    std::string token = readToken();
    char* end;
    errno = 0;
    long val = strtol(token.c_str(), &end, 10);
    if (*end != '\0' || errno == ERANGE || val < 0)
        throw ParserException("invalid max_body_size");
    _lTmp.max_body_size = static_cast<size_t>(val);
    expectSemicolon();
}

void Parser::detectLocationDirective(std::string token) {
	if (token == "methods")
		parseMethods();
	else if (token == "autoindex")
		parseAutoindex();
	else if (token == "upload_dir")
		parseStringValue(_lTmp.upload_dir);
	else if (token == "cgi_path")
		parseStringValue(_lTmp.cgi_path);
	else if (token == "redirect")
		parseStringValue(_lTmp.redirect);
	else if (token == "root")
		parseStringValue(_lTmp.root);
	else if (token == "index")
		parseStringValue(_lTmp.index);
	else if (token == "client_max_body_size")
		parseLocationMaxBodySize();
	else if (token == "}") {
		_depth--;
		_cTmp.locations.push_back(_lTmp);
		_lTmp = t_location();
	}
	else
    	throw ParserException("unknown token");
}

void Parser::parseLocation() {
	handlePath();
	expectObracket();
}

void Parser::checkPath(t_location& l) {
	if (l.path.empty())
		throw ParserException("location is empty");
}

void Parser::checkDupPaths(std::vector<t_location>& v) {
	std::vector<t_location>::iterator it;
	std::vector<t_location>::iterator it2;
	for (it = v.begin(); it != v.end(); it++) {
		for (it2 = it + 1; it2 != v.end(); it2++) {
			if (it->path == it2->path)
				throw ParserException("path duplicate detected");
		}
	}
}

void Parser::checkMethods(t_location& l) {
	if (l.methods.empty())//si aucune methode precisee, GET par defaut
		l.methods.push_back("GET");
	std::vector<std::string>::iterator it;
	for (it = l.methods.begin(); it != l.methods.end(); it++) {
		if (*it != "GET" && *it != "POST" && *it != "DELETE")
			throw ParserException("methods are only GET, POST or DELETE");
	}
}

void Parser::checkLocInfo(t_location& l) {
	checkPath(l);
	checkMethods(l);
	if (!checkSlash(l.upload_dir))
		throw ParserException("upload_dir format: '/...' or './...'");
	if (!checkSlash(l.redirect))
		throw ParserException("redirect format: '/...' or './...'");
	if (!checkSlash(l.cgi_path))
		throw ParserException("cgi_path format: '/...' or './...'");
}
