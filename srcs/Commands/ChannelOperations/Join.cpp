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
    std::vector<std::string> params = user->get_params();
    std::vector<std::string> error;
    #if DEBUG
        std::cout << PURPLE << "Join command called" << std::endl;
    #endif

    #if DEBUG
        user->display_params();
    #endif
    //Check nombre de params
    if (user->get_params_size() < 1)
    {
        error.push_back(user->get_command_name());
        server->send_rpl("461", user, error, "");
        return ;
    }
    /*
    else
    {
        //TODO: pas bon, a modifier
        //On utilise des vecteurs car il peut y avoir plusieurs target
        //std::vector<std::string> channel = user->get_params().front();
        //std::vector<std::string> opt_key = user->get_params().back();

        if (is_correct_channel_name(channel) == false)
        {
            error.push_back(channel);
            return (server->send_rpl("403", user, error, ""));
        }
        //On verifie si la channel existe, sinon on va la creer
        Channel *chan = NULL;
        if (server->has_channel(channel) == false)
            chan = server->add_channel(channel, opt_key, user);
        else
        {
            //Fonction qui permet de recuperer le pointeur de la channel correspondante
            chan = server->find_channel(channel);
            //On verifie si la channel n est pas full
            if (chan->is_full_channel() == true)
            {
                error.push_back(channel);
                return (server->send_rpl("471", user, error, ""));
            }
        }
        //Cas ou on passe une cle en argument alors que le mode n est pas active
        if (should_ignore_key(chan, params) == true)
        {
            if (chan->is_correct_channel_key(opt_key) == false)
            {
                error.push_back(channel);
                return (server->send_rpl("475", user, error, ""));
            }
        }
        //on verifie si le user n'a pas atteint son quota max de channel
        if (server->user_can_join(chan) == true && !chan->user_is_member(user)) // || pas deja membre a ajouter
        {
            //On verifie si le user ne listen pas deja sur trop de channels
            if (chan->get_members_nb() >= CHAN_MAXCAPACITY)
                return (server->send_rpl("471", user, params, ""));
            //si oui, rajouter au channel
            user->be_added_to_channel(chan);
            //On l'ajoute a sa liste
            user->add_channel_to_list(chan);
            //On prepare et envoie la reponse du serveur
            server->send_rpl_to_all_members("", chan->get_members(), params, "JOIN");
        }
        //Erreur to many channels car l user fait partie de trop de channels
        else
        {
            error.push_back(channel);
            return (server->send_rpl("405", user, error, ""));
        }
    }
    */
    return ;
}