#include "Client.hpp"
#include <string>
#include <sstream>
#include <cstdlib>
#include <iostream>
#include <unistd.h>

Client::Client() : _fd(-1), _config(NULL), _bodyTooLarge(false), _pendingResponse(0) {}

Client::Client(int fd,const t_config* config) : _fd(fd), _config(config), _bodyTooLarge(false), _pendingResponse(0) {}

void Client::appendToBuffer(const char * str, ssize_t bytes)
{
    _buffer.append(str, bytes);
}

bool Client::isRequestComplete(size_t max_body_loc)
{
    size_t header_end_pos = _buffer.find("\r\n\r\n");
	if (header_end_pos == std::string::npos)
		return false;

    std::string headers = _buffer.substr(0, header_end_pos);

    for (size_t i = 0; i <headers.size(); i++)
        headers[i] = std::tolower(static_cast<unsigned char>(headers[i]));

    size_t limit;
    if (max_body_loc > 0)
        limit = max_body_loc;
    else
    {
        if (_config)
            limit = _config->max_body_size > 0 ? _config->max_body_size : 1024 * 1024;   
        else
            limit = 1024 * 1024;
    }
    size_t transcode = headers.find("transfer-encoding: chunked");
    if (transcode == std::string::npos)
    {
        if (_buffer.compare(0, 4, "POST") == 0)
        {
            size_t pos = headers.find("content-length: ");

            if (pos != std::string::npos)
            {
                size_t start = pos + 16;
                size_t end = headers.find("\r\n", start);
                size_t content_length = std::strtoul(headers.substr(start, end - start).c_str(), NULL, 10);

                if (content_length > limit)
                {
                    _bodyTooLarge = true;
                    return true;
                }

                size_t body_received = _buffer.size() - (header_end_pos + 4);
                return (body_received >= content_length);
            }
        }
        return true;
    }
    else
    {
		size_t server_limit = _config ? (_config->max_body_size > 0 ? _config->max_body_size : 1024 * 1024) : 1024 * 1024;
		size_t effective_limit = (max_body_loc > server_limit) ? max_body_loc : server_limit;
		size_t body_size = (_buffer.size() > header_end_pos + 4) ? _buffer.size() - (header_end_pos + 4) : 0;
		if (body_size > effective_limit)
		{
			_bodyTooLarge = true;
			return true;
		}
        size_t end_ch = _buffer.find("0\r\n\r\n", header_end_pos + 4);
        if (end_ch == std::string::npos)
            return false;
        return true;
    }
    return true;
}

std::string& Client::getBuffer()
{
    return _buffer;
}

void Client::clearBuffer()
{
    _buffer.clear();
}
void Client::setResponse(std::string str)
{
    _response = str;
}

std::string& Client::getResponse()
{
    return _response;
}
int Client::getFD() const
{
    return _fd;
}

const t_config* Client::getConfig()
{
    return _config;
}

bool Client::isBodyTooLarge()
{
    return _bodyTooLarge;
}

void Client::setPending(size_t add)
{
    _pendingResponse += add;
}
size_t Client::getPending()
{
    return _pendingResponse;
}