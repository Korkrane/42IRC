#include "IRC.hpp"

void Commands::kill(User *user, IRC *server)
{
#if DEBUG == 1
    std::cout << RED << "ENTER KILL CMD" << NC << std::endl;
#endif
    std::vector<std::string> params = user->get_params();
    std::vector<std::string> reply_params;

    if (!user->is_operator())
        server->send_rpl("481", user, reply_params, "");
    else if (params.size() < 1) //s'il n'y a pas de target
    {
        reply_params.push_back(user->get_command_name());
        server->send_rpl("411", user, reply_params, "");
    }
    else if (params.size() >= 2)
    {
        //TODO gérer le comment.
        User *target = server->get_user_ptr((params[0]));
        if (params[0] == server->get_name())
            server->send_rpl("483", user, reply_params, "");
        else if (target)
            server->_disconnect_list.push_back(target->get_fd());
        else
        {
            reply_params.push_back(params[0]);
            server->send_rpl("401", user, reply_params, "");
        }
    }
#if DEBUG == 1
    std::cout << RED << "EXIT KILL CMD" << NC << std::endl;
#endif
}