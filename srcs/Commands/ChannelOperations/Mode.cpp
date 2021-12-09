#include <IRC.hpp>

void            Commands::mode(User *user, IRC *server)
{
    (void)user;
    (void)server;
    //Check du nombre d'arguments
    std::string modes;
    std::string channel;
    int param_size = user->get_params_size();
    std::vector<std::string> params;
    //Preparation du vecteur qui permet de gerer les erreurs
    std::vector<std::string> error;
    if (param_size < 2)
    {
        error.push_back(user->get_command_name());
        error_handler("461", user, NULL, error);
        return ;
    }
    //Verifier comment gerer plus de 2 arguments
    else
    {
        //On store la channel passee en parametre et les modes demandes
        channel = params[1];
        modes = params[2];
        //On check la channel (syntaxe)
        if (is_correct_channel_name(channel) == false)
        {
            error.push_back(channel);
            error_handler("403", user, NULL, error);
            return ;
        }
        //On check si la channel existe ?
        Channel *chan = NULL;
        if (server->has_channel(channel) == false)
        {
            //TODO: a tester
            return ;
        }
        chan = server->find_channel(channel);
        //On check si l'user est membre de la channel
        if (chan->user_is_member(user) == false)
        {
            error.push_back(user->get_nickname());
            error.push_back(channel);
            error_handler("441", user, NULL, error);
            return ;
        }
        //On doit checker les modes
        bool check = chan->check_channel_modes(modes);
        if (check == false)//ERR_UNKNOWN MODE
        {
            //Isoler le char qui n est pas reconnu
            std::string incorrect = chan->get_unknown_mode(channel);
            error.push_back(incorrect);
            error.push_back(channel);
            error_handler("472", user, chan, error);
        }
        std::string key = params[3];
        //et surtout qui va gerer ce qu il faut faire
        edit_modes(chan, user, modes, key, server);
    }
    return ;
}

//TODO: voir comment gerer le cas ou il n y aurait ni + ni -
bool            Commands::should_add_mode(std::string modes)
{
    //si on trouve un +, oui
    bool res = false;
    if (modes[0] == '+')
    {
        res = true;
    }
    return (res);   
}

bool            Commands::should_remove_mode(std::string modes)
{
    bool res = false;
    if (modes[0] == '-')
    {
        res = true;
    }
    return (res);
}

void            Commands::handle_key(Channel *channel, User *user, std::string modes, std::string key, bool add)
{
    (void)channel;
    (void)user;
    (void)modes;
    (void)add;
    if (add == true)
    {
       if (channel->get_has_key() == true)
       {
           //TODO: faire des tests pour voir s il faut quand meme renvoyer un message
            #if DEBUG
               std::cout << BLUE << "DEBUG: " << "MODE: key is already set." << std::endl;
           #endif
           return ;
       }
       if (!key.empty())
       {
           channel->set_has_key();
           channel->set_key(key);
       }
       else
       {
           #if DEBUG
               std::cout << BLUE << "DEBUG: " << "MODE: key argument is empty" << std::endl;
           #endif
           //TODO: faire des tests et voir comment gerer ce cas
           return ;
       }
        
    }
    else
    {
        if (channel->get_has_key() == false)
        {
            #if DEBUG
                std::cout << BLUE << "DEBUG: " << "MPDE: key is already unset." << std::endl;
            #endif
            return ;
        }
        else
        {
            channel->unset_has_key();
            channel->drop_key();
        }
        
    } 
    return ;
}

/**
 * @brief Il y a beaucoup de modes donc on va seulement implementer ceux utilises dans les commandes obligatoires
 * 
 * @param channel 
 * @param user 
 * @param modes 
 * @param server 
 * TODO: a tester
 */
void            Commands::edit_modes(Channel *channel, User *user, std::string modes, std::string key, IRC *server)
{
    (void)server;
    //faire une fonction qui permet de savoir si c est des plus ou des moins   
    bool add = should_add_mode(modes);
    bool remove = should_remove_mode(modes);
    if ((add && remove) || (!add && !remove))
    {
        #if DEBUG
            std::cout << BLUE << "DEBUG: " << "MODE: bad sign in command params." << std::endl;
        #endif
        return ;
    }
    //On verifie que modes ne fait pas plus de 4 char
    int len = modes.length();
    if (len > 4)
    {
        #if DEBUG
            std::cout << BLUE << "DEBUG: " << "MODE: too many chars in param." << std::endl;
        #endif
        return ;
    }
    //Pour l'instant on ne gere que le mode k
    int i = 0;
    if (i < len)
    {
        if (modes[i] == 'k')
        {
            handle_key(channel, user, modes, key, add);
        }
        i++;
    }
    //si je trouve un k je fais le necessaire pour l ajouter ou l enlever
    //TODO: verifier/faire la creation du message
}