#ifndef SERVER_HPP
# define SERVER_HPP
# include <poll.h>
# include <vector>
# include <Client.hpp>
# include <map>
# include "Request.hpp"
# include "Response.hpp"
# include "Config.hpp"

struct RouteContext {
    const t_config* config;
    t_location*     loc;
    std::string     root;
    std::string     fullPath;
    bool            needsSlashRedirect;

    RouteContext() : config(NULL), loc(NULL) {}
};

struct CGIProcess {
    int         pipe_out;
    int         pipe_in;
    int         client_fd;
    pid_t       pid;
    time_t      start;
    bool        alive;
    std::string body;
    size_t      body_offset;
    std::string output;
    const t_config* config;
};

class Server
{
    private:
        std::vector<struct pollfd> _fds;
        std::map<int, Client> _clients;
		std::vector<t_config> _configs;
		std::map<int, const t_config*> _listen_fds_to_config;
		std::vector<CGIProcess> _cgiprocesses;
		std::map<int, pid_t> _pipe_to_cgi;
        RouteContext buildRouteContext(Request &req, const t_config* config);

    public:
        static bool g_keep_running;
        Server(std::vector<t_config> const &configs);
        ~Server();
		void setupServerSocket(t_listen const &listen_info, t_config const &config);
        void run();
		void acceptNewClient(int listen_fd);
		void removeClient(int fd);
        int handleClientRequest(int index);
        void handleGet(Request &req, Response &res, RouteContext &ctx);
        void handlePost(Request &req, Response &res, RouteContext &ctx);
        void handleDelete(Response &res, RouteContext &ctx);
		int handleCGI(Request &req, Response &res, RouteContext &ctx, int fd);
		int sendResponse(size_t index);
        bool getFileContent(std::string path, std::string& content);
        std::string getMimeType(std::string path);
		void generateAutoIndex(std::string path, std::string urlPath, Response &res, const t_config& config);
		t_location* findLocation(std::string const &path, const t_config* config);
        bool isMethodAllowed(t_location* loc, const std::string& method);
		bool isCGI(RouteContext &ctx);
        bool handleRedirection(Response& res, RouteContext &ctx);
        bool isSafePath(const std::string fullPath, const std::string &allowedDir);
        std::string extractUploadDir(RouteContext& ctx);
        std::string extractFilename(Request& req, RouteContext& ctx, const std::string& body, const std::string& boundary);
        std::string extractMultipartBody(const std::string& body, const std::string& boundary);
        void saveFile(const std::string& path, const std::string& content, Response& res, const t_config& config);
        void finalizeResponse(int fd, Response &res);
        void processRequest(int fd);
		void checkCGIProcesses(std::vector<CGIProcess>& processes);
        void prepAndFinal(std::vector<CGIProcess>::iterator it, Response &res);
        void serveFile(const std::string& path, Response& res, RouteContext& ctx);
		void registerCGIPipes(CGIProcess& process);
		void handleCGIPipeWrite(size_t& i, CGIProcess& proc);
		void handleCGIPipeRead(CGIProcess &proc);
		void removePipeFromFds(int fd);
};
#endif
