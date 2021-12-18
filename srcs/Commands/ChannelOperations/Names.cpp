#include <IRC.hpp>

/**
 * @brief Va servir notamment (voir exclusivement) A NAMES pour envoyer la liste
 * des utilisteurs en indiquant leurs roles. La commande names constitue une seule 
 * ligne contrairement a la commande WHO. 
 * @param user 
 * @param channel 
 * @param server 
 * @param code 
 */
void Commands::send_members_nick(User *user, Channel *channel, IRC *server)
{
    //On va boucler sur tous les membres de la channel 
    std::vector<User *> members = channel->get_members();
    std::vector<User *>::iterator it = members.begin();
    std::vector<User *>::iterator ite = members.end();

    std::string rpl;
    User *oper = channel->get_operators().front();

    rpl = ":127.0.0.1 353 " + user->get_nickname();
    rpl += " = " + channel->get_name() + " :";
    rpl += "@"+ oper->get_nickname() + " ";

    while (it != ite)
    {
        //Pour l'instant on ne gere qu'un seul operateur
        if ((*it) != oper)
        {
            rpl += (*it)->get_nickname() + " ";
        }
        it++;
    }
    rpl += "\r\n";
    server->_response_queue.push_back(std::make_pair(user->get_fd(), rpl));
#if MALATINI
    std::cout << GREEN << rpl<< NC << std::endl;
    std::cout << GREEN << "Join rpl sent to socket : " << user->get_fd() << std::endl;
#endif
    server->send_rpl("366", user, user->get_params(), "");//ENDOFNAMES
#if MALATINI
    std::cout << GREEN << rpl << NC << std::endl;
    std::cout << GREEN << "Join rpl sent to socket : " << user->get_fd() << std::endl;
#endif 
    return;
}

/**
 * @brief
 *
 * @param client
 * @param server
 * TODO: a revoir, tester
 */
void Commands::names(User *user, IRC *server)
{
    std::vector<std::string> params = user->get_params();
    std::vector<std::string> error;
    unsigned int size = params.size();
    if (size == 0)
    {
        error.push_back(user->get_command_name());
        return (return_error("461", user, server, error, NULL)); //NEED MORE PARAMS
    }
    get_channel_targets(user, server);
    if (channel)
    {
        #if MALATINI == 1 
            std::cout << YELLOW << "Success ! Names will send the names of the users in the channel." << NC << std::endl;
        #endif
        send_members_nick(user, channel, server);
    }
    //TODO: revoir les autres cas de NAMES si il ne s agit pas d'une CHANNEL
    else
    {
        /*
        #if MALATINI == 1
            std::cout << RED << "Error: the target channel seems to be wrong." << NC << std::endl;
        #endif
        std::string chan;
        if (size > 0)
            chan = params[0];
        */
        return ;
    }
    return;
}