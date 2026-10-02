#include "Parsing.hpp"

void Parser::parseListen() {
	t_listen tmp;
	std::string listen = readToken();
	unsigned int dd = (unsigned int)listen.find(":");
	char* end;
	if (dd == (unsigned int)std::string::npos) {//pas trouve
		tmp.host = "0.0.0.0";
		tmp.port = strtol(listen.c_str(), &end, 10);
	} else {
		std::string host = listen.substr(0, dd);
		std::string port = listen.substr(dd +1);
		tmp.host = host;
		tmp.port = strtol(port.c_str(), &end, 10);
	}
	if (*end != '\0')
		throw ParserException("invalid port");
	expectSemicolon();
	_cTmp.listens.push_back(tmp);
}

void Parser::parseStringValue(std::string& dest) {
	dest = readToken();
	expectSemicolon();
}

void Parser::parseMaxBodySize() {
	std::string token = readToken();
	char* end;
	errno = 0;
	_cTmp.max_body_size = strtol(token.c_str(), &end, 10);
	if (*end != '\0' || errno == ERANGE)
		throw ParserException("invalid max_body_size");
	expectSemicolon();
}

void Parser::checkBodySize(t_config& c) {
	if (c.max_body_size < 0)
		throw ParserException("max_body_size must be positive");
	if (c.max_body_size > 1073741824) // 1GB max
        throw ParserException("max_body_size too large");
	if (c.max_body_size == 0)
		c.max_body_size = 1024 * 1024;//si vide assigne 1MB comme nginx
}

void Parser::parseErrorPage() {
	char* end;
	int code = strtol(readToken().c_str(), &end, 10);
	if (*end != '\0')
		throw ParserException("invalid error code");
	std::string path = readToken();
	_cTmp.error_pages[code] = path;
	expectSemicolon();
}

void Parser::detectServerDirective(std::string token) {
	if (token == "listen")
		parseListen();
	else if (token == "root")
		parseStringValue(_cTmp.root);
	else if (token == "server_name")
		parseStringValue(_cTmp.server_name);
	else if (token == "index")
		parseStringValue(_cTmp.index);
	else if (token == "max_body_size")
		parseMaxBodySize();
	else if (token == "error_page")
		parseErrorPage();
	else if (token == "location")
		parseLocation();
	else if (token == "}") {
		_depth--;
		_config.push_back(_cTmp);
		_cTmp = t_config();//remettre ctmp a zero
	}
	else
		throw ParserException("unknown token");
}

void Parser::checkListen(t_config& c) {
	if (c.listens.empty())
		throw ParserException("server has no listen directive");
	for (std::vector<t_listen>::iterator it = c.listens.begin(); it != c.listens.end(); it++) {
		if (it->port < 1 || it->port > 65535)//port 0 valide mais ca choisit un port dispo random
			throw ParserException("port must be between 1 and 65535");
		checkHostFormat(it->host);
	}
}

void Parser::checkRoot(t_config& c) {
	if (c.root.empty())
		c.root = "./www";
	if (!checkSlash(c.root))
		throw ParserException("root format: '/...' or './...'");
}

void Parser::checkServerName(t_config& c) {
//peut etre vide et devient "catch-all": repond a toutes les requetes qui 
//correspondent a aucun autre server
	for (int i = 0; c.server_name[i]; i++) {
		if (!(isalnum(c.server_name[i])) && c.server_name[i] != '-' && c.server_name[i] != '.')
			throw ParserException("invalid server_name");
	}
}

void Parser::checkIndex(t_config& c) {
	if (c.index.empty())
		c.index = "index.html";
	for (int i = 0; c.index[i]; i++) {
		if (!(isalnum(c.index[i])) && c.index[i] != '-' && c.index[i] != '_' && c.index[i] != '.')
			throw ParserException("invalid index");
	}
}

void Parser::checkErrorPage(t_config& c) {
	std::map<int, std::string>::iterator it;
	for (it = c.error_pages.begin(); it != c.error_pages.end(); it++) {
		if (it->first < 400 || it->first > 599)
			throw ParserException("error page code must be between 400 and 599");
		if (it->second[0] != '/')
			throw ParserException("error page path format: /...");
	}
}

void Parser::checkServInfo(t_config& c) {
	checkListen(c);
	checkRoot(c);
	checkDupPaths(c.locations);
	checkServerName(c);
	checkBodySize(c);
	checkIndex(c);
	checkErrorPage(c);
}
