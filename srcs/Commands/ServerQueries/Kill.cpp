#include <IRC.hpp>

void Commands::kill(User *user, IRC *server)
{
    #if DEBUG
        std::cout << RED << "ENTER KILL CMD" << NC << std::endl;
    #endif
    std::vector<std::string> params = user->get_params();
    std::vector<std::string> params_reply;
    if(user->get_operator_status() == false)
    {
        server->send_rpl("481", user, params_reply, "");
        return ;
    }
    if (user->get_params_size() < 1) //s'il n'y a pas de target
    {
        params_reply.push_back(user->get_command_name());
        server->send_rpl("411", user, params_reply, "");
        return;
    }
    else if (user->get_params_size() >= 2)
    {
        //TODO gérer le comment.
        User *targetuser = server->get_user_ptr((params[0]));
        std::cout << targetuser << std::endl;
        if(params[0] == server->get_name())
            server->send_rpl("483", user, params_reply, "");
        if(targetuser)
            server->_disconnect_list.push_back(targetuser->get_socket());
        else
        {
            params_reply.push_back(params[0]);
            server->send_rpl("401", user, params_reply, "");
        }
    }
    #if DEBUG
        std::cout << RED << "EXIT KILL CMD" << NC << std::endl;
    #endif
}