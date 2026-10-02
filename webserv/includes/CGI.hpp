#ifndef CGI_HPP
# define CGI_HPP

# include <iostream>
# include "Request.hpp"
# include "Response.hpp"
# include "Server.hpp"
# include <unistd.h>
# include <sys/wait.h>
# include <cstring>
# include <sys/stat.h>
# include <cerrno>
# include <fcntl.h>

class CGI {
	public: 
		CGI() {}
		~CGI() {}

		std::vector<std::string>	buildEnv(Request& req, RouteContext& ctx);
		std::vector<std::string> 	buildArgv(RouteContext& ctx);
		CGIProcess 					execute(Request& req, std::vector<std::string>& env, std::vector<std::string>& argv);
		void						parseOutput(std::string& output, Response& rep);
		int 						readFromOutput(int out, std::string& output);

		class CGIException : public std::exception {
			private:
				std::string _msg;
			public:
				CGIException(std::string msg) : _msg(msg) {}
				virtual const char* what() const throw() {return _msg.c_str();}
				~CGIException() throw() {}
		};
};

#endif