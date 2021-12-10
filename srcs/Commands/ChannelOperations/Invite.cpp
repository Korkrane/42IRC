#include <IRC.hpp>

/**
 * @brief
 *
 * @param target_channel
 * @param user
 * @param server
 * @return Channel*
 */
Channel *Commands::find_target_channel(std::string target_channel, User *user, IRC *server)
{
    (void)target_channel;
    (void)user;
    (void)server;

    std::vector<Channel *>::iterator it;
    std::vector<Channel *>::iterator ite;
    std::vector<Channel *> channels = server->get_channels();
    it = channels.begin();
    ite = channels.end();
    std::string check_target;
    while (it != ite)
    {
        check_target = (*it)->get_name();
        if (check_target.compare(target_channel) == 0)
            return (*it);
        it++;
    }
#if DEBUG
    std::cout << BLUE << "DEBUG: "
              << "did not find target_nick" << std::endl;
#endif
    return (NULL);
}

/**
 * @brief
 *
 * @param target_nick
 * @param user
 * @param server
 * @return User*
 */
User *Commands::find_target_nick(std::string target_nick, User *user, IRC *server)
{
    (void)target_nick;
    (void)user;
    (void)server;

    std::vector<User *>::iterator it;
    std::vector<User *>::iterator ite;
    it = server->get_users().begin();
    ite = server->get_users().end();
    std::string check_nick;
    while (it != ite)
    {
        check_nick = (*it)->get_nickname();
        if (check_nick.compare(target_nick) == 0)
            return (*it);
        it++;
    }
#if DEBUG
    std::cout << BLUE << "DEBUG: "
              << "did not find target_nick" << std::endl;
#endif
    return (NULL);
}

/**
 * @brief
 *
 * @param user
 * @param server
 * Params: <nickname> <channel>
 * TODO: faire des tests pour voir l'ordre de priorite des erreurs
 */
void Commands::invite(User *user, IRC *server)
{
    (void)user;
    (void)server;

    //0. Preparation en cas d'erreur
    std::vector<std::string> error;

    //1. Verifier le nombre d'argument
    if (user->get_params_size() != 2)
    {
#if DEBUG
        std::cout << BLUE << "DEBUG: "
                  << "Invite command incorrect params size" << std::endl;
#endif
        error.push_back(user->get_command_name());
        error_handler("461", user, NULL, error);
        return;
    }
    //2. Verifier si le nickname correspond bien a quelqu'un
    std::string target_nick = user->get_params().front();
    User *target_user = find_target_nick(target_nick, user, server);
    if (!target_user)
    {
        error.push_back(user->get_nickname());
        error_handler("401", user, NULL, error);
        return;
    }
    //3. Verifier si le channel correspond bien a un channel
    std::string target_channel = user->get_params().back();
    Channel *chan = find_target_channel(target_channel, user, server);
    if (chan)
    {
        //TODO: a tester
        //4. Verifier que le user est lui meme member
        if (chan->user_is_member(user) == false) //NOTONCHANNEL
        {
            error.push_back(chan->get_name());
            error_handler("442", user, chan, error);
            return;
        }
        //5. Verifier que la channel n'est pas full
        if (chan->get_members_nb() >= USER_MAXCHAN)
        {
            return;
        }
        //6. Verifier que celui qui invite n'est pas deja sur le channel
        if (chan->user_is_member(target_user) == false)
        {
            error.push_back(user->get_nickname());
            error.push_back(chan->get_name());
            error_handler("443", user, chan, error);
            return;
        }
        //7. Verifier que le target nick_name est connecte
        if (server->find_user(target_nick) == true)
        {
            error.push_back(user->get_nickname());
            error_handler("401", user, chan, error);
            return;
        }
        //8. Ajouter au channel l'user
        //chan->addMember(target_nick)
        User *target_user = server->get_user_ptr(target_nick);
        chan->newMember(target_user, false);

        //9. Envoyer le message au serveur
        server->send_rpl("431", user, chan, chan->get_name() + " " + target_user->get_nickname());
    }
    return;
}