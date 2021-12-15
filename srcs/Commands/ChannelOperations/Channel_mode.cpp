#include <IRC.hpp>

bool            Commands::should_remove_mode(std::string modes)
{
    bool res = false;
    if (modes[0] == '-')
        res = true;
    return (res);
}

//TODO: voir comment gerer le cas ou il n y aurait ni + ni - //par defaut irssi et hex considere un + si pas de signe :)
bool            Commands::should_add_mode(std::string modes)
{
    //si on trouve un +, oui
    bool res = false;
    if (modes[0] == '+')
        res = true;
    return (res);
}

//Fonction simplifiee Mahaut
char    Commands::get_mode_sign(std::string str, int pos)
{
    int i = pos;
    char c;
    int len = str.length();
    while (!isalpha(str[i]) && i < len)
    {
        c = str[i];
        i++;
    }
    return (c);
}

int     Commands::pos_next_mode(std::string str, int prev_pos)
{
    int pos = prev_pos;
    int len = str.length();
    while (!isalpha(str[pos] && pos < len))
    {
        pos++;
    }
    pos++;//posistion du mode et pas du sign
    if (pos >= len)
        pos = -1;
    return (pos);
}

/**
 * @brief exemple de test qui doivent marcher : /mode #channel +key secret
 * Dans mes tests sur free node je n ai pas reussi a unset une key (on me demandait toujours un mot de passe)
 * Par contre pour le mode t soit doit fonctionner correctement
 * Fonction pour les deux parties
 * 
 * @param user 
 * @param server 
 */
void Commands::mode_channel(User *user, IRC *server)
{
    std::string                 modes;
    std::string                 channel;
    int                         param_size = user->get_params_size();
    std::vector<std::string>    params = user->get_params();
    std::vector<std::string>    error;
    std::string                 key;

    if (param_size == 0)
    {
        #if DEBUG
            std::cout << "ERROR ! Param size is " << 0 << std::endl;
        #endif
        return ;
    }
    if (param_size < 2)
    {
        error.push_back(user->get_command_name());
        return (return_error("461", user, server, error, ""));
    }
    else
    {
        channel = params[0];
        modes = params[1];
        if (param_size > 2)
            key = params[2];
        if (is_correct_channel_name(channel) == false)
        {
            error.push_back(channel);
            return (return_error("403", user, server, error, ""));
        }
        Channel *chan = NULL;
        if (server->has_channel(channel) == false)
        {
            error.push_back(channel);
            return (return_error("403", user, server, error, ""));//NOSUCHCHANNEL
        }
        chan = server->find_channel(channel);
        //On check si l'user est membre de la channel
        if (chan->user_is_member(user) == false)
        {
            error.push_back(user->get_nickname());
            error.push_back(channel);
            return (return_error("441", user, server, error, ""));
        }
        //On doit checker les modes
        bool check = chan->check_channel_modes(modes);
        if (check == false)//ERR_UNKNOWN MODE
        {
            std::string incorrect = chan->get_unknown_mode(channel);
            error.push_back(incorrect);
            error.push_back(channel);
            return (return_error("472", user, server, error, ""));
        }
        std::string key = params[3];
        edit_modes(chan, user, modes, key, server);
    }
}

//Va permettre d'ajouter une cle
void            Commands::handle_key(Channel *channel, User *user, std::string modes, std::string key, bool add)
{
    (void)user;
    (void)modes;
    if (add == true)
    {
       if (channel->get_has_key() == true)
           return ;
       if (!key.empty())
       {
           channel->set_has_key();
           channel->set_key(key);
       }
       else
           return ;
    }
    else
    {
        if (channel->get_has_key() == false)
            return ;
        else
        {
            channel->unset_has_key();
            channel->drop_key();
        }
    }
    return ;
}

void            Commands::edit_modes(Channel *channel, User *user, std::string modes, std::string key, IRC *server)
{
    (void)server;

    //faire une fonction qui permet de savoir si c est des plus ou des moins
    bool add = should_add_mode(modes);
    bool remove = should_remove_mode(modes);
    if ((add && remove) || (!add && !remove))
        return ;
    int len = modes.length();
    int i = 0;
    char sign;
    char m = '\0';
    while (i != -1 && i < len)
    {
        sign = get_mode_sign(modes, i);
        #if DEBUG
            std::cout << GREEN << "Sign is " << sign << NC << std::endl;
        #endif   
        i = pos_next_mode(modes, i);
        if (i != -1)
        {
             m = modes[i];
            #if DEBUG
                std::cout << GREEN << "pos is is " << i << NC << std::endl;
                std::cout << PURPLE << "corresponging char is " << modes[i] << NC << std::endl;
            #endif 
            if (m == 'k' && sign == '+')
            {
                handle_key(channel, user, modes, key, add);
                //TODO: ajouter le message
            }
        }
    }
}