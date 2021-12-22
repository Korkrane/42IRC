#include "IRC.hpp"

void Commands::die(User *user, IRC *server)
{
#if DEBUG
    std::cout << RED << "ENTER DIE CMD" << NC << std::endl;
#endif
    std::vector<std::string> params = user->get_params();
    std::vector<std::string> reply_params;

    if (!user->is_operator())
        server->send_rpl("481", user, reply_params, "");
    else
    {
        server->die = true;
        std::vector<User *> users = server->get_users();
        for (std::vector<User *>::iterator it = users.begin(); it != users.end(); it++)
            server->_disconnect_list.push_back((*it)->get_fd());
    }
#if DEBUG
    std::cout << RED << "EXIT DIE CMD" << NC << std::endl;
#endif
}