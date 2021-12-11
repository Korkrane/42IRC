#include <IRC.hpp>

void Commands::send_join_message(Channel *channel, User *user, std::vector<std::string> message, IRC *server)
{
    (void)message;
    std::string rpl = server->init_rpl(user);
    rpl += " JOIN " + channel->get_name();
    rpl += "\r\n";
    //Envoyer le message a tout le channel
    server->send_rpl_to_all_members(channel, rpl);
    //Envoyer le message concernant le topic
    if (channel->get_has_topic() == true)
    {
        server->send_rpl("332", user, channel, "");
    }
    server->send_rpl("353", user, channel, "");
    server->send_rpl("366", user, channel, "");
    return;
}

/**
 * @brief
 *
 * @param command
 * @param client
 * @param server
 * Mahaut
 * 1ere fonction de la liste des Channel Operations dans la rfc
 * TODO: a tester
 */

void Commands::join(User *user, IRC *server)
{
    std::vector<std::string> error;
#if DEBUG
    std::cout << RED << "ENTER JOIN CMD" << NC << std::endl;
#endif

    //On verifie le nombre minimum de param
    //TODO: revoir si mon get params est d'actualite ou si le resultat du parsing est ailleurs
    if (user->get_params_size() < 1)
    {
        error.push_back(user->get_command_name());
        error_handler("461", user, NULL, error);
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
            error.push_back(channel);
            error_handler("403", user, NULL, error);
            return;
        }
        //On verifie si la channel existe, sinon on va la creer
        Channel *chan = NULL;
        if (server->has_channel(channel) == false)
            chan = server->add_channel(channel, opt_key);
        else
        {
            std::cout << "ICI" << std::endl;
            //Fonction qui permet de recuperer le pointeur de la channel correspondante
            chan = server->find_channel(channel);
            //On verifie si la channel n est pas full
            if (chan->is_full_channel() == true)
            {
                error.push_back(channel);
                error_handler("471", user, chan, error);
                return;
            }
        }
        if (chan->is_correct_channel_key(opt_key) == false)
        {
            error.push_back(channel);
            error_handler("475", user, NULL, error);
            return;
        }
        //on verifie si le user n'a pas atteint son quota max de channel
        //if (user->can_join() == true)
        if (server->user_can_join(chan) == true && !chan->user_is_member(user)) // || pas deja membre a ajouter
        {
            //On verifie si le user ne listen pas deja sur trop de channels
            if (chan->get_members_nb() >= CHAN_MAXCAPACITY)
            {
                error.push_back(channel);
                error_handler("471", user, NULL, error);
                return;
            }
            //si oui, rajouter au channel
            user->be_added_to_channel(chan);
            //On l'ajoute a sa liste
            user->add_channel_to_list(chan);

            send_join_message(chan, user, user->get_params(), server);

            /*
            reply_params.push_back(chan->get_name());
            reply_params.push_back(chan->get_topic());
            reply = build_reply(332, user, reply_params);
            server->_response_queue.push_back(std::make_pair(user->get_socket(), reply));
            reply_params.clear();
            */
        }
        //Erreur to many channels car l user fait partie de trop de channels
        else
        {
            error.push_back(channel);
            error_handler("405", user, NULL, error);
            return;
        }
        //voir cas ou il y aurait plus de params mais qu ils pourraient etre ignores ?
    }
#if DEBUG
    std::cout << RED << "EXIT JOIN CMD" << NC << std::endl;
#endif
}