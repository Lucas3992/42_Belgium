#include "Request.hpp"
#include <sstream>
#include <algorithm>

Request::Request()  {}
Request::~Request() {}

void Request::parse(std::string buffer)
{
    size_t header_end = buffer.find("\r\n\r\n");
	if (header_end == std::string::npos)
		return;

    std::string header_part = buffer.substr(0, header_end);
    std::stringstream ss(header_part);
    std::string line;

    if(std::getline (ss, line)){
		if (!line.empty() && line[line.size() -1] == '\r')
			line.erase(line.size() -1);

        std::stringstream firstline(line);
        firstline >> _method >> _path >> _version;
		_rawPath = _path;
    }

    while(std::getline(ss, line)){
		if (line == "\r" || line.empty())
			break;
		if (line[line.size() -1] == '\r')
			line.erase(line.size() -1);
        size_t colon = line.find(':');
        if (colon != std::string::npos){
            std::string key = line.substr(0, colon);
			for (size_t i = 0; i < key.length(); i++)
				key[i] = std::tolower(static_cast<unsigned char>(key[i]));
            std::string value = line.substr(colon+2);
            _headers[key] = value;
        }
    }
	_body = buffer.substr(header_end + 4);
    if (getHeader("transfer-encoding") == "chunked")
        _body = decodeChunk(_body);
}

std::string& Request::getPath()
{
    return _path;
}
Method Request::getMethodEnum() const
{
    if (_method == "GET")
        return GET;
    if (_method == "POST")
        return POST;
    if (_method == "DELETE")
        return DELETE;
    return UNKNOWN;
}

std::string& Request::getBody()
{
    return _body;
}

const std::string& Request::getMethod() const
{
	return _method;
}

std::string& Request::getRawPath()
{
    return _rawPath;
}

const std::string& Request::getHeader(std::string const &key) const
{
	static std::string empty = "";
	std::map<std::string, std::string>::const_iterator it = _headers.find(key);

	if (it != _headers.end())
			return it->second;
	return empty;
}

std::string Request::decodeChunk(const std::string& body)
{
    std::string result;
    size_t pos = 0;

    while (pos < body.size())
    {
        size_t lineStart = pos;
        size_t lineEnd = body.find("\r\n", pos);
        std::string size = body.substr(lineStart, lineEnd - lineStart);
        size_t toExtract = std::strtol(size.c_str(), NULL, 16);
        if (toExtract == 0)
            break;
        pos = lineEnd + 2;
        result += body.substr(pos, toExtract);
        pos += toExtract + 2;
    }
    return result;
}

std::string& Request::getVersion()
{
	return _version;
}
const std::map<std::string, std::string>& Request::getHeaders() const
{
    return _headers;
}