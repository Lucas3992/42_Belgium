#ifndef REQUEST_HPP
# define REQUEST_HPP
# include <string>
# include <map>
# include <vector>

enum Method {
    GET,
    POST,
    DELETE,
    UNKNOWN
};

class Request
{
    private:
       std::string _method;
       std::string _path;
       std::string _version;
       std::string _body;
	   std::string _rawPath;
       std::map<std::string, std::string> _headers;
    public:
        Request();
        ~Request();
        void parse(std::string buffer);

        Method getMethodEnum() const;
		const std::string& getMethod() const;
		std::string& getPath();
        std::string& getBody();
        std::string& getVersion();
		const std::string& getHeader(std::string const &key) const;
        std::string& getRawPath();
        std::string decodeChunk(const std::string& body);
		std::string getQuery_String();
		std::string getContent_Length();
		const std::map<std::string, std::string>& getHeaders() const;
};

#endif