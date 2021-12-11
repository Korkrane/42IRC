#include <IRC.hpp>

//TODO: a deplacer dans un dossier commande
void Commands::ping_cmd(User *user, IRC *server)
{
    (void)user;
    (void)server;
    #if DEBUG
        std::cout << BLUE << "ENTER PING CMD" << NC << std::endl;
    #endif
    std::vector<std::string> reply_params;
    std::string reply;

    //reply = "hexchat request ping\r\n";
    reply = build_reply(999, user, reply_params);
    server->_response_queue.push_back(std::make_pair(user->get_socket(), reply));
    reply_params.clear();
    #if DEBUG
        std::cout << RED << "EXIT PING CMD" << NC << std::endl;
    #endif
}