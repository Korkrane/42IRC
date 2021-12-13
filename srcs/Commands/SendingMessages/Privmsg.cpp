#include <IRC.hpp>

std::vector<std::string> Commands::fill_recipients(std::string target)
{
    std::vector<std::string> recipients;

    recipients = ft_split(target, ",");
    #if DEBUG
        for(std::vector<std::string>::iterator it = recipients.begin(); it != recipients.end(); it++)
            std::cout << PURPLE << "Target for privmsg: " << (*it) << std::endl;
    #endif
    return recipients;
}

void Commands::privmsg(User *user, IRC *server)
{
    #if DEBUG
        std::cout << RED << "ENTER PRIVMSG CMD" << NC << std::endl;
    #endif
    int size = user->get_params_size();
    std::vector<std::string> error;
    std::vector<std::string> params = user->get_params();
    //TODO
    // 411ERR_NORECIPIENT
              //":No recipient given (<command>)"
    //404 ERR CAN NOT SEND TO CHAN
    //Sent to a user who is either (a) not on a channel
    //       which is mode +n or (b) not a chanop (or mode +v) on
    //       a channel which has mode +m set or where the user is
    //       banned and is trying to send a PRIVMSG message to
    //       that channel.
    //401 no_such_nick when didnt find the user target
    //412 no text to send
    //407 err too many targets
     //Returned to a client which is attempting to send a
     //      PRIVMSG/NOTICE using the user@host destination format
     //      and for a user@host which has several occurrences.
     //
     //    - Returned to a client which trying to send a
     //      PRIVMSG/NOTICE to too many recipients.
     //
     //    - Returned to a client which is attempting to JOIN a safe
     //      channel using the shortname when there are more than one
     //      such channel.
    //TODO: je n ai pas reussi a reproduire l erreur toomanytarget
    //TODO /privmsg user2,user3,#chanlol  hello  -- with #chanlol not existing gonna send hello to user2 & user3 and return 401 for chan
    if (size < 1)
    {
        std::vector<std::string> params_reply;
        params_reply.push_back(user->get_command_name());
        server->send_rpl("411", user, params_reply, "");
        return;
    }
    else if (size < 2)
    {
        std::vector<std::string> params_reply;
        server->send_rpl("412", user, params_reply, "");
        return;
    }
    //On analyse les params
    std::string target = params.front();
    std::vector<std::string> targets = fill_recipients(target);

    for(std::vector<std::string>::iterator it = targets.begin(); it != targets.end(); it++)
    {
        std::string message = params[1];
        User *targetuser = server->get_user_ptr((*it));
        Channel *targetchannel = server->get_channel_ptr((*it));
        if(!targetuser && !targetchannel)
        {
            std::vector<std::string> reply_params;

            reply_params.push_back((*it));
            ///TODO check if he sends notice or error
            server->send_rpl("401", user, reply_params, "");
        }
        else if(targetuser && !targetchannel)
        {
            //TODO build reply correctly
            //here add elements to handle away status :)
            server->send_rpl("1001", targetuser, params, "PRIVMSG");
        }
        else if(!targetuser && targetchannel)
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