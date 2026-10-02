#include "Response.hpp"
#include <fstream>

Response::Response() : _status_code(200), _content_type("text/html") {}

Response::~Response() {}

void Response::setBody(std::string newBody) {
	_body = newBody;
}

void Response::setContent_type(std::string newCT) {
	_content_type = newCT;
}

std::string Response::getBody() const {
	return _body;
}

std::string Response::getContent_type() const {
	return _content_type;
}

void Response::prepareResponse(int code, std::string contentType, std::string body) {
    _status_code = code;
    _content_type = contentType;
    _body = body;
    buildResponse();
}

void Response::buildResponse() {
	std::stringstream ss;
    ss << "HTTP/1.1 " << _status_code << " " << getStatusMessage(_status_code) << "\r\n";
    ss << "Content-Type: " << _content_type << "\r\n";
    ss << "Content-Length: " << _body.length() << "\r\n";
    
    std::map<std::string, std::string>::iterator it;
    for (it = _custom_headers.begin(); it != _custom_headers.end(); ++it) {
        ss << it->first << ": " << it->second << "\r\n";
    }

    ss << "Connection: close\r\n\r\n";
    ss << _body;
    _full_response = ss.str();
}

std::string Response::getStatusMessage(int code) {
    static std::map<int, std::string> m;
	if (m.empty()){
		m[200] = "OK";
		m[201] = "Created";
		m[204] = "No Content";
        m[301] = "Moved Permanently";
        m[400] = "Bad Request";
		m[403] = "Forbidden";
		m[404] = "Not Found";
        m[405] = "Method Not Allowed";
		m[413] = "Payload Too Large";
        m[500] = "Internal Server Error";
    }
    if (m.count(code))
        return m[code];
    return "Unknown Error";
}

std::string Response::getFullResponse() const {
    return _full_response;
}

void Response::addHeader(const std::string& key, const std::string& value) {
    _custom_headers[key] = value;
}

std::string Response::buildErrorPage(int code) {
    std::stringstream ss;
    ss << "<html><head><title>Error " << code << "</title></head>";
    ss << "<body style='font-family: sans-serif; background: #222; color: #fa0;'>";
    ss << "<h1>FICSIT - Error " << code << "</h1>";
    ss << "<p>" << getStatusMessage(code) << "</p>";
    ss << "<hr><p>Webserv/1.0 (Pionnier Edition)</p>";
    ss << "</body></html>";
    return ss.str();
}

void Response::prepareErrorResponse(int code, const t_config& config) {
    _status_code = code;
    _content_type = "text/html";
    _body = "";

    std::map<int, std::string>::const_iterator it = config.error_pages.find(code);
    
    if (it != config.error_pages.end()) {
        //construit le chemin vers le fichier d'erreur
        std::string errorPath = config.root + "/" + it->second;
        //essaie de lire le contenu du fichier
        std::ifstream file(errorPath.c_str());
        if (file.is_open()) {
            std::stringstream buffer;
            buffer << file.rdbuf();
            _body = buffer.str();
            file.close();
        }
    }
    if (_body.empty())
        _body = buildErrorPage(code);
    buildResponse();
}