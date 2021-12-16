#include <IRC.hpp>

//TODO: A remettre dans build_rpl ?
void    Commands::send_members_nick(User *user, Channel *channel, IRC *server)
{
    (void)user;
    (void)server;

    std::vector<User *> members = channel->get_members();
    std::vector<User *>::iterator it = members.begin();
    std::vector<User *>::iterator ite = members.end();

    std::string rpl;

    rpl = ":127.0.0.1 353 " + user->get_nickname();
    rpl += " = " + channel->get_name() + " :";
    while (it != ite)
    {
        if (channel->user_is_operator(*it) == true)
        {
            rpl += "@";
        }
        rpl += (*it)->get_nickname() + " ";
        it++;
    }
    rpl += "\r\n";
    #if MALATINI == 1
        std::cout << GREEN << "response will be : " << rpl << std::endl;
    #endif
    server->_response_queue.push_back(std::make_pair(user->get_socket(), rpl));
    return;
}

/**
 * @brief
 *
 * @param client
 * @param server
 */
void Commands::names(User *user, IRC *server)
{
    std::vector<std::string>    params = user->get_params();
    std::vector<std::string>    error;
    unsigned int                size = params.size();
    std::string                 channel;

    if (size > 0)
        channel = params[0];
    else 
    {
        error.push_back(user->get_command_name());
        return (return_error("461", user, server, error, NULL));//NEED MORE PARAMS
    }
    Channel *chan = NULL;
    //On va juste retourner rpl mais pas d'erreur
    get_channel_targets(user, server);
    std::vector<std::string>::iterator it = user->_splitted_channels.begin();
    std::vector<std::string>::iterator ite  = user->_splitted_channels.end();
    int pos = 0;
    while (it != ite)
    {
        chan = server->find_channel((*it));
        if (chan)
        {
                send_members_nick(user, chan, server);
                server->send_rpl("366", user, params, "");
        }
        else
        {
            //server->send_rpl("366", user, params, (*it));//End of names
            ;
        }
        pos++;
        it++;
    }
    user->_splitted_channels.clear();
    return;
}