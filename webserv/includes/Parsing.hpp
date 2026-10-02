#ifndef PARSING_HPP
# define PARSING_HPP

# include "Config.hpp"
# include <fstream>
# include <iostream>
# include <cstdlib>

class Parser {
	private:
		std::vector<t_config>	_config;
		t_config				_cTmp;
		t_location				_lTmp;
		unsigned int			_depth;
		std::string				_currentLine;
		size_t					_i;
	public:
		Parser(){}
		~Parser(){}

		void		skipSpace();
		std::string	readToken();
		void		expectSemicolon();
		void		expectServer();
		void		expectObracket();
		void		handlePath();
		void		checkHostFormat(std::string host);
		bool		checkSlash(std::string& s);
		void		handleComs();
		void		checkConfigFile(std::string argv);

		void		checkListen(t_config& c);
		void		checkRoot(t_config& c);
		void		checkBodySize(t_config& c);
		void		checkServerName(t_config& c);
		void		checkIndex(t_config& c);
		void		checkErrorPage(t_config& c);
		void		checkDupPaths(std::vector<t_location>& v);
		void		checkPath(t_location& l);
		void		checkMethods(t_location& l);

		void		checkServInfo(t_config& c);
		void		checkLocInfo(t_location& l);

		void		validate();
		void		ultimateParsing(std::string argv);
		void		parseLocation();

		void		detectServerDirective(std::string token);
		void		detectLocationDirective(std::string token);

		void		parseListen();
		void		parseStringValue(std::string& dest);
		void		parseErrorPage();
		void		parseMaxBodySize();
		void		parseLocationMaxBodySize();

		void		parseMethods();
		void		parseAutoindex();

		std::vector<t_config>&	getConfig() {return _config;}

		class ParserException : public std::exception {
			private:
				std::string _msg;
			public:
				ParserException(std::string msg) : _msg("Error in config file: " + msg) {}
				virtual const char* what() const throw() {return _msg.c_str();}
				~ParserException() throw() {}
		};
};

std::ostream& operator<<(std::ostream& os, Parser& p);

#endif