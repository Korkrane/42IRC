#include <IRC.hpp>

std::vector<std::string> Commands::fill_recipients(std::string target)
{
    std::vector<std::string> recipients = ft_split(target, ",");
    #if DEBUG
        for(std::vector<std::string>::iterator it = recipients.begin(); it != recipients.end(); it++)
            std::cout << PURPLE << "Target for privmsg: " << (*it) << std::endl;
    #endif
    return recipients;
}

    //TODO 404 ERR CAN NOT SEND TO CHAN
    //Sent to a user who is either (a) not on a channel
    //       which is mode +n or (b) not a chanop (or mode +v) on
    //       a channel which has mode +m set or where the user is
    //       banned and is trying to send a PRIVMSG message to
    //       that channel.

void Commands::privmsg(User *user, IRC *server)
{
    #if DEBUG
        std::cout << RED << "ENTER PRIVMSG CMD" << NC << std::endl;
    #endif
    std::vector<std::string> params = user->get_params();
    if (user->get_params_size() < 1) //s'il n'y a pas de recipient
    {
        std::vector<std::string> params_reply;
        params_reply.push_back(user->get_command_name());
        server->send_rpl("411", user, params_reply, "");
        return;
    }
    else if (user->get_params_size() < 2) //s'il n'y a pas de message à envoyer
    {
        std::vector<std::string> params_reply;
        server->send_rpl("412", user, params_reply, "");
        return;
    }
    //Dans le cas ou il y a plusieurs recipinets ex: /privmsg user1,user2,#channel3
    std::vector<std::string> recipients = fill_recipients(params[0]);
    //Envoie le message pour chaque recipient
    for(std::vector<std::string>::iterator it = recipients.begin(); it != recipients.end(); it++)
    {
        std::string message = params[1];
        //CHeck si le recipient est un user ou une channel
        User *targetuser = server->get_user_ptr((*it));
        Channel *targetchannel = server->get_channel_ptr((*it));
        if(!targetuser && !targetchannel) //si il n'existe pas de channel ou d'user à ce nom
        {
            std::vector<std::string> reply_params;
            reply_params.push_back((*it));
            server->send_rpl("401", user, reply_params, ""); ///TODO check if he sends notice or error
        }
        else if(targetuser && !targetchannel) //si le recipient est un user
        {
            std::vector<std::string> reply_params;
            if(targetuser->user_is_away()) //si le recipient est afk
            {
                reply_params.push_back(targetuser->get_nickname());
                reply_params.push_back(targetuser->get_away_mssg());
                server->send_rpl("301", user, reply_params, "");
            }
            else //TODO build reply correctly
                server->send_rpl("1001", targetuser, reply_params, "PRIVMSG");
        }
        else if(!targetuser && targetchannel) //si le recipient est un channel
        {
            //TODO build reply correctly
            server->send_rpl_to_all_members("1001", targetchannel->get_members(), params, "PRIVMSG");
        }
    }
    #if DEBUG
        std::cout << RED << "EXIT PRIVMSG CMD" << NC << std::endl;
    #endif
}

/*
void Commands::send_one_word_privmsg(User *target, User *user, IRC *server, std::string message)
{
    (void)user;

    std::string rpl = server->init_rpl(user);
    rpl += " PRIVMSG " + target->get_nickname();
    rpl += message;
    rpl += "\r\n";
    return;
}
*/