#include <IRC.hpp>

//TODO: a revoir
bool Commands::should_ignore_key(Channel *channel, std::vector<std::string> params)
{
    bool res = true;
    int size = params.size();
    if (size < 1)
        return (res);//Signifie qu'il n'y a pas de key
    bool has_key = channel->get_has_key();
    std::string key = channel->get_key();
    std::string candidate_key = params.front();
    if (key.compare(candidate_key) == false)//The keys are the same
        res = false;
    #if DEBUG
        if ((!has_key && !key.empty()) || (has_key && key.empty()))
            std::cout << "DEBUG: " << "CHANNEL :" << "There are some incompatible values regarding key members." << std::endl;
    #endif
    return (res);
}

void Commands::join(User *user, IRC *server)
{
    std::vector<std::string>    params = user->get_params();
    std::vector<std::string>    error;
    std::string                 channel;
    std::string                 opt_key;

    //Check nombre de params
    //std::vector<std::string> target_channel
    get_channel_targets(user, server);
    get_key_targets(user, server);

    #if DEBUG
        //TODO: a mettre en prive
        std::cout << "PRINTING SPLITTED CHANNELS" << std::endl;
        display_vector_string(user->_splitted_channels);
        std::cout << "PRINTING SPLITTED ARGS" << std::endl;
        display_vector_string(user->_splitted_args);
        std::cout << NC << std::endl;
    #endif        
    if (user->get_params_size() < 1)
    {
        error.push_back(user->get_command_name());
        server->send_rpl("461", user, error, "");
        return ;
    }
    /* */
    else
    {
        unsigned int max = user->_splitted_channels.size();
        unsigned int index = 0;
        unsigned int comp = user->_splitted_args.size();
        //unsigned int in = 0;
        while (index < max)
        {
            //on update nos variables
            channel = user->_splitted_channels[index];
            //Si l'element dans le vecteur a cette position n est pas nul
            if (!user->_splitted_channels.empty() && index < comp && !user->_splitted_channels[index].empty())
                opt_key = user->_splitted_args[index];
            else
                opt_key = "";

            #if DEBUG
                std::cout << BLUE << "channel " << channel << std::endl;
                std::cout << BLUE << "opt key " << opt_key << std::endl;
            #endif
            //On verifie que le parametre peut correspondre a un nom de channel valide
            if (!channel.empty() && is_correct_channel_name(channel) == false)
            {
                error.push_back(channel);
                server->send_rpl("403", user, error, "");
                return ;
            }
            //On verifie si la channel existe, sinon on va la creer (par defaut il n y a pas de cle quand on la cree)
            Channel *chan = NULL;
            if (!channel.empty() && server->has_channel(channel) == false)
            {
                chan = server->add_channel(channel, user);
                //std::cout << "ICI" << std::endl;
                chan = server->get_channels().back();
            }
            /*
            else if (!channel.empty())
            {
                //Fonction qui permet de recuperer le pointeur de la channel correspondante
                chan = server->find_channel(channel);
                //On verifie si la channel n est pas full
                if (chan->is_full_channel() == true)
                {
                    error.push_back(channel);
                    server->send_rpl("471", user, error, "");
                    return ;
                }
            }
            //Cas ou on passe une cle en argument alors que le mode n est pas active
            if (should_ignore_key(chan, params) == true)
            {
                if (chan->is_correct_channel_key(opt_key) == false)
                {
                    error.push_back(channel);
                    server->send_rpl("475", user, error, "");
                    return ;
                }
            }
            //on verifie si le user n'a pas atteint son quota max de channel
            if (server->user_can_join(chan) == true && !chan->user_is_member(user)) // || pas deja membre a ajouter
            {
                //On verifie si le user ne listen pas deja sur trop de channels
                if (chan->get_members_nb() >= CHAN_MAXCAPACITY)
                {
                    server->send_rpl("471", user, params, "");
                    return ;
                }
                //si oui, rajouter au channel
                user->be_added_to_channel(chan);
                //On l'ajoute a sa liste
                user->add_channel_to_list(chan);
                //On prepare et envoie la reponse du serveur
                #if DEBUG
                    std::cout << PURPLE << "DEBUG: JOIN: " << "Success params !" << std::endl;
                #endif
                server->send_rpl_to_all_members("", chan->get_members(), params, "JOIN");
            }
            //Erreur to many channels car l user fait partie de trop de channels
            else
            {
                error.push_back(channel);
                server->send_rpl("405", user, error, "");
                return ;
            }
            */
            index++;
        }
    }
    //delete target_channel;
    //delete target_key;
    return ;
}