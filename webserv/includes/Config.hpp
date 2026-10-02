#ifndef CONFIG_HPP
# define CONFIG_HPP

# include <string>
# include <vector>
# include <map>
# include <cctype>

typedef struct s_listen {
	int			port;
	std::string	host;

    s_listen() : port(0) {};
} t_listen;

typedef struct s_location {
    std::string					path;
    std::string					root;
    bool						autoindex;
    std::vector<std::string>	methods;
    std::string					index;
    std::string					cgi_path;
	std::string					upload_dir;
	std::string					redirect;
    size_t                      max_body_size;

    s_location() : autoindex(false), max_body_size(0) {};
} t_location;

typedef struct s_config {
	std::vector<t_listen>		listens;
    std::string					root;
    std::string					server_name;
    std::string					index;
    std::map<int, std::string>	error_pages;
    long						max_body_size;
    std::vector<t_location>		locations;

    s_config() : max_body_size(0) {};
} t_config;

#endif