#include <IRC.hpp>

void        Commands::oper(User *user, IRC *server)
{
    std::vector<std::string> user_params = user->get_params();
    std::vector<std::string> reply_params;

    if (user->get_params_size() < 2) //ERR_NEEDMOREPARAMS 461
    {
        reply_params.push_back("OPER");
        server->send_rpl("461", user, reply_params, "");
    }
    else
    {
        std::string name = user_params[0];
        std::string password = user_params[1];
        if(name == OPER_NAME && password == OPER_PASS) //RPL_YOUROPER 381
        {
            server->send_rpl("381", user, reply_params, "");

            //then add mode to user
            std::vector<std::string> tmp;
            tmp.push_back(user->get_nickname());
            tmp.push_back("+o");
            user->set_params(tmp);
            server->_commands->mode(user, server);
        }
        else // ERR_PASSWDMISMATCH 464
            server->send_rpl("464", user, reply_params, "");
    }
}