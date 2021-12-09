#include <IRC.hpp>

/**
 * @brief 
 * 
 * @param channel 
 * @param user 
 * @param server 
 * TODO: A tester
 */
void        Commands::send_names_message(Channel *channel, User *user, IRC *server)
{
    (void)server;
    if (channel)
        send_rpl("366", user, channel, "");//ENDOFNAMES
    else 
        send_rpl("366", user, NULL, channel->get_name());
    return ;
}

/**
 * @brief
 *
 * @param client
 * @param server
 * TODO: voir la notion de "nickname visibles"
 * Mahaut
 */
void		Commands::names(User *user, IRC *server)
{
    (void)user;
    (void)server;
    
    std::vector<std::string> params = user->get_params();
    std::vector<std::string> error;
    //Apres test via hexchat, ne pas prendre en compte des args sup a 1
    std::string channel;
    channel = params[1];
    Channel *chan = server->find_channel(channel);
    //On va juste retourner rpl mais pas d'erreur
    if (chan)
    {
        send_names_message(chan, user, server);
    }
    return ;
}