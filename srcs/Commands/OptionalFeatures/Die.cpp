#include <IRC.hpp>

void Commands::die(User *user, IRC *server)
{
#if DEBUG
    std::cout << RED << "ENTER DIE CMD" << NC << std::endl;
#endif
    std::vector<std::string> params = user->get_params();
    std::vector<std::string> params_reply;

    if (user->is_operator() == false)
        server->send_rpl("481", user, params_reply, "");
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