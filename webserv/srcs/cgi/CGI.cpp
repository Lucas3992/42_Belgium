#include "CGI.hpp"

std::string Request::getQuery_String() {
	size_t found = _rawPath.rfind("?");
	if (found != std::string::npos)
		return _rawPath.substr(found +1);
	return "";
}

std::string Request::getContent_Length() {
	std::stringstream ss;
	ss << getBody().size();
	return ss.str();
}

static std::string getServer_Port(RouteContext& ctx) {
	std::stringstream ss;
	ss << ctx.config->listens[0].port;
	return ss.str();
}

std::vector<std::string> CGI::buildEnv(Request& req, RouteContext& ctx) {
	std::vector<std::string> env;
	env.push_back("REQUEST_METHOD=" + req.getMethod());
	env.push_back("QUERY_STRING=" + req.getQuery_String());
	env.push_back("CONTENT_TYPE=" + req.getHeader("content-type"));
	env.push_back("CONTENT_LENGTH=" + req.getContent_Length());
	env.push_back("SCRIPT_FILENAME=" + ctx.fullPath);
	env.push_back("PATH_INFO=" + req.getPath());
	env.push_back("SERVER_PROTOCOL=HTTP/1.1");
	env.push_back("SERVER_NAME=" + ctx.config->server_name);
	env.push_back("SERVER_PORT=" + getServer_Port(ctx));

	const std::map<std::string, std::string>& headers = req.getHeaders();
    for (std::map<std::string, std::string>::const_iterator it = headers.begin();
         it != headers.end(); ++it) {
        std::string key = "HTTP_";
        for (size_t i = 0; i < it->first.size(); i++)
            key += (it->first[i] == '-') ? '_' : std::toupper(static_cast<unsigned char>(it->first[i]));
        env.push_back(key + "=" + it->second);
    }
	return env;
}

std::vector<std::string> CGI::buildArgv(RouteContext& ctx) {
	std::vector<std::string> av;
	av.push_back(ctx.loc->cgi_path);
	av.push_back(ctx.fullPath);
	return av;
}

static char** convert(const std::vector<std::string>& v) {
    size_t size = v.size();
    char** av = new char*[size + 1];
    for (size_t i = 0; i < size; i++) {
        av[i] = new char[v[i].length() + 1];
        std::strcpy(av[i], v[i].c_str());
    }
    av[size] = NULL;
    return av;
}

int CGI::readFromOutput(int out, std::string& output) {
	char buf[4096];
	ssize_t b;
	while ((b = read(out, buf, sizeof(buf))) > 0)
		output.append(buf, b);
	if (b < 0)
		return -1;
	return 0;
}

static void closeFds(int f1, int f2) {
	close(f1);
	close(f2);
}

static void deleteArray(char** array) {
	for (int i = 0; array[i] != NULL; i++)
		delete[] array[i];
	delete[] array;
}

static void dofork(int in[2], int out[2], std::vector<std::string>& env, std::vector<std::string>& argv) {
	closeFds(in[1], out[0]);
	dup2(in[0], STDIN_FILENO);
	dup2(out[1], STDOUT_FILENO);
	closeFds(in[0], out[1]);
	char **charEnv = convert(env);
	char **charArgv = convert(argv);
	execve(charArgv[0], charArgv, charEnv);
	deleteArray(charEnv);
	deleteArray(charArgv);
	_exit(1);
}

CGIProcess CGI::execute(Request& req, std::vector<std::string>& env, std::vector<std::string>& argv) {
    int in[2];
    int out[2];
    pid_t pid;

    if (pipe(in) == -1)
        throw CGIException("Error: pipe failed");
    if (pipe(out) == -1) {
        closeFds(in[0], in[1]);
        throw CGIException("Error: pipe failed");
    }
    pid = fork();
    if (pid == -1) {
        closeFds(in[0], in[1]);
        closeFds(out[0], out[1]);
        throw CGIException("Error: fork failed");
    }
    fcntl(in[1],  F_SETFL, O_NONBLOCK);
    fcntl(out[0], F_SETFL, O_NONBLOCK);
    if (pid == 0)
        dofork(in, out, env, argv);
    closeFds(in[0], out[1]);
    CGIProcess current;
    current.pipe_in     = in[1];
    current.pipe_out    = out[0];
    current.pid         = pid;
    current.start       = time(NULL);
    current.body        = req.getBody();
    current.body_offset = 0;
    current.output      = "";
    if (current.body.empty()) {
        close(current.pipe_in);
        current.pipe_in = -1;
    }
    return current;
}

void CGI::parseOutput(std::string& output, Response& resp) {
/*  la rep du script python doit etre exactement 
    Content-Type: text/html\r\n
    \r\n
    <html>resultat</html> */
    size_t ctPos = output.find("Content-Type: ");
    if (ctPos == std::string::npos)
        throw CGIException("Error: 'Content-Type: ' missing");
    size_t ctEnd = output.find("\r\n", ctPos + 14);
    std::string contentType = output.substr(ctPos + 14, ctEnd - (ctPos + 14));
    size_t sepPos = output.find("\r\n\r\n");
    if (sepPos == std::string::npos)
        throw CGIException("Error: '\\r\\n\\r\\n' missing");
    std::string body = output.substr(sepPos + 4);
    resp.prepareResponse(200, contentType, body);
}

bool Server::isCGI(RouteContext &ctx) {
    if (ctx.loc && ctx.loc->path.size() > 1 && ctx.loc->path[0] == '*')
        return true;
    struct stat info;
    if (stat(ctx.fullPath.c_str(), &info) != 0)
        return false;
    if (S_ISDIR(info.st_mode))
        return false;
    return true;
}

int Server::handleCGI(Request &req, Response &res, RouteContext &ctx, int fd) {
	try {
		CGI cgi;
		CGIProcess process;
		std::vector<std::string> env = cgi.buildEnv(req, ctx);
		std::vector<std::string> av = cgi.buildArgv(ctx);
		process = cgi.execute(req, env, av);
		process.client_fd = fd;
		process.config = ctx.config;
		process.alive = true;
		_cgiprocesses.push_back(process);
		registerCGIPipes(_cgiprocesses.back());
		return 0;
	} catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		res.prepareErrorResponse(500, *ctx.config);
		return -1;
	}
}

void Server::registerCGIPipes(CGIProcess& process) {
    struct pollfd pfd;
    pfd.fd = process.pipe_out;
    pfd.events = POLLIN;
    pfd.revents = 0;
    _fds.push_back(pfd);
    _pipe_to_cgi[process.pipe_out] = process.pid;
    if (process.pipe_in != -1) {
        pfd.fd = process.pipe_in;
        pfd.events = POLLOUT;
        pfd.revents = 0;
        _fds.push_back(pfd);
        _pipe_to_cgi[process.pipe_in] = process.pid;
    }
}