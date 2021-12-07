#include <irc.hpp>

/*
** Mahaut
*/

/**
 * @brief
 *
 * @param target_channel
 * @param user
 * @param server
 * @return Channel*
 */
Channel     *Commands::find_target_channel(std::string target_channel, User *user, IRC *server)
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
    std::cout << BLUE << "DEBUG: " << "did not find target_nick" << std::endl;
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
User    *Commands::find_target_nick(std::string target_nick, User *user, IRC *server)
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
    std::cout << BLUE << "DEBUG: " << "did not find target_nick" << std::endl;
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
void    Commands::invite(User *user, IRC *server)
{
    (void)user;
    (void)server;

    //0. Preparation en cas d'erreur
    std::vector<std::string> error;

    //1. Verifier le nombre d'argument
    if (user->get_params_size() != 2)
    {
#if DEBUG
    std::cout << BLUE << "DEBUG: " << "Invite command incorrect params size" << std::endl;
#endif
        error.push_back(user->get_command_name());
        error_handler("461", user, NULL, error);
        return ;
    }
    //2. Verifier si le nickname correspond bien a quelqu'un
    std::string target_nick = user->get_params().front();
    User *target_user = find_target_nick(target_nick,user, server);
    if (!target_user)
    {
        error.push_back(user->get_nickname());
        error_handler("401", user, NULL, error);
        return ;
    }
    //3. Verifier si le channel correspond bien a un channel
    std::string target_channel = user->get_params().back();
    Channel *chan = find_target_channel(target_channel, user, server);
    if (!chan)
    {
        //Il n y a pas l'erreur "no such channel", donc il faudrait la creer ?
        //faire des testsgit
    }
    //4. Verifier qu'on a les droits d'inviter ?

    //5. Verifier que la channel n'est pas full ?

    //6. Verifier que celui qui invite est bien lui-meme sur la channel

    //7. Verifier que celui qui est invite n'est pas deja sur le channel

    //8. Ajouter au channel l'user

    //9. Envoyer le message au serveur
    return ;
}