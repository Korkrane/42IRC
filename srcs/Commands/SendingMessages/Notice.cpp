#include <IRC.hpp>

void Commands::notice(User *user, IRC *server)
{
#if DEBUG == 1
    std::cout << RED << "ENTER NOTICE CMD" << NC << std::endl;
#endif
    std::vector<std::string> params = user->get_params();
    std::vector<std::string> reply_params;
    if (params.size() < 1) //s'il n'y a pas de recipient
    {
        reply_params.push_back(user->get_command_name());
        server->send_rpl("411", user, reply_params, "");
        return;
    }
    else if (params.size() < 2 || params[1].empty()) //s'il n'y a pas de message à envoyer
    {
        server->send_rpl("412", user, reply_params, "");
        return;
    }
    //Dans le cas ou il y a plusieurs recipinets ex: /privmsg user1,user2,#channel3
    std::vector<std::string> recipients = fill_recipients(params[0]);
    //Envoie le message pour chaque recipient
    for (std::vector<std::string>::iterator it = recipients.begin(); it != recipients.end(); it++)
    {
        std::string message = params[1];
        //Check si le recipient est un user ou une channel
        User *targetuser = server->get_user_ptr((*it));
        Channel *targetchannel = server->get_channel_ptr((*it));
        if (!targetuser && !targetchannel) //si il n'existe pas de channel ou d'user à ce nom
        {
#if DEBUG == 1
            std::cout << PURPLE << "DEBUG: Target doesnt exist" << NC << std::endl;
#endif
            reply_params.push_back((*it));
            server->send_rpl("401", user, reply_params, "");
            reply_params.clear();
        }
        else if (targetuser && !targetchannel) //si le recipient est un user
        {
#if DEBUG == 1
            std::cout << PURPLE << "DEBUG: Target is a user" << NC << std::endl;
#endif
            //le recipient recoit le message
            reply_params.push_back(user->get_nickname());
            reply_params.push_back(user->get_username());
            reply_params.push_back(user->get_hostname());
            reply_params.push_back(targetuser->get_nickname());
            reply_params.push_back(message);
            server->send_rpl("1001", targetuser, reply_params, "NOTICE");
        }
        else if (!targetuser && targetchannel) //si le recipient est un channel
        {
#if DEBUG == 1
            std::cout << BLUE << "DEBUG: Target is a channel" << NC << std::endl;
#endif
            reply_params.push_back(user->get_nickname());
            reply_params.push_back(user->get_username());
            reply_params.push_back(user->get_hostname());
            reply_params.push_back(targetchannel->get_name());
            reply_params.push_back(message);
            std::vector<User *> users_execept_sender;
            std::vector<User *> users = targetchannel->get_members();
            for (unsigned long i = 0; i < users.size(); i++)
                users_execept_sender.push_back(users[i]);
            User *sender = server->get_user_ptr(user->get_nickname());
            for (std::vector<User *>::iterator it = users_execept_sender.begin(); it != users_execept_sender.end(); it++)
            {
                if ((*it) == sender)
                {
                    users_execept_sender.erase(it);
                    break;
                }
            }
            server->send_rpl_to_all_members("1001", users_execept_sender, reply_params, "NOTICE");
            reply_params.clear();
        }
    }
#if DEBUG == 1
    std::cout << RED << "EXIT NOTICE CMD" << NC << std::endl;
#endif
}