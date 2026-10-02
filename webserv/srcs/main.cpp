#include "Server.hpp"
#include <iostream>
#include <signal.h>
#include <cstdlib>
#include "Parsing.hpp"

void handle_sigint(int sig) {
    (void)sig;
    Server::g_keep_running = false;//sinon ca tue sans fermer proprement les sockets et des laisse des process orphelins qui continuent de tourner
    std::cout << "\nArrêt du serveur..." << std::endl;
}

int main(int ac, char** av) {
	
    if (ac > 2) {
        std::cout << "Error: Too many arguments." << std::endl;
        return 1;
    }
    try {
        Parser config_ws;
        std::vector<t_config> config;
        if ( ac == 1)
            config_ws.ultimateParsing("conf/ws.conf");
        else
            config_ws.ultimateParsing(av[1]);
        config = config_ws.getConfig();
        
        signal(SIGINT, handle_sigint);
        Server webserv(config);        
        webserv.run();
        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "Erreur fatale : " << e.what() << std::endl;
        return 1;
    }
}