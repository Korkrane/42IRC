#include <IRC.hpp>

/*
void Commands::send_join_message(Channel *channel, User *user, std::vector<std::string> message, IRC *server)
{
    (void)message;
    std::string rpl = server->init_rpl(user);
    rpl += " JOIN " + channel->get_name();
    rpl += "\r\n";
    //Envoyer le message a tout le channel
    server->send_rpl_to_all_members(channel, rpl);
    //Envoyer le message concernant le topic (voir RFC2812)
    if (channel->get_has_topic() == true)
        server->send_rpl("332", user, channel, "");
    server->send_rpl("353", user, channel, "");
    server->send_rpl("366", user, channel, "");
    return ;
}
*/

/**
 * @brief Permet de savoir si les arguments qui representeraient la key doivent etre pris en compte ou non.
 *
 * @param channel
 * @param params
 * @return true
 * @return false
 */
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

/**
 * @brief
 *
 * @param command
 * @param client
 * @param server
 * Mahaut
 * 1ere fonction de la liste des Channel Operations dans la rfc
 * TODO: a retester
 */

void Commands::join(User *user, IRC *server)
{
    std::vector<std::string> params = user->get_params();
    std::vector<std::string> error;
#if DEBUG
    std::cout << RED << "ENTER JOIN CMD" << NC << std::endl;
#endif

    if (user->get_params_size() < 1)
    {
        //TODO: build reply
        /*
        error.push_back(user->get_command_name());
        error_handler("461", user, NULL, error);
        */
        return;
    }
    //Dans nos tests via hexchat seuls 2 params sont pris en compte (1 channel et 2 key)
    if (user->get_params_size() == 1)
    {
        std::string channel = user->get_params().front();
        std::string opt_key = user->get_params().back();

        //On verifie si l'argument channel est correct
        if (is_correct_channel_name(channel) == false)
        {
            //TODO: build reply
            /*
            error.push_back(channel);
            error_handler("403", user, NULL, error);
            */
            return;
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
                //TODO: build reply
                /*
                error.push_back(channel);
                error_handler("471", user, chan, error);
                */
                return;
            }
        }
        //TODO: voir s il y a d autres cas d'erreur possible ?
        if (should_ignore_key(chan, params) == true)
        {
            if (chan->is_correct_channel_key(opt_key) == false)
            {
                //TODO : build reply
                /*
                error.push_back(channel);
                error_handler("475", user, NULL, error);
                */
                return;
            }
        }
        //on verifie si le user n'a pas atteint son quota max de channel
        if (server->user_can_join(chan) == true && !chan->user_is_member(user)) // || pas deja membre a ajouter
        {
            //On verifie si le user ne listen pas deja sur trop de channels
            if (chan->get_members_nb() >= CHAN_MAXCAPACITY)
            {
                //TODO: build reply
                /*
                error.push_back(channel);
                error_handler("471", user, NULL, error);
                */
                return;
            }
            //si oui, rajouter au channel
            user->be_added_to_channel(chan);
            //On l'ajoute a sa liste
            user->add_channel_to_list(chan);
            //On prepare et envoie la reponse du serveur
            //TODO: ajouter appel au nouveau build_reply
            //send_join_message(chan, user, user->get_params(), server);
        }
        //Erreur to many channels car l user fait partie de trop de channels
        else
        {
            //TODO: build reply
            /*
            error.push_back(channel);
            error_handler("405", user, NULL, error);
            */
            return;
        }
    }
#if DEBUG
    std::cout << RED << "EXIT JOIN CMD" << NC << std::endl;
#endif
}