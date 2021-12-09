#include <IRC.hpp>

/**
 * @brief
 *
 * @param user
 * @param server
 * Baudoin + aide Mahaut
 */
void    Commands::privmsg(User *user, IRC *server)
{
    (void)user;
    (void)server;

    int size = user->get_params_size();
    std::vector<std::string> error;
    std::vector<std::string> params = user->get_params();
    if (size < 2)
    {
        error.push_back(user->get_command_name());
        error_handler("461", user, NULL, error);//Not enough params
        return ;
    }
    else if (size == 2)
    {
        error_handler("412", user, NULL, error);//No text to send
        return ; 
    }
    //On analyse les params 
    //Le premier param c'est le target user
    //TODO: a modifier avec le changement dans le parsing 
    std::string receiver = params.front();
    std::vector<std::string> message = store_second_param_message(params);
    //TODO: je n ai pas reussi a reproduire l erreur toomanytarget
    //On verifie qu'on trouve la target
    User *target = server->get_user_ptr(receiver);
    if (!target)
    {
        error.push_back(receiver);
        error_handler("401", user, NULL, error);
        return;
    }
    //Deux cas de figure observes 
    //Si le premier mot est prefixe d'un :
    if (prefixed_by_colon(message.front()) == true)
    {
        //Tout le message sera transmis
        send_full_privmsg(target, user, server, message);
    }
    else
    {
        send_one_word_privmsg(target, user, server, message);
    }
    //Si il ne l'est pas
        //seul le premier mot est transmis et le reste est ignore
    //TODO: voir pour les autres commandes qui sont concernees par un : en faisant des tests
    return ;
}

void                Commands::send_full_privmsg(User *target, User *user, IRC *server, std::vector<std::string>message)
{
    (void)target;
    (void)user;
    (void)server;
    (void)message;
    return ;
}

void                Commands::send_one_word_privmsg(User *target, User *user, IRC *server, std::vector<std::string>message)
{
    (void)target;
    (void)user;
    (void)server;
    (void)message;
    return ;
}