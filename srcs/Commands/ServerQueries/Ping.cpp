#include <IRC.hpp>

void Commands::ping_cmd(User *user, IRC *server)
{
    #if DEBUG
        std::cout << BLUE << "ENTER PING CMD" << NC << std::endl;
    #endif
    std::vector<std::string> params;

    server->send_rpl("999", user, params, "");
    #if DEBUG
        std::cout << RED << "EXIT PING CMD" << NC << std::endl;
    #endif
}