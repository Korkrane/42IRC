#include <IRC.hpp>

/**
 * @brief exemple de test qui doivent marcher : /mode #channel +key secret
 * Dans mes tests sur free node je n ai pas reussi a unset une key (on me demandait toujours un mot de passe)
 * Par contre pour le mode t soit doit fonctionner correctement
 * 
 * @param user 
 * @param server 
 */
void Commands::mode_channel(User *user, IRC *server)
{
    std::string                 modes;
    std::string                 channel;
    int                         param_size = user->get_params_size();
    std::vector<std::string>    params;
    std::vector<std::string>    error;
    std::string                 key;

    if (param_size < 2)
    {
        error.push_back(user->get_command_name());
        return (return_error("461", user, server, error, ""));
    }

    else
    {
        //On store la channel passee en parametre et les modes demandes
        channel = params[0];
        modes = params[1];
        if (param_size > 2)
            key = params[2];

        //On veut gerer +t, -t, +k key
        //On check la channel (syntaxe)
        if (is_correct_channel_name(channel) == false)
        {
            //TODO: appel build reply
            /*
            error.push_back(channel);
            error_handler("403", user, NULL, error);
            */
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
            //TODO: appel build reply
            /*
            error.push_back(user->get_nickname());
            error.push_back(channel);
            error_handler("441", user, NULL, error);
            */
            return ;
        }
        //On doit checker les modes
        bool check = chan->check_channel_modes(modes);
        if (check == false)//ERR_UNKNOWN MODE
        {
            //TODO: appel build reply
            //Isoler le char qui n est pas reconnu
            /*
            std::string incorrect = chan->get_unknown_mode(channel);
            error.push_back(incorrect);
            error.push_back(channel);
            error_handler("472", user, chan, error);
            */
            return ;
           ;
        }
        std::string key = params[3];
        //et surtout qui va gerer ce qu il faut faire
        edit_modes(chan, user, modes, key, server);
    }
}

//TODO to complete based on what mode we are implementing
void Commands::modif_user(User *user, IRC *server, std::string modifications)
{
    (void)server;
    bool sign;
    for (std::string::iterator it = modifications.begin(); it != modifications.end(); it++)
    {
        switch ((*it))
        {
            case '+':
            {
                sign = true;
                continue ;
            }
            case '-':
            {
                sign = false;
                continue ;
            }
            case 'a':
            {
                (sign == true) ? user->set_is_away(true) : user->set_is_away(false);
                std::cout << "after mode affect a user away ? " << user->user_is_away() << std::endl;
                continue ;
            }
            case 'i':
                continue ;
            case 'w':
                continue ;
            case 'r':
                continue ;
            case 'o':
                continue ;
            case 'O':
                continue ;
            case 's':
                continue ;
            default:
                continue ;
        }
    }
}

void            Commands::mode_user(User *user, IRC *server)
{
    int param_size = user->get_params_size();
    std::vector<std::string> params = user->get_params();
    std::vector<std::string> reply_params;
    if(param_size == 0)
    {
        server->send_rpl("461", user, reply_params, ""); //ERR_NEEDMOREPARAMS
        return;
    }
    else if (param_size == 1) //SI JUSTE LA TARGET
    {
        if(server->find_user(params[0]))
        {
            if(user->get_nickname() == params[0])
            {
                reply_params.push_back(user->get_modes());
                server->send_rpl("221", user, reply_params, ""); //RPL_UMODEIS
            }
            else
                server->send_rpl("502", user, reply_params, ""); //ERR_USERDONTMATCH
        }
        else
        {
            reply_params.push_back(params[0]);
            server->send_rpl("401", user, reply_params, ""); //ERR_NO_SUCHNICK
        }
        return ;
    }
    else if(param_size == 2) //SI TARGET + MODES TO CHANGE
    {
        #if DEBUG
            std::cout << PURPLE << "DEBUG: MODE has user target and mode to change" << NC << std::endl;
        #endif
        if(user->get_nickname() == params[0])
        {
            bool has_unknown_mode = false;
            bool sign = true;
            std::string modes(USER_VALID_MODES);
            std::string modes_changed;
            for(std::string::iterator it = params[1].begin(); it != params[1].end(); it++)
            {
                if((*it) == '-')
                {
                    sign = false;
                    modes_changed.push_back((*it));
                    continue ;
                }
                else if((*it) == '+')
                {
                    sign = true;
                    modes_changed.push_back((*it));
                    continue ;
                }
                //std::cout << "value tested: " << (*it) << std::endl;
                if(modes.find((*it)) != std::string::npos)
                {
                    std::string user_modes = user->get_modes();
                    if(sign == true && (user_modes.find((*it)) == std::string::npos)) //add mode to user
                    {
                        //std::cout << "add mode" << std::endl;
                        modes_changed.push_back((*it));
                        user->set_modes(user->get_modes() + (*it));
                    }
                    else if(sign == false && (user_modes.find((*it)) != std::string::npos)) //remove mode to user
                    {
                        //std::cout << "remove mode" << std::endl;
                        modes_changed.push_back((*it));
                        user_modes.erase(std::remove(user_modes.begin(), user_modes.end(), (*it)), user_modes.end());
                        user->set_modes(user_modes);
                    }
                }
                else
                    has_unknown_mode = true;
            }
            if(has_unknown_mode)
            {
                server->send_rpl("501", user, reply_params, "");
                reply_params.clear();
            }
            //here need to format string replied for reply -+i+
            std::string format_modes_params;
            std::cout << "modes_changed before put it in format_modes:" << modes_changed << std::endl;
            for(std::string::iterator it = modes_changed.begin(); it != modes_changed.end(); it++)
            {
                if(format_modes_params.empty() && ((*it) != '-' && (*it) != '+'))
                    format_modes_params.push_back('+');
                if((*it) != '+' && (*it) != '-')
                {
                    format_modes_params.push_back((*it));
                    continue ;
                }
                if(((*it) == '+' || (*it) == '-') && (*(it+1) != '+' && *(it+1) != '-' && (it+1) != modes_changed.end()))
                        format_modes_params.push_back((*it));
            }
            std::cout << "after patching reply format:" << format_modes_params << std::endl;
            if(!format_modes_params.empty())
            {
                reply_params.push_back(format_modes_params);
                server->send_rpl("1005", user, reply_params, "MODE_USER");
                modif_user(user, server, format_modes_params);
            }
        }
        else
            server->send_rpl("502", user, reply_params, ""); //ERR_USERDONTMATCH
    }
}

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
        return ;
    }
    else
    {
        //Baudoin: autre cas possible ou pas?
        return ;
    }
    #if DEBUG
        std::cout << RED << "EXIT MODE COMMAND" << NC << std::endl;
    #endif
}

//TODO: voir comment gerer le cas ou il n y aurait ni + ni - //par defaut irssi et hex considere un + si pas de signe :)
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