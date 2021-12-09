#include <IRC.hpp>

void      Commands::send_topic_message(Channel *channel, User *user, std::vector<std::string> message)
{
    (void)channel;
    (void)user;
    (void)topic;
    std::string rpl = init_rpl(user);
    rpl += " TOPIC ";
    rpl += channel->get_name();
    rpl += " :";
    //Ajouter toutes les string params
    std::vector<std::string>::iterator it = message.begin();
    std::vector<std::string>::iterator ite = message.end();
    while (it != ite)
    {
        rpl += (*it);
        //Pour ne pas ajouter un espace au dernier mot
        if (it + 1 == ite)
            break;
        rpl += " ";
        it++;
    }
    rpl += "\r\n";
    //On doit envoyer le message a toute la channel
    send_rpl_to_all_members(channel, rpl);
    return ;
}


/**
 * @brief
 *
 * @param client
 * @param server
 * Mahaut
 */
void		Commands::topic(User *user, IRC *server)
{
    (void)user;
    (void)server;
    unsigned int size = user->get_params_size();
    std::vector<std::string> params = user->get_params();
    //Vecteur pour gerer les erreurs
    std::vector<std::string> error;
    // verifier le nombre d argument (ne peut pas etre egal a 1)
        //retourner erreur ERR_NEEDMOREPARAMS
    if (size == 1)
    {
        error.push_back(user->get_command_name());
        error_handler("461", user, NULL, error);
        return ;
    }
    std::string channel = params[0];
    //verifier que la channel passe en parametre existe
    if (is_correct_channel_name(channel) == false || server->has_channel(channel) == false)
    {
        //NOSUCHCHANNEL
      error.push_back(channel);
      error_handler("403", user, NULL, error);
      return ;
    }
    //On va sauvegarder les string qui constituent le topic
    std::vector<std::string> topic;
    int i = 1;
    while (!params[i].empty())
    {
        topic.push_back(params[i]);
    }
    //et que le client y est registered
    Channel *chan = server->find_channel(channel);
    //si il n est pas membre on retourne une erreur
    if (chan->user_is_member(user) == false)
    {
        //NOTONCHANNEL
        error.push_back(channel);
        error_handler("442", user, chan, error);
        return ;
    }
    //Est-ce qu il faut etre operateur pour set un topic ? a priori non
    //verifier si il y a deja un topic ou pas
    if (params[1].empty())
    {
        check_topic(chan, user, server);
    }
    //Si la chaine est une chaine vide (comprendre contient uniquement :), ca unset les topic (clear)
    //Si il n y a pas de chaine, alors fait permet de checker quel est le topic
    else if (params[1].compare(":") == false)
    {
        chan->clear_topic(user, server, topic);
    }
    else
    {
        chan->set_topic(user, server, topic);
    }
    send_topic_message(chan, user, topic);
    return ;
}

//TODO: a tester
void            Commands::check_topic(Channel *channel, User *user, IRC *server)
{
    (void)channel;
    (void)user;
    (void)server;

    std::vector<std::string> error;
    if (channel->get_has_topic() == false)
    {
        //RPL _NOTOPIC
        send_rpl("331", user, channel, "");
    }
    else 
    {
        send_rpl("332", user, channel, "");
    }
    return ;
}