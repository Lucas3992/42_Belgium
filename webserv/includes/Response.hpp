#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include <string>
#include <map>
#include <iostream>
#include <sstream>
#include "Config.hpp"

class Response {
    private:
        std::string _full_response;
        std::string _body;
        int         _status_code;
        std::string _content_type;

		std::map<std::string, std::string> _custom_headers;
        void        buildResponse();

    public:
        Response();
        ~Response();

        void        prepareResponse(int code, std::string contentType, std::string body);
        std::string getFullResponse() const;
		void		setContent_type(std::string newCT);
		void		setBody(std::string newBody);
		std::string	getContent_type() const;
		std::string	getBody() const;
		void addHeader(const std::string& key, const std::string& value);
		void prepareErrorResponse(int code, const t_config& config);
        std::string getStatusMessage(int code);
        std::string buildErrorPage(int code);
};

#endif