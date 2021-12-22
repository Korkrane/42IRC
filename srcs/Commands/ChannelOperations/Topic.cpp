#include <IRC.hpp>

bool Commands::same_args(User *user, IRC *server)
{
    (void)user;
    (void)server;
    std::vector<std::string> params = user->get_params();
    int size = params.size();
    std::string param_one = "";
    std::string param_two = "";
    std::string tmp = "";
    std::string tmp2 = "";

    if (size > 1)
        param_one = params[0];
    if (size > 2)
        param_two = params[1];

    if (param_one.length() > 1)
        std::string tmp(param_one.substr(1));
    if (param_two.length() > 1)
        std::string tmp2(param_two.substr(1));
    if (tmp.compare(tmp2) == 0)
    {
#if MALATINI == 1
        std::cout << GREEN << "TOPIC : same arg true" << NC << std::endl;
#endif
        return (true);
    }

    return (false);
}

//obligee de refaire la fonction car le send to all convient pas
void Commands::send_topic_message(User *user, Channel *chan, IRC *server)
{
#if MALATINI == 1
    std::cout << RED << "SEND TOPIC MESSAGE CALLED" << NC << std::endl;
#endif
    (void)user;
    (void)chan;
    //(void)params;
    (void)server;
    std::vector<std::string> params = user->get_topic_params();
    int size = params.size();

#if MALATINI == 1
    if (size == 0)
    {
        std::cout << PURPLE << "The given params vector is empty." << NC << std::endl;
    }
    else
    {
        std::cout << PURPLE << "The size is " << size << std::endl;
    }
#endif
    std::vector<User *> users = chan->get_members();
    std::string rpl = ":" + user->get_nickname() + "!" + user->get_username() + "@0";
    //+chan->get_name() + "\r\n";
    std::vector<User *>::iterator it = users.begin();
    std::vector<User *>::iterator ite = users.end();
    bool info = false;
    if (!chan->user_is_operator(user))
    {
        rpl += " 332 : ";
        info = true;
    }

    else if (size > 1 && params[1].compare(":No topic is set"))
        rpl += " TOPIC ";
    else
        rpl += " 331 : ";
    if (size >= 1)
        rpl += params[0] + " ";
    #if MALATINI == 1
        std::cout << BLUE << "JOIN : the size is " << size << NC << std::endl;
    #endif
    if (size >= 2)
    {
        if (info == true)
        {
            #if MALATINI == 1
                std::cout << PURPLE "JOIN : getting the topic" << NC << std::endl;
            #endif
            rpl += chan->get_topic();
            rpl += "\r\n";
            //si c est une info je ne l'envoie qu a une personne
            server->_response_queue.push_back(std::make_pair(user->get_fd(), rpl));
            return;
        }
        else
            rpl += params[1];
    }
    rpl += "\r\n";
    while (it != ite)
    {
#if MALATINI == 1
        std::cout << GREEN << rpl << NC << std::endl;
#endif
        server->_response_queue.push_back(std::make_pair((*it)->get_fd(), rpl));
        it++;
    }
    user->clear_topic_params();
    return;
}

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
    bool same_arg = same_args(user, server);
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
    if (size >= 1)
        user->add_topic_params(params[0]);
    if (size >= 2)
        user->add_topic_params(params[1]);
    //Si la channel porte le mode "t", seuls les operateurs peuvent set le topic
    if (chan->has_mode('t') == true && !chan->user_is_operator(user) && !same_arg) //
    {
#if MALATINI == 1
        std::cout << BLUE << "TOPIC must not be set." << NC << std::endl;
#endif
        error.push_back(channel);
        //Erreur not operateur
        return (return_error("482", user, server, error, ""));
    }
    else if (same_arg && !chan->user_is_operator(user) && chan->has_mode('t') == true) //Si je ne suis pas operator et qu il y a le mode et que je veux voir le topic
    {
        if (!chan->get_has_topic())
            user->add_topic_params(":No topic is set");
        else
            user->add_topic_params(chan->get_topic());
        send_topic_message(user, chan, server);
        //server->send_rpl_to_all_members("", chan->get_members(), params, "TOPIC");
        return;
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
            user->add_topic_params(":No topic is set");
        else
            user->add_topic_params(chan->get_topic());
        //params.push_back(chan->get_topic());
    }
    send_topic_message(user, chan, server);
    user->clear_topic_params(); //ca fait un peu doublon
    //server->send_rpl_to_all_members("", chan->get_members(), params, "TOPIC");
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