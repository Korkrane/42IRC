#include <IRC.hpp>

void    Commands::check_roles(Channel *chan, User *user, bool added)
{
    (void)chan;
    (void)user;
    (void)added;

    if (chan->is_channel_owner(user) == true && chan->user_is_operator(user) == false)
    {
        chan->newOperator(user);
    }
    //ne devrait pas arriver
    if (chan->is_channel_owner(user) == true && chan->user_is_member(user) == false)
    {
        chan->newMember(user, false);
    }
    return ;
}

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

//TODO: faire des sous fonctions pour nettoyer
void Commands::join(User *user, IRC *server)
{
    std::vector<std::string>    params = user->get_params();
    std::vector<std::string>    error;
    std::string                 channel;
    std::string                 opt_key;

    //Va permettre de gerer le cas ou il y a plusieurs channels
    get_channel_targets(user, server);
    get_key_targets(user, server);

    #if DEBUG
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
        user->_splitted_args.clear();
        user->_splitted_channels.clear();
        return ;
    }
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
                user->_splitted_args.clear();
                user->_splitted_channels.clear();
                return ;
            }
            //On verifie si la channel existe, sinon on va la creer (par defaut il n y a pas de cle quand on la cree)
            Channel *chan = NULL;
            if (!channel.empty() && server->has_channel(channel) == false)
            {
                chan = server->add_channel(channel, user);
                //chan = server->get_channels().back();
            }
            //chan->displayChannelInfo();
            else if (!channel.empty())
            {
                //Fonction qui permet de recuperer le pointeur de la channel correspondante
                chan = server->find_channel(channel);
                //On verifie si la channel n est pas full
                if (chan->is_full_channel() == true)
                {
                    #if DEBUG
                        chan->displayChannelInfo();
                    #endif
                    error.push_back(channel);
                    server->send_rpl("471", user, error, "");
                    user->_splitted_args.clear();
                    user->_splitted_channels.clear();
                    return ;
                }
            }
            //Cas ou on passe une cle en argument alors que le mode n est pas active
            if (should_ignore_key(chan, params) == true)
            {
                #if DEBUG
                    std::cout << BLUE << "Even if there is a key mentionend we should ignored it" << NC << std::endl;
                #endif
                //TODO: a replacer ca ailleurs ?
                if (chan->is_correct_channel_key(opt_key) == false)
                {
                    #if DEBUG
                        chan->displayChannelInfo();
                    #endif
                    error.push_back(channel);
                    server->send_rpl("475", user, error, "");
                    user->_splitted_args.clear();
                    user->_splitted_channels.clear();
                    return ;
                }
            }
            //on verifie si le user n'a pas atteint son quota max de channel
            if (server->user_can_join(chan) == true && !chan->user_is_member(user)) // || pas deja membre a ajouter
            {
                //On verifie si le user ne listen pas deja sur trop de channels
                if (chan->get_members_nb() >= CHAN_MAXCAPACITY)
                {
                    #if DEBUG
                        chan->displayChannelInfo();
                    #endif
                    server->send_rpl("471", user, params, "");
                    user->_splitted_args.clear();
                    user->_splitted_channels.clear();
                    return ;
                }
                //Erreur too many channels
                else if (user->get_channels_nb() >= USER_MAXCHAN)
                {
                    #if DEBUG
                        chan->displayChannelInfo();
                    #endif
                    server->send_rpl("405", user, params, "");
                    user->_splitted_args.clear();
                    user->_splitted_channels.clear();
                    return ;
                }
                //si oui, rajouter au channel
                user->be_added_to_channel(chan);
                //On l'ajoute a sa liste
                user->add_channel_to_list(chan);
                check_roles(chan, user, true);
                //On prepare et envoie la reponse du serveur
                std::vector<std::string> chan_vec;
                chan_vec.push_back(user->_splitted_channels[index]);
                server->send_rpl_to_all_members("", chan->get_members(), chan_vec, "JOIN");//user->_splitted_channels
                 #if DEBUG
                    std::cout << PURPLE << "DEBUG: JOIN: " << "Success params !" << NC << std::endl;
                    chan->displayChannelInfo();
                #endif
                chan_vec.clear();
                //TODO: a rajouter topic
                //server->send_rpl("", user, error, "TOPIC");
                //TODO: a rajouer names
                //server->send_rpl("", user, error, "NAMES");
            }
            //Erreur to many channels car l user fait partie de trop de channels
            else
            {
                error.push_back(channel);
                server->send_rpl("405", user, error, "");
                user->_splitted_args.clear();
                user->_splitted_channels.clear();
                return ;
            }
            #if DEBUG
                std::cout << "index is " << index << NC << std::endl;
            #endif
            index++;
        }
    }
    user->_splitted_args.clear();
    user->_splitted_channels.clear();
    return ;
}