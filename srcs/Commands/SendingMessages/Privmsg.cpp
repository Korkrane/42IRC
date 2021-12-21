#include <IRC.hpp>

std::vector<std::string> Commands::fill_recipients(std::string target)
{
#if DEBUG == 1
    std::cout << PURPLE << "ENTER IN FILL RECIPIENTS FOR PRIVMSG" << NC << std::endl;
#endif
    std::vector<std::string> recipients = old_ft_split(target, ",");
#if DEBUG == 1
    for (std::vector<std::string>::iterator it = recipients.begin(); it != recipients.end(); it++)
        std::cout << PURPLE << "Target for privmsg: " << (*it) << std::endl;
#endif
    return recipients;
}

void Commands::privmsg(User *user, IRC *server)
{
#if DEBUG == 1
    std::cout << RED << "ENTER PRIVMSG CMD" << NC << std::endl;
#endif
    std::vector<std::string> params = user->get_params();
    if (user->get_params_size() < 1) //s'il n'y a pas de recipient
    {
        std::vector<std::string> reply_params;
        reply_params.push_back(user->get_command_name());
        server->send_rpl("411", user, reply_params, "");
        return;
    }
    else if (user->get_params_size() < 2 || params[1].empty()) //s'il n'y a pas de message à envoyer
    {
        std::vector<std::string> reply_params;
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
            std::vector<std::string> reply_params;
            reply_params.push_back((*it));
            server->send_rpl("401", user, reply_params, "");
        }
        else if (targetuser && !targetchannel) //si le recipient est un user
        {
#if DEBUG == 1
            std::cout << PURPLE << "DEBUG: Target is a user" << NC << std::endl;
#endif
            std::vector<std::string> reply_params;
#if DEBUG == 1
            std::cout << PURPLE << "DEBUG: target is away ? " << targetuser->is_away() << NC << std::endl;
#endif
            if (targetuser->is_away()) //si le recipient est afk prevenir celui qui envoie
            {
                reply_params.push_back(targetuser->get_nickname());
                reply_params.push_back(targetuser->get_away_mssg());
                server->send_rpl("301", user, reply_params, "");
                reply_params.clear();
            }
            //puis (qu'il soit afk ou non) le recipient recoit le message
            reply_params.push_back(user->get_nickname());
            reply_params.push_back(user->get_username());
            reply_params.push_back(user->get_hostname());
            reply_params.push_back(targetuser->get_nickname());
            reply_params.push_back(message);
            server->send_rpl("1001", targetuser, reply_params, "PRIVMSG");
        }
        else if (!targetuser && targetchannel) //si le recipient est un channel
        {
#if DEBUG == 1
            std::cout << BLUE << "DEBUG: Target is a channel" << NC << std::endl;
#endif
            std::vector<std::string> reply_params;

            if (targetchannel->user_is_member(user))
            {
                reply_params.push_back(user->get_nickname());
                reply_params.push_back(user->get_username());
                reply_params.push_back(user->get_hostname());
                reply_params.push_back(targetchannel->get_name());
                reply_params.push_back(message);
                std::vector<User *> users_execept_sender;
                std::vector<User *> users = targetchannel->get_members();
                ;

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
                server->send_rpl_to_all_members("1001", users_execept_sender, reply_params, "PRIVMSG");
            }
            else
            {
                reply_params.push_back(targetchannel->get_name());
                server->send_rpl("404", user, reply_params, "");
            }
        }
    }
#if DEBUG == 1
    std::cout << RED << "EXIT PRIVMSG CMD" << NC << std::endl;
#endif
}