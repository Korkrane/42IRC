#include <irc.hpp>

void Commands::ping_cmd(User *user, IRC *server)
{
    (void)user;
    (void)server;
    #if DEBUG
        std::cout << "DEBUG: enter ping" << std::endl;
    #endif
    std::vector<std::string> reply_params;
    std::string reply;

    reply = "hexchat request ping\r\n";
    server->_response_queue.push_back(std::make_pair(user->get_socket(), reply));
    reply_params.clear();
}