#ifndef CLIENT_HPP
# define CLIENT_HPP
# include <string>
# include "Config.hpp"
# include "unistd.h"

class Client
{
    private:
        std::string _buffer;
        std::string _response;
        int _fd;
		const t_config* _config;
        bool _bodyTooLarge;
        size_t _pendingResponse;
    public:
        Client();
        Client(int fd, const t_config* config);
        void appendToBuffer(const char* str, ssize_t bytes);
        bool isRequestComplete(size_t max_body);
        std::string& getBuffer();
        void setResponse(std::string str);
        std::string& getResponse();
        void clearBuffer();
        int getFD() const;
		const t_config* getConfig();
        bool isBodyTooLarge();
        size_t getPending();
        void setPending(size_t add);
};

#endif
