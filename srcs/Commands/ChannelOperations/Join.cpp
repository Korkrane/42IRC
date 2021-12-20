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
        chan->newOperator(user);
    //ne devrait pas arriver
    if (chan->is_channel_owner(user) == true && chan->user_is_member(user) == false)
        chan->newMember(user, false);
    return;
}

bool Commands::should_ignore_key(Channel *channel, std::vector<std::string> params)
{
    bool res = true;
    int size = params.size();
    if (size < 1)
        return (res); //Signifie qu'il n'y a pas de key
    bool has_key = channel->get_has_key();
    std::string key = channel->get_key();
    std::string candidate_key = params.front();
    if (has_key && key.compare(candidate_key) == 0)
        res = false;
    return (res);
}

void Commands::join(User *user, IRC *server)
{
    std::vector<std::string> params = user->get_params();
    std::vector<std::string> error;
    std::string channel;
    std::string opt_key = "";

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
        unsigned int index = 0;
        unsigned int comp = user->_splitted_args.size();
        while (index < max)
        {
            //on update nos variables
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
            //Cas ou on passe une cle en argument alors que le mode n est pas active
            if (should_ignore_key(chan, params) == true)
            {
                //Il y a une cle mais ce n est pas la bonne
                if (chan->is_correct_channel_key(opt_key) == false)
                {
                    error.push_back(channel);
                    return (return_error("475", user, server, error, ""));
                }
            }
            //on verifie si le user n'a pas atteint son quota max de channel
            if (server->user_can_join(chan) == true && !chan->user_is_member(user)) // || pas deja membre a ajouter
            {
                #if MALATINI
                    std::cout << BLUE << "The user is in " << user->get_channels_nb() <<"channels." << NC << std::endl;
                #endif
                //On verifie si le user ne listen pas deja sur trop de channels
                if (chan->get_members_nb() > CHAN_MAXCAPACITY - 1)
                    return (return_error("471", user, server, error, ""));
                //Erreur too many channels
                else if (user->get_channels_nb() > USER_MAXCHAN - 1)
                {
                    //TODO: the chan must be deleted if it has been created with this user
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
            index++;
        }
    }
    //Clean
    user->_splitted_args.clear();
    user->_splitted_channels.clear();
    //user->set_target_channel(NULL);
    return ;
}

void Commands::user_joins(User *user, IRC *server, Channel *chan, int index)
{
    (void)index;
    user->set_target_channel(chan);

#if MALATINI
    std::cout << BLUE << "user_joins called" << NC << std::endl;
#endif
    //si oui, rajouter au channel
    user->be_added_to_channel(chan);

    //On l'ajoute a sa liste
    user->add_channel_to_list(chan);

    //Verification de la coherence des roles
    check_roles(chan, user, true);

    //On prepare et envoie la reponse du serveur
    //std::vector<std::string> chan_vec;
    //chan_vec.push_back(user->_splitted_channels[index]);
    std::vector<User *> users = chan->get_members();
    //users.push_back(user);
#if MALATINI ==  1
    std::cout << BLUE << "send_rpl_to_all_members called" << NC << std::endl;
#endif
    std::string rpl = ":" + user->get_nickname() + "!" + user->get_username() + "@0 JOIN " + chan->get_name() + "\r\n";
    std::vector<User *>::iterator it = users.begin();
    std::vector<User *>::iterator ite = users.end();
    while (it != ite)
    {
        server->_response_queue.push_back(std::make_pair((*it)->get_fd(), rpl));
        it++;
    }
    //server->send_rpl_to_all_members("", users, chan_vec, "JOIN"); //user->_splitted_channels
    //chan_vec.clear();

    names(user, server);
    //Equivalent NAMES (comme si on avait passe la channel en parametre)
    /*
    user->set_target_channel(chan);
    std::string success_rpl_1;
    success_rpl_1 = ":127.0.0.1 353 " + user->get_nickname() + " = " + chan->get_name() + " :";
    //On va d'abord afficher l'operateur
    User *op = chan->get_operators().front();
    success_rpl_1 += "@";
    std::string operator_name = op->get_nickname();
    success_rpl_1 += operator_name + " ";

    //On fera probablement le tour de tous les users ?
    if (user != op)
        success_rpl_1 += user->get_nickname();
    success_rpl_1 += "\r\n";
    names(user, server);
    server->send_rpl("366", user, user->get_params(), "");//ENDOFNAMES 
    //352 WHO - appelee par le client 
    user->set_target_channel(NULL);//On remet la target channel a null pour que ce soit bien propre
    */
}

//Trash pour join mais names devrait fonctionner comme ca de toute facon
void    Commands::trash_names(User *user, IRC *server)
{
    (void)user;
    (void)server;
    return ;
}