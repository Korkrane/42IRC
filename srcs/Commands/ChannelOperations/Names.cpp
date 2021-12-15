#include <IRC.hpp>


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
    #if DEBUG
        std::cout << GREEN << "Here we go!" << std::endl;
    #endif
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
            #if DEBUG
                std::cout << BLUE << "Names found channel. " << chan->get_name() << std::endl;
            #endif
            server->send_rpl("366", user, params, "");
        }
        else
        {
            #if DEBUG
                std::cout << BLUE << "Names did not found" << chan->get_name() << std::endl;
            #endif
            //server->send_rpl("366", user, params, (*it));//End of names
        }
            
        #if DEBUG
             std::cout << "Successfull command names." << std::endl;
        #endif
        pos++;
        it++;
    }
    user->_splitted_channels.clear();
    return;
}