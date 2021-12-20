#include <IRC.hpp>

//TODO: gerer le cas ou on voudrait creer un topic pour plsieurs channels
void Commands::topic(User *user, IRC *server)
{
    unsigned int size = user->get_params_size();
    std::vector<std::string> params = user->get_params();
    std::vector<std::string> error;

    if (size == 0)
    {
        error.push_back(user->get_command_name());
        return (return_error("461", user, server, error, ""));
    }
    std::string channel = params[0];

#if MALATINI == 1
    std::cout << GREEN << "Channels is : " << channel << NC << std::endl;
#endif
    //verifier que la channel passe en parametre existe
    if (is_correct_channel_name(channel) == false || server->has_channel(channel) == false)
    {
        error.push_back(channel);
        return (return_error("403", user, server, error, ""));
    }
    //On va sauvegarder les string qui constituent le topic
    std::vector<std::string> topic;
    unsigned int i = 1;
    while (i < size)
    {
        topic.push_back(params[i]);
        i++;
    }
    //et que le client y est registered
    Channel *chan = server->find_channel(channel);

    if (!chan)
    {
#if MALATINI == 1
        std::cout << RED << "TOPIC, the channel is invalid." << NC << std::endl;
#endif
        error.push_back(channel);
        return (return_error("403", user, server, error, ""));
    }
    else
    {
#if MALATINI == 1
        std::cout << RED << "TOPIC : THE CHAN IS NOT NULL" << NC << std::endl;
#endif
        ;
    }
    //si il n est pas membre on retourne une erreur
    if (chan->user_is_member(user) == false)
    {
        error.push_back(channel);
        return (return_error("442", user, server, error, "")); //You're not on that channel
    }
    if (size > 1 && params[1].empty())
    {
        check_topic(chan, user, server);
    }
    //Si la channel porte le mode "t", seuls les operateurs peuvent set le topic
    if (chan->has_mode('t') == true && !chan->user_is_operator(user))
    {
#if MALATINI == 1
        std::cout << BLUE << "TOPIC must not be set." << NC << std::endl;
#endif
        error.push_back(channel);
        //Erreur not operateur
        return (return_error("482", user, server, error, ""));
    }

    //Si la chaine est une chaine vide (comprendre contient uniquement :), ca unset les topic (clear)
    //Si il n y a pas de chaine, alors fait permet de checker quel est le topic
    if (size > 1 && params[1].compare(":") == false)
    {
        chan->clear_topic(user, server, topic);
    }
    else if (size > 1)
    {
#if MALATINI == 1
        std::cout << GREEN << "TOPIC : setting topic to " << params[1] << NC << std::endl;
#endif
        chan->set_topic(params[1]);
    }
    else if (size == 1)
    {
        if (!chan->get_has_topic())
            params.push_back(":No topic is set");
        else
            params.push_back(chan->get_topic());
    }
    server->send_rpl_to_all_members("", chan->get_members(), params, "TOPIC");
    return;
}

void Commands::check_topic(Channel *channel, User *user, IRC *server)
{
    std::vector<std::string> error;
    if (channel->get_has_topic() == false)
    {
        error.push_back(user->get_command_name());
        return (return_error("331", user, server, error, ""));
    }
    else
    {
        error.push_back(user->get_command_name());
        return (return_error("332", user, server, error, ""));
    }
    return;
}