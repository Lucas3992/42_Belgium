#include "Server.hpp"
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdexcept>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Request.hpp"
#include "Response.hpp"
#include "Client.hpp"
#include <dirent.h>
#include <cstring>
#include <stdlib.h>
#include <sys/wait.h>
#include "CGI.hpp"

bool Server::g_keep_running = true;

Server::Server(std::vector<t_config> const &configs) : _configs(configs)
{
	for (size_t i = 0; i < _configs.size(); ++i) {
		for (size_t j = 0; j < _configs[i].listens.size(); ++j) {
			setupServerSocket(_configs[i].listens[j], _configs[i]);
		}
	}
}

Server::~Server()
{
    for (size_t i = 0; i < _fds.size(); i++)
    {
        if (_fds[i].fd > 2)
            close(_fds[i].fd);
    }
}

void Server::setupServerSocket(t_listen const &listen_info, t_config const &config)
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd < 0)
		throw std::runtime_error("Error: socket creation failed.");

    int opt = 1;
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
    {
        close(fd);
        throw std::runtime_error("Error at setsockopt.");
    }

    struct sockaddr_in addr;
	std::memset(&addr, 0, sizeof(addr));

    addr.sin_family = AF_INET;
    addr.sin_port = htons(listen_info.port);

	if (listen_info.host == "0.0.0.0" || listen_info.host == "")
		addr.sin_addr.s_addr = INADDR_ANY;
	else
		addr.sin_addr.s_addr = inet_addr(listen_info.host.c_str());

    if (bind(fd, (struct sockaddr *)&addr, sizeof(addr)) < 0){
        close(fd);
        throw std::runtime_error("Port already used.(Error on bind).");
    }

    if (listen(fd, 1024) < 0)
    {
        close(fd);
        throw std::runtime_error("Error on listen.");
    }

    struct pollfd pfd;

    pfd.fd = fd;
    pfd.events = POLLIN;
    pfd.revents = 0;
    _fds.push_back(pfd);

	_listen_fds_to_config[fd] = &config;

	std::cout << "Server [" << config.server_name << "] listening on " 
              << listen_info.host << ":" << listen_info.port << std::endl;
}

void Server::prepAndFinal(std::vector<CGIProcess>::iterator it, Response &res)
{
    close(it->pipe_out);
    res.prepareErrorResponse(500, *it->config);
    finalizeResponse(it->client_fd, res);
}

void Server::removePipeFromFds(int fd)
{
    for (std::vector<struct pollfd>::iterator it = _fds.begin(); it != _fds.end(); ++it) {
        if (it->fd == fd) {
            _fds.erase(it);
            return;
        }
    }
}

void Server::checkCGIProcesses(std::vector<CGIProcess> &processes)
{
    for (std::vector<CGIProcess>::iterator it = processes.begin(); it != processes.end(); )
    {
        Response res;
        int status;
        CGI cgi;

        if (time(NULL) - it->start > 15 || !it->alive)
        {
            kill(it->pid, SIGKILL);
            waitpid(it->pid, &status, 0);
            if (it->pipe_in != -1) {
                _pipe_to_cgi.erase(it->pipe_in);
                removePipeFromFds(it->pipe_in);
                close(it->pipe_in);
            }
            _pipe_to_cgi.erase(it->pipe_out);
            removePipeFromFds(it->pipe_out);
            if (it->alive)
                prepAndFinal(it, res);
            else
                close(it->pipe_out);
            it = processes.erase(it);
            std::cout << "Timed out, closing connection..." << std::endl;
            continue;
        }

        int ret = waitpid(it->pid, &status, WNOHANG);
        if (ret > 0)
        {
            char buf[4096];
            ssize_t b;
            while ((b = read(it->pipe_out, buf, sizeof(buf))) > 0)
                it->output.append(buf, b);

            _pipe_to_cgi.erase(it->pipe_out);
            removePipeFromFds(it->pipe_out);

            if (it->pipe_in != -1) {
                _pipe_to_cgi.erase(it->pipe_in);
                removePipeFromFds(it->pipe_in);
                close(it->pipe_in);
            }
            try {
                cgi.parseOutput(it->output, res);
            } catch (const std::exception& e) {
                prepAndFinal(it, res);
                it = processes.erase(it);
                continue;
            }
            close(it->pipe_out);
            finalizeResponse(it->client_fd, res);
            it = processes.erase(it);
        }
        else
            it++;
    }
}

void Server::run()
{
    while(g_keep_running)
    {
        int response = poll(&_fds[0], _fds.size(), 10);
        if (response < 0)
            break;

        checkCGIProcesses(_cgiprocesses);

        for (size_t i = 0; i < _fds.size(); i++)
        {
            if (_pipe_to_cgi.count(_fds[i].fd))
            {
                CGIProcess* proc = NULL;
                for (size_t j = 0; j < _cgiprocesses.size(); j++) {
                    if (_cgiprocesses[j].pid == _pipe_to_cgi[_fds[i].fd]) {
                        proc = &_cgiprocesses[j];
                        break;
                    }
                }
                if (!proc)
                    continue;

                if (_fds[i].revents & POLLOUT && proc->pipe_in != -1)
                    handleCGIPipeWrite(i, *proc);
                else if (_fds[i].revents & POLLIN)
                    handleCGIPipeRead(*proc);
                continue;
            }

            if (_fds[i].revents & POLLIN)
            {
                if (_listen_fds_to_config.count(_fds[i].fd))
                {
                    acceptNewClient(_fds[i].fd);
                    continue;
                }
                else if (handleClientRequest(i) == -1)
                {
                    i--;
                    continue;
                }
            }
            if (_fds[i].revents & POLLOUT)
            {
                if (sendResponse(i) == -1)
                    i--;
            }
        }
    }
}

void Server::handleCGIPipeWrite(size_t& i, CGIProcess& proc)
{
    const size_t CHUNK = 512 * 1024;
    size_t remaining = proc.body.size() - proc.body_offset;
    size_t toWrite = remaining < CHUNK ? remaining : CHUNK;
    ssize_t n = write(proc.pipe_in, proc.body.c_str() + proc.body_offset, toWrite);
    if (n > 0) {
        proc.body_offset += n;
        if (proc.body_offset >= proc.body.size()) {
            _pipe_to_cgi.erase(_fds[i].fd);
            _fds.erase(_fds.begin() + i);
            close(proc.pipe_in);
            proc.pipe_in = -1;
            proc.start = time(NULL);
            i--;
        }
    } else if (n < 0 && errno != EAGAIN) {
        _pipe_to_cgi.erase(_fds[i].fd);
        _fds.erase(_fds.begin() + i);
        close(proc.pipe_in);
        proc.pipe_in = -1;
        i--;
    }
}

void Server::handleCGIPipeRead(CGIProcess& proc)
{
    char buf[4096];
    ssize_t b = read(proc.pipe_out, buf, sizeof(buf));
    if (b > 0)
        proc.output.append(buf, b);
}

void Server::acceptNewClient(int listen_fd)
{
	struct sockaddr_in client_addr;
	socklen_t addr_len = sizeof(client_addr);
	int new_client = accept(listen_fd, (struct sockaddr *)&client_addr, &addr_len);
	if (new_client != -1)
	{
		struct pollfd pfd;
		pfd.fd = new_client;
		pfd.events = POLLIN;
		pfd.revents = 0;

		_fds.push_back(pfd);
		_clients[new_client] = Client(new_client, _listen_fds_to_config[listen_fd]);
	}
		
}

void Server::removeClient(int fd)
{

    for (std::vector<CGIProcess>::iterator it = _cgiprocesses.begin(); it != _cgiprocesses.end(); it++)
    {
        if (it->client_fd == fd)
            it->alive = false;
    }
    close(fd);
    _clients.erase(fd);
    for (std::vector<struct pollfd>::iterator it = _fds.begin(); it != _fds.end(); ++it)
    {
        if (it->fd == fd)
        {
            _fds.erase(it);
            break ;
        }
    }
    std::cout << "Client on FD " << fd << " properly disconnected." << std::endl;
}

static std::string extractPath(std::string b)
{
    size_t Bpos = b.find(" ");
    if (Bpos == std::string::npos)
        return "";
    size_t Epos = b.find(" ", Bpos + 1);
    if (Epos == std::string::npos)
        return "";
    std::string path = b.substr(Bpos + 1, Epos - Bpos - 1);
    return path;
}

int Server::handleClientRequest(int index)
{
    int fd = _fds[index].fd;
    char buffer[65536];
    ssize_t bytes_read = recv(fd, buffer, sizeof(buffer) - 1, MSG_DONTWAIT);

    if (bytes_read > 0)
    {
        buffer[bytes_read] = '\0';
        _clients[fd].appendToBuffer(buffer, bytes_read);

        std::string path = extractPath(_clients[fd].getBuffer());
        size_t max_body;
        if (path.empty())
            max_body = 1024 * 1024;
        else
        {
            t_location *loc = findLocation(path, _clients[fd].getConfig());
            if (!loc)
                max_body = 1024 * 1024;
            else
                max_body = loc->max_body_size;
        }
        if (_clients[fd].isRequestComplete(max_body))
        {
/* 			    std::cerr << "request complete ! body size=" 
              << _clients[fd].getBuffer().size() << std::endl; */
            processRequest(fd);
            return 0;
        }
        return 0;
/* 		else
			std::cerr << "request incomplete, buffer size=" << _clients[fd].getBuffer().size() << std::endl; */
	}
    else
    {
        removeClient(fd);
        return -1;
    }
}

void Server::processRequest(int fd)
{
    Request req;
    req.parse(_clients[fd].getBuffer());
    Response res;
    RouteContext ctx = buildRouteContext(req, _clients[fd].getConfig());
    size_t loc_limit = (ctx.loc && ctx.loc->max_body_size > 0) ? (size_t)ctx.loc->max_body_size : 0;

    if (req.getPath().empty() || req.getMethod().empty() || req.getVersion().empty())
        res.prepareErrorResponse(400, *ctx.config);
    else if (_clients[fd].isBodyTooLarge())
        res.prepareErrorResponse(413, *ctx.config);
    else if (loc_limit > 0 && req.getBody().size() > loc_limit)
        res.prepareErrorResponse(413, *ctx.config);
    else if (ctx.needsSlashRedirect)
    {
        res.addHeader("Location", req.getPath() + "/");
        res.prepareResponse(301, "text/html", "<h1>Redirecting...</h1>");
    }
    else if (handleRedirection(res, ctx)) {}
    else if (!isMethodAllowed(ctx.loc, req.getMethod()))
        res.prepareErrorResponse(405, *ctx.config);
    else if (ctx.loc && !ctx.loc->cgi_path.empty())
    {
        if (isCGI(ctx))
        {
            if (handleCGI(req, res, ctx, fd) == 0)
                return;
        }
        else
            res.prepareErrorResponse(404, *ctx.config);
    }
    else
    {
        switch (req.getMethodEnum())
        {
        case GET:
            handleGet(req, res, ctx);
            break;
        case POST:
            handlePost(req, res, ctx);
            break;
        case DELETE:
            handleDelete(res, ctx);
            break;
        default:
            res.prepareErrorResponse(405, *ctx.config);
            break;
        }
    }
    finalizeResponse(fd, res);
}

void Server::finalizeResponse(int fd, Response& res)
{
	if (_clients.find(fd) == _clients.end())
		return;
	_clients[fd].setResponse(res.getFullResponse());
	for (size_t i = 0; i < _fds.size(); i++)
	{
		if (_fds[i].fd == fd)
		{
			_fds[i].events = POLLOUT;
			return;
		}
	}
}

void Server::handleGet(Request &req, Response &res, RouteContext &ctx) 
{

    struct stat info;

    if (stat(ctx.fullPath.c_str(), &info) != 0){
        res.prepareErrorResponse(404, *ctx.config);
        return;
    }
    if (S_ISDIR(info.st_mode)) {
        std::string indexFile = (ctx.loc && !ctx.loc->index.empty()) ? ctx.loc->index : ctx.config->index;
        if (indexFile.empty())
            indexFile = "index.html";

        std::string indexPath = ctx.fullPath;
        if (indexPath[indexPath.size()-1] != '/')
            indexPath += "/" ;   
        indexPath += indexFile;

        struct stat indexStat;
        if (stat(indexPath.c_str(), &indexStat) == 0) {
            serveFile(indexPath, res, ctx);
            return;
        }
        else if (ctx.loc && ctx.loc->autoindex){
             generateAutoIndex(ctx.fullPath, req.getPath(), res, *ctx.config);
             return;
        }
        else {
            res.prepareErrorResponse(404, *ctx.config);
            return;
        }
    }
    else
        serveFile(ctx.fullPath, res, ctx);
}


void Server::serveFile(const std::string& path, Response& res, RouteContext& ctx)
{
    std::string content;

    if (!getFileContent(path, content))
        res.prepareErrorResponse(403, *ctx.config);
    else
        res.prepareResponse(200, getMimeType(path), content);
}

void Server::handlePost(Request &req, Response &res, RouteContext &ctx) {
    std::string body = req.getBody();
    if (!ctx.loc || ctx.loc->upload_dir.empty())
    {
        res.prepareResponse(200, "text/html", "<h1>OK</h1>");
        return ;
    }
    std::string contentType = req.getHeader("content-type");
    std::string uploadDir = extractUploadDir(ctx);
    std::string filename;
    if (contentType.find("multipart/form-data") != std::string::npos)
    {
        size_t boundPos = contentType.find("boundary=");
        if (boundPos == std::string::npos)
        {
            res.prepareErrorResponse(400, *ctx.config);
            return;
        }
        std::string boundary = "--" + contentType.substr(boundPos + 9);
        filename = extractFilename(req, ctx, body, boundary);
        body = extractMultipartBody(body, boundary);
    }
    else
        filename = extractFilename(req, ctx, body, "");
    saveFile(uploadDir + filename, body, res, *ctx.config);
}

std::string Server::extractUploadDir(RouteContext& ctx)
{
    std::string uploadDir = ctx.loc->upload_dir;

    if (uploadDir[uploadDir.size() - 1] != '/')
        uploadDir += "/";

    return uploadDir;
}

std::string Server::extractFilename(Request &req, RouteContext &ctx, const std::string &body, const std::string &boundary)
{

    std::string filename;

    if (!boundary.empty())
    {
        size_t partStart = body.find(boundary);
        size_t headersEnd = body.find("\r\n\r\n", partStart);
        std::string partHeaders = body.substr(partStart, headersEnd - partStart);
        size_t filePos = partHeaders.find("filename=\"");
        if (filePos != std::string::npos)
        {
            size_t start = filePos + 10;
            size_t end = partHeaders.find("\"", start);
            filename = partHeaders.substr(start, end - start);
        }
    }
    else
    {
        filename = req.getPath().substr(req.getPath().find_last_of('/') + 1);
        size_t filePos = body.find("filename=\"");
        if (filePos != std::string::npos)
        {
            size_t start = filePos + 10;
            size_t end = body.find("\"", start);
            filename = body.substr(start, end - start);
        }
    }
    if (filename.empty() && req.getPath() == ctx.loc->path)
    {
        std::ostringstream oss;
        oss << "upload_" << time(NULL);
        filename = oss.str();
    }
    return filename;
}

std::string Server::extractMultipartBody(const std::string &body, const std::string &boundary)
{       
    
        size_t partStart = body.find(boundary);
        if (partStart == std::string::npos)
            return "";
        size_t headersEnd = body.find("\r\n\r\n", partStart);
        if (headersEnd == std::string::npos)
            return "";
        std::string partHeaders = body.substr(partStart, headersEnd - partStart);
        size_t endPart = body.find(boundary, headersEnd);
        std::string MultiBody = body.substr(headersEnd + 4, endPart - 2 - (headersEnd + 4));

        return MultiBody;

}

void Server::saveFile(const std::string &path, const std::string &content, Response &res, const t_config &config)
{
	std::ofstream outFile(path.c_str(), std::ios::out | std::ios::binary);
	
	if (outFile.is_open())
	{
		outFile.write(content.data(), content.size());
		outFile.close();
		res.prepareResponse(201, "text/html", "<h1>File uploaded to " + path + "</h1>");
	}
	else
		res.prepareErrorResponse(500, config);
}

void Server::handleDelete(Response &res, RouteContext &ctx) {
    struct stat info;

    if (!ctx.loc || ctx.loc->upload_dir.empty()){
        res.prepareErrorResponse(405, *ctx.config);
        return;
    }
    if (!isSafePath(ctx.fullPath, ctx.loc->upload_dir)){
        res.prepareErrorResponse(403, *ctx.config);
        return;
    }
    if (stat(ctx.fullPath.c_str(), &info) != 0) {
        res.prepareErrorResponse(404, *ctx.config);
        return;
    }
    if (S_ISDIR(info.st_mode)) {
        res.prepareErrorResponse(403, *ctx.config);
        return;
    }
    if (std::remove(ctx.fullPath.c_str()) == 0)
        res.prepareResponse(200, "text/html", "<h1>File deleted.</h1>");
    else
    {
        if (errno == EACCES || errno == EPERM)
            res.prepareErrorResponse(403, *ctx.config);
        else if (errno == ENOENT)
            res.prepareErrorResponse(404, *ctx.config);
        else
            res.prepareErrorResponse(500, *ctx.config);
    }
}

int Server::sendResponse(size_t index)
{
    int fd = _fds[index].fd;
    std::string reponse = _clients[fd].getResponse();

    if (reponse.empty()) {
        _fds[index].events = POLLIN;
        return 0;
    }

    ssize_t bytes_sent = send(fd, reponse.c_str() + _clients[fd].getPending(), reponse.size() - _clients[fd].getPending(), MSG_NOSIGNAL);

    if (bytes_sent <= 0)
    {
        removeClient(fd);
        return -1;
    }
    else if (_clients[fd].getPending() + bytes_sent == reponse.size())
    {
        _clients[fd].clearBuffer();
        _clients[fd].setResponse("");
        removeClient(fd);
        return -1;
    }
    else
    {
        _clients[fd].setPending(bytes_sent);
        _fds[index].events = POLLOUT;
        return 0;
    }
}

bool Server::getFileContent(std::string path, std::string& content) {
    std::ifstream file(path.c_str(), std::ios::in | std::ios::binary);
    if (!file)
        return false;
    std::stringstream ss;
    ss << file.rdbuf();
    content = ss.str();
    return true;
}

std::string Server::getMimeType(std::string path) {
    size_t dotPos = path.find_last_of('.');
    if (dotPos == std::string::npos) return "text/plain";
    std::string ext = path.substr(dotPos);
    if (ext == ".html") return "text/html";
    if (ext == ".css")  return "text/css";
    if (ext == ".jpg" || ext == ".jpeg") return "image/jpeg";
    if (ext == ".png")  return "image/png";
    if (ext == ".gif")  return "image/gif";
    if (ext == ".ico")  return "image/x-icon";
    return "text/plain";
}

void Server::generateAutoIndex(std::string path, std::string urlPath, Response &res, const t_config& config)
{
	DIR *dir = opendir(path.c_str());
	if(!dir)
    {
		res.prepareErrorResponse(404, config);
        return ;
    }
	std::string html;
    if (!(getFileContent("./www/internal/autoindex_template.html", html)))
    {
        res.prepareErrorResponse(42, config);
        return ;
    }
    std::stringstream rows;
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        std::string name = entry->d_name;
        if (name == ".") continue;
        std::string link = urlPath;
        if (link.empty() || link[link.size() - 1] != '/') link += "/";
        link += name;
        rows << "<tr>"
             << "<td><a href=\"" << link << "\">" << name << (entry->d_type == DT_DIR ? "/" : "") << "</a></td>"
             << "<td>" << (entry->d_type == DT_DIR ? "[DIRECTORY]" : "[FILE]") << "</td>"
             << "</tr>";
    }
    closedir(dir);

    size_t pathPos = html.find("{{PATH}}");
    while (pathPos != std::string::npos) {
        html.replace(pathPos, 8, urlPath);
        pathPos = html.find("{{PATH}}", pathPos + urlPath.length());
    }

    size_t contentPos = html.find("{{CONTENT}}");
    if (contentPos != std::string::npos) 
        html.replace(contentPos, 11, rows.str());
    res.prepareResponse(200, "text/html", html);
    return;
}


t_location* Server::findLocation(std::string const &path, const t_config* config)
{
    t_location* bestMatch = NULL;
    size_t longestMatch = 0;

    for (size_t i = 0; i < config->locations.size(); i++) {
        std::string const &locPath = config->locations[i].path;
        //cas 1 : pattern d'extension (*.bla)
        if (locPath.size() > 1 && locPath[0] == '*') {
            std::string ext = locPath.substr(1); // ".bla"
            if (path.size() >= ext.size() &&
                path.compare(path.size() - ext.size(), ext.size(), ext) == 0) {
                return const_cast<t_location*>(&config->locations[i]);
            }
            continue;
        }
        //cas 2 : prefixe classique
        if (path.compare(0, locPath.length(), locPath) == 0) {
            if (locPath.length() >= longestMatch) {
                longestMatch = locPath.length();
                bestMatch = const_cast<t_location*>(&config->locations[i]);
            }
        }
    }
    //cas 3 : /directory sans slash => on cherche /directory/
    if (!bestMatch) {
        std::string pathWithSlash = path + "/";
        for (size_t i = 0; i < config->locations.size(); i++) {
            if (config->locations[i].path == pathWithSlash)
                return const_cast<t_location*>(&config->locations[i]);
        }
    }
    return bestMatch;
}

bool Server::isMethodAllowed(t_location* loc, const std::string& method)
{
    if (!loc || loc->methods.empty())
        return true;
    for (size_t i = 0; i < loc->methods.size(); i++)
    {
        if (loc->methods[i] == method)
            return true;
    }
    return false;
}

RouteContext Server::buildRouteContext(Request& req, const t_config* config)
{
    RouteContext ctx;

    ctx.config = config;
    ctx.needsSlashRedirect = false;
    ctx.loc = findLocation(req.getPath(), config);
    if (ctx.loc && ctx.loc->path != req.getPath()) {
        std::string pathWithSlash = req.getPath() + "/";
        for (size_t i = 0; i < config->locations.size(); i++) {
            if (config->locations[i].path == pathWithSlash) {
                ctx.loc = const_cast<t_location*>(&config->locations[i]);
                ctx.needsSlashRedirect = true;
                break;
            }
        }
    }

    ctx.root = (ctx.loc && !ctx.loc->root.empty()) ? ctx.loc->root : config->root; 
    if (ctx.loc && ctx.loc->path.size() > 1 && ctx.loc->path[0] == '*')
    {
        std::string parentPath = req.getPath().substr(0, req.getPath().rfind('/') + 1);
        t_location *parentLoc = findLocation(parentPath, config);
        if (parentLoc && !parentLoc->root.empty())
        {
            std::string filename = req.getPath().substr(req.getPath().rfind('/') + 1);
            ctx.fullPath = parentLoc->root + "/" + filename;
        }
        else
            ctx.fullPath = ctx.root + req.getPath();
    }
    else if (ctx.loc && !ctx.loc->root.empty())
    {
        if (ctx.needsSlashRedirect)
            ctx.fullPath = ctx.root;
        else
        {
            std::string suffix = req.getPath().substr(ctx.loc->path.length());
            ctx.fullPath = ctx.root + "/" + suffix;
        }
    }
    else
        ctx.fullPath = ctx.root + req.getPath();
    return ctx;
}

bool Server::handleRedirection(Response &res, RouteContext &ctx)
{
    if (ctx.loc && !ctx.loc->redirect.empty())
    {
        res.addHeader("Location", ctx.loc->redirect);
        res.prepareResponse(301, "text/html", "<h1>Redirecting...</h1>");
        return true;
    }
    return false;
}

bool Server::isSafePath(const std::string fullPath, const std::string& allowedDir)
{
    char* normalDir = realpath(allowedDir.c_str(), NULL);
    if (normalDir == NULL)
        return false;
    std::string zone = normalDir;
    free(normalDir);
    if (zone[zone.size() - 1] != '/')
        zone += "/";

    std::string parent = fullPath.substr(0, fullPath.find_last_of('/'));
    std::string filename = fullPath.substr(fullPath.find_last_of('/') + 1);
    char* normalParent = realpath(parent.c_str(), NULL);
    if (normalParent == NULL)
        return false;
    std::string resolvedPath = std::string(normalParent) + "/" + filename;
    free(normalParent);

    return resolvedPath.compare(0, zone.size(), zone) == 0;
}
