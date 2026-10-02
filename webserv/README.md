*This project has been created as part of the 42 curriculum by dcasiell, lde_sutt.*

# Webserv

## Description

Webserv is a fully custom HTTP/1.1 server written in C++98, built as part of the 42 School curriculum. The goal is to implement a standards-compliant web server from scratch — without using any external libraries — capable of serving static websites, handling file uploads, processing CGI scripts, and managing multiple simultaneous clients.

The server is non-blocking and event-driven, using a single `poll()` call to monitor all I/O operations across clients and listening sockets simultaneously.

Key features:
- Multi-server, multi-port configuration via a NGINX-inspired `.conf` file
- GET, POST, and DELETE methods
- Static file serving with autoindex (directory listing)
- File upload support (multipart/form-data and raw binary)
- Chunked transfer encoding (decode on receive, unchunked to CGI)
- CGI execution (Python, custom binaries) with non-blocking async process management and 15-second timeout
- Custom error pages in FICSIT/Satisfactory theme
- Per-location `client_max_body_size` enforcement
- Path traversal protection on DELETE via `realpath`
- Graceful shutdown on SIGINT

## Instructions

### Requirements

- Linux (tested on Ubuntu 24)
- `c++` compiler with C++98 support
- `python3` for CGI scripts

### Compilation

```bash
make
```

### Execution

```bash
./webserv [config_file]
```

If no config file is provided, the server defaults to `conf/ws.conf`.

### Example

```bash
./webserv conf/ws.conf
```

Then open your browser at `http://localhost:8080`.

### Running the official tester

```bash
./tester http://localhost:8080
```

Make sure the server is running with `conf/ws.conf` and the `YoupiBanane/` directory is present at the project root before running the tester.

### Configuration file

The configuration follows a NGINX-inspired syntax. Example:

```nginx
server {
    listen 8080;
    server_name mysite.com;
    root ./www;
    index index.html;
    max_body_size 1048576;
    error_page 404 /errors/404.html;

    location / {
        methods GET;
        autoindex off;
    }

    location /upload {
        methods GET POST DELETE;
        upload_dir ./upload;
        root ./upload;
        autoindex on;
    }

    location /cgi {
        methods GET POST;
        cgi_path /usr/bin/python3;
    }

    location *.bla {
        methods GET POST;
        cgi_path ./cgi_tester;
    }

    location /post_body {
        methods POST;
        client_max_body_size 100;
    }
}
```

Supported directives: `listen`, `server_name`, `root`, `index`, `max_body_size`, `error_page`, `location`, `methods`, `autoindex`, `upload_dir`, `cgi_path`, `redirect`, `client_max_body_size`.

## Project Structure

```
.
├── conf/               # Configuration files
├── includes/           # Header files
├── srcs/
│   ├── cgi/            # CGI execution, env building, async process handling
│   ├── http/           # Request and Response classes
│   ├── network/        # Server and Client classes
│   └── parsing/        # Configuration file parser
├── www/                # Static website files (FICSIT theme)
│   ├── cgi/            # Python CGI scripts
│   ├── errors/         # Custom error pages
│   ├── example/        # Example files for autoindex demo
│   └── internal/       # Server-side templates (autoindex)
└── upload/             # Upload directory
```

## Resources

### HTTP & Networking
- [RFC 7230 — HTTP/1.1 Message Syntax](https://datatracker.ietf.org/doc/html/rfc7230)
- [RFC 7231 — HTTP/1.1 Semantics](https://datatracker.ietf.org/doc/html/rfc7231)
- [RFC 3875 — The Common Gateway Interface (CGI)](https://datatracker.ietf.org/doc/html/rfc3875)
- [Beej's Guide to Network Programming](https://beej.us/guide/bgnet/)
- [MDN Web Docs — HTTP](https://developer.mozilla.org/en-US/docs/Web/HTTP)
- [NGINX documentation](https://nginx.org/en/docs/) — used as behavioral reference

### C++ & Systems
- [cppreference.com](https://en.cppreference.com/) — C++98 standard library reference
- `man` pages: `poll(2)`, `socket(2)`, `recv(2)`, `send(2)`, `fork(2)`, `execve(2)`, `waitpid(2)`

### AI Usage

Claude (Anthropic) was used throughout this project in a Socratic teaching role — helping understand concepts rather than generating code directly. Specific uses include:

- Understanding non-blocking I/O architecture and the `poll()` event loop model
- Clarifying HTTP protocol concepts (chunked transfer encoding, multipart/form-data, header parsing, case-insensitive header matching)
- Designing the async CGI architecture: non-blocking pipes, `WNOHANG` waitpid, process tracking with timeout via a `CGIProcess` vector
- Debugging iterator safety when erasing from `std::vector` during iteration
- Understanding the null-byte truncation issue with `std::string +=` for binary data and the correct use of `.append(ptr, length)`
- Understanding CGI environment variables and the server-CGI communication protocol
- Reviewing edge cases in request parsing, binary file upload, and path traversal protection with `realpath`
- Generating the front-end HTML/CSS pages for the demo website (FICSIT/Satisfactory theme)
