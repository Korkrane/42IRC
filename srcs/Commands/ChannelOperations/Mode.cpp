#include <IRC.hpp>

void            Commands::mode(User *user, IRC *server)
{
    #if DEBUG
        std::cout << RED << "ENTER MODE COMMAND" << NC << std::endl;
    #endif
    std::vector<std::string> params = user->get_params();
    User *targetuser = server->get_user_ptr((params[0]));
    Channel *targetchannel = server->get_channel_ptr((params[0]));
    if(targetuser)
        mode_user(user, server);
    else if(targetchannel)
        mode_channel(user, server);
    else if(!targetchannel && !targetuser)
    {
        std::vector<std::string> reply_params;
        reply_params.push_back(params[0]);
        server->send_rpl("401", user, reply_params, ""); //ERR_NOSUCHNICK
    }
    #if DEBUG
        std::cout << RED << "EXIT MODE COMMAND" << NC << std::endl;
    #endif
}