#include <IRC.hpp>

/**
 * @brief
 *
 * @param user
 * @param server
 * Baudoin + aide Mahaut
 */
void Commands::privmsg(User *user, IRC *server)
{
    int size = user->get_params_size();
    std::vector<std::string> error;
    std::vector<std::string> params = user->get_params();
    if (size < 2)
    {
        //TODO: build reply
        /*
        error.push_back(user->get_command_name());
        error_handler("461", user, NULL, error); //Not enough params
        */
        return;
    }
    else if (size == 2)
    {
        //TODO: build reply
        //error_handler("412", user, NULL, error); //No text to send
        return;
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
        //TODO: build reply
        /*
        error.push_back(receiver);
        error_handler("401", user, NULL, error);
        */
        return;
    }
    //Deux cas de figure observes
    //Si le premier mot est prefixe d'un :
    if (prefixed_by_colon(message.front()) == true)
    {
        //TODO: build reply
        //Tout le message sera transmis
        //send_full_privmsg(target, user, server, message);
        return ;
    }
    else
    {
        //TODO: build reply
        //send_one_word_privmsg(target, user, server, message.front());
        return ;
    }
    //Si il ne l'est pas
    //seul le premier mot est transmis et le reste est ignore
    //TODO: voir pour les autres commandes qui sont concernees par un : en faisant des tests
    return;
}

//TODO: a tester - Attention si on veut implementer away il y a des choses a ajouter
/*
void Commands::send_full_privmsg(User *target, User *user, IRC *server, std::vector<std::string> message)
{
    (void)target;
    (void)user;
    (void)server;
    (void)message;
    std::string rpl = server->init_rpl(user);
    rpl += " PRIVMSG " + target->get_nickname();
    std::vector<std::string>::iterator it = message.begin();
    std::vector<std::string>::iterator ite = message.end();

    while (it != ite)
    {
        rpl += (*it);
        if (it + 1 == ite)
            break;
        rpl += " ";
        it++;
    }
    rpl += "\r\n";
    //TODO: a revoir, il y a des fois on fait cette fonction et d autres ou on fait un send_rpl, verifier que tout est ok
    server->_response_queue.push_back(std::make_pair(user->get_socket(), rpl));
    return;
}
*/

/*
void Commands::send_one_word_privmsg(User *target, User *user, IRC *server, std::string message)
{
    (void)user;

    std::string rpl = server->init_rpl(user);
    rpl += " PRIVMSG " + target->get_nickname();
    rpl += message;
    rpl += "\r\n";
    return;
}
*/