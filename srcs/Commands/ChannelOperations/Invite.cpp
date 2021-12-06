#include <irc.hpp>

/*
** Mahaut
*/

User    *find_target_nick(std::string target_nick, User *user, Server *server)
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
        if (check_nick.)
        it++;
    }
    return (NULL);
}

/**
 * @brief 
 * 
 * @param user 
 * @param server 
 * Params: <nickname> <channel>
 */
void    Commands::invite(User *user, Server *server)
{
    (void)user;
    (void)server;

    //1. Verifier le nombre d'argument
    if (user->get_params_size() != 2)
    {
#if DEBUG
    std::cout << BLUE << "DEBUG: " << "Invite command incorrect params size" << std::endl;
#endif
        std::vector<std::string> error;
        error.push_back(user->get_command_name());
        error_handler("461", user, NULL, error);
    }
    //2. Verifier si le nickname correspond bien a quelqu'un
    std::string target_nick;

    //3. Verifier si le channel correspond bien a un channel

    //4. Verifier qu'on a les droits d'inviter ?
    
    //5. Ajouter au channel l'user

    //6. Envoyer le message au serveur
    return ;
}