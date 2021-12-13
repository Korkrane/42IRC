#include <IRC.hpp>

/*
void Commands::send_full_notice(User *target, User *user, IRC *server, std::vector<std::string> message)
{
    (void)target;
    (void)user;
    (void)server;
    (void)message;

    std::string rpl = server->init_rpl(user);
    rpl += " NOTICE " + target->get_nickname();
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
    //TODO: verifier si ca doit etre user ou target
    server->_response_queue.push_back(std::make_pair(user->get_socket(), rpl));
    return;
}
*/

/**
 * @brief
 *
 * @param user
 * @param server
 * Baudoin + aide Mahaut
 * TODO: updater avec changement du parsing ?
 */
void Commands::notice(User *user, IRC *server)
{
    (void)user;
    (void)server;

    int size = user->get_params_size();
    std::vector<std::string> params = user->get_params();
    //Preparation du vecteur a envoyer en cas d'erreur
    std::vector<std::string> error;

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
    //TODO: build reply
    //send_full_notice(target, user, server, message);
    return;
}