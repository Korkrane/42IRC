#include <IRC.hpp>

/**
 * @brief Permet de verifier et/ou rectifier la coherence du role d'un user
 *
 * @param chan
 * @param user
 * @param added
 */
void Commands::check_roles(Channel *chan, User *user, bool added)
{
    (void)added;
    if (chan->is_channel_owner(user) == true && chan->user_is_operator(user) == false)
        chan->new_operator(user);
    if (chan->is_channel_owner(user) == true && chan->user_is_member(user) == false)
        chan->new_member(user, false);
    return;
}

void Commands::loop_join(User *user, IRC *server, unsigned int index)
{
    std::string channel;
    std::string opt_key = "";
    std::vector<std::string> params = user->get_params();
    std::vector<std::string> error;
    unsigned int comp = user->_splitted_args.size();

    channel = user->_splitted_channels[index];
    //Si l'element dans le vecteur a cette position n est pas nul
    if (!user->_splitted_channels.empty() && index < comp && !user->_splitted_channels[index].empty())
        opt_key = user->_splitted_args[index];

    //On verifie que le parametre peut correspondre a un nom de channel valide
    if (!channel.empty() && is_correct_channel_name(channel) == false)
    {
#if MALATINI == 1
        std::cout << RED << "Error : JOIN: Invalid channel name" NC << std::endl;
#endif
        error.push_back(channel);
        return (return_error("403", user, server, error, ""));
    }

    //On verifie si la channel existe, sinon on va la creer (par defaut il n y a pas de cle quand on la cree)
    Channel *chan = NULL;
    user->set_target_channel(chan);
    if (!channel.empty() && server->has_channel(channel) == false)
        chan = server->add_channel(channel, user);
    else if (!channel.empty())
    {
        //Fonction qui permet de recuperer le pointeur de la channel correspondante
        chan = server->find_channel(channel);
        //On verifie si la channel n est pas full
        if (chan->is_full_channel() == true)
        {
            error.push_back(channel);
            return (return_error("471", user, server, error, ""));
        }
    }
    //si il y devrait y avoir une cle mais que le nombre d args n est pas bons
    int size = params.size();
#if MALATINI
    std::cout << "JOIN : size is " << size << " and has key  is : " << chan->get_has_key() << BLUE << NC << std::endl;
#endif
    if (size < 2 && chan->get_has_key() == true)
    {
        error.push_back(channel);
        return (return_error("475", user, server, error, ""));
    }
    std::string key = "";
    std::string real_key = "";
    if (size >= 2)
        key = params[1];
    if (chan->get_has_key() == true)
    {
        real_key = chan->get_key();
    }
#if MALATINI == 1
    std::cout << GREEN << "Real key : " << real_key << " and key is " << key << NC << std::endl;
#endif
    if (!key.empty() && !real_key.empty() && real_key.compare(key) != 0)//Ssi je dois avoir une key et que ce n est pas la bonne
    {
#if MALATINI == 1
        std::cout << BLUE << "JOIN : We should check the key." << NC << std::endl;
        error.push_back(channel);
        return (return_error("475", user, server, error, ""));
#endif
    }
    else
    {
#if MALATINI == 1
        std::cout << BLUE << "JOIN : The ignore key return true" << NC << std::endl;
#endif
        ;
    }

    //on verifie si le user n'a pas atteint son quota max de channel
    if (server->user_can_join(chan) == true && !chan->user_is_member(user)) // || pas deja membre a ajouter
    {
#if MALATINI
        std::cout << BLUE << "The user is in " << user->get_channels_nb() << "channels." << NC << std::endl;
#endif
        //On verifie si le user ne listen pas deja sur trop de channels
        if (chan->get_members_nb() > CHAN_MAXCAPACITY - 1)
        {
            error.push_back(channel);
            user->set_target_channel(NULL);
            return (return_error("471", user, server, error, ""));
        }
        //Erreur too many channels
        else if (user->get_channels_nb() > USER_MAXCHAN - 1)
        {
            error.push_back(channel);
            user->set_target_channel(NULL);
            return (return_error("405", user, server, error, ""));
        }
        //chan = server->find_channel(channel);
        user->set_target_channel(chan);
        user_joins(user, server, chan, index);
    }
    //Erreur to many channels car l user fait partie de trop de channels
    else
    {
        error.push_back(channel);
        return (return_error("405", user, server, error, ""));
    }
#if MALATINI == 1
    std::cout << BLUE << "Index is " << index << NC << std::endl;
#endif
}

/* 
bool Commands::should_ignore_key(Channel *channel, std::vector<std::string> params)
{
    if (params.size() < 1)
        return (true); //Signifie qu'il n'y a pas de key

    std::string key = channel->get_key();
    std::string candidate_key = params.front();

    if (channel->get_has_key() && key.compare(candidate_key) == 0)
        return (false);
    return (true);
}
*/

void Commands::join(User *user, IRC *server)
{
    std::vector<std::string> error;

    //Va permettre de gerer le cas ou il y a plusieurs channels
    get_channel_targets(user, server);
    get_key_targets(user, server);

    //Si il n'y a pas de param
    if (user->get_params_size() < 1)
    {
        error.push_back(user->get_command_name());
        return (return_error("461", user, server, error, ""));
    }
    else
    {
        unsigned int max = user->_splitted_channels.size();
        unsigned int i = 0;
        // unsigned int comp = user->_splitted_args.size();
        while (i < max)
        {
            //on update nos variables
            loop_join(user, server, i);
            i++;
            user->set_display_who(true);
            who(user, server);
        }
    }
    //Clean
    user->_splitted_args.clear();
    user->_splitted_channels.clear();
    return;
}

void Commands::user_joins(User *user, IRC *server, Channel *chan, int index)
{
    (void)index;
    user->set_target_channel(chan);
    std::string topic = "";

    if (chan->get_has_topic() == true)
    {
        topic = ":127.0.0.1 332 " + user->get_nickname() + " " + chan->get_name() + " ";
        topic += chan->get_topic();
        topic += "\r\n";
#if MALATINI == 1
        std::cout << GREEN << "topic is : " << NC << std::endl;
        std::cout << GREEN << topic << NC << std::endl;
#endif
        //server->_response_queue.push_back(std::make_pair(user->get_fd(), topic));
    }

#if MALATINI
    std::cout << BLUE << "user_joins called" << NC << std::endl;
#endif
    //si oui, rajouter au channel
    user->be_added_to_channel(chan);

    //On l'ajoute a sa liste
    user->add_channel_to_list(chan);

    //Verification de la coherence des roles
    check_roles(chan, user, true);

    //Faire une sous fonction speciale ou remettre dans le send rpl
    std::vector<User *> users = chan->get_members();
#if MALATINI == 1
    std::cout << BLUE << "send_rpl_to_all_members called" << NC << std::endl;
#endif
    std::string rpl = ":" + user->get_nickname() + "!" + user->get_username() + "@0 JOIN " + chan->get_name() + "\r\n";
    std::vector<User *>::iterator it = users.begin();
    std::vector<User *>::iterator ite = users.end();
    while (it != ite)
    {
        server->_response_queue.push_back(std::make_pair((*it)->get_fd(), rpl));
        if ((*it)->get_nickname() == user->get_nickname())
        {
            server->_response_queue.push_back(std::make_pair((*it)->get_fd(), topic));
        }
        it++;
    }
    names(user, server);
}