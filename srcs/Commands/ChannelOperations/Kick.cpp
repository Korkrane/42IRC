
#include <IRC.hpp>

//TODO: a tester
/*
void Commands::send_kick_message(Channel *channel, User *user, IRC *server, std::vector<std::string> comment)
{
    (void)channel;
    (void)user;
    (void)server;
    (void)comment;

    std::string rpl = server->init_rpl(user);
    rpl += " KICK ";
    rpl += channel->get_name() + " ";
    rpl += user->get_nickname() + " ";

    std::vector<std::string>::iterator it = comment.begin();
    std::vector<std::string>::iterator ite = comment.end();
    while (it != ite)
    {
        rpl += (*it);
        if (it + 1 == ite)
            break;
        rpl += " ";
        it++;
    }
    rpl += "\r\n";
#if DEBUG == 1
    std::cout << BLUE << "DEBUG: "
              << "KICK: message will be " << rpl << std::endl;
#endif
    server->send_rpl_to_all_members(channel, rpl);
    return;
}
*/

void Commands::kick(User *user, IRC *server)
{
    (void)user;
    (void)server;
    int size = user->get_params_size();
    std::vector<std::string> error;
    std::vector<std::string> param = user->get_params();

    //on verifie le nombres de parametre
    if (size <= 2)
    {
        //TODO: build reply
        /*
        error.push_back(user->get_command_name());
        error_handler("461", user, NULL, error);
        */
        return;
    }

    //TODO: a tester
    std::string channel = param[0];
    std::string target = param[1];

    Channel *chan = server->find_channel(channel);
    //on prepare la string comment si il y en a
    if (is_correct_channel_name(channel) || server->has_channel(channel) == false)
    {
        //NOTONCHANNEL
        //TODO: build reply
        /*
        error.push_back(channel);
        error_handler("442", user, chan, error);
        */
    }
    //on check si l'user existe et fait partie du channel
    if (server->find_user(target) == false)
    {
        //TODO: build reply
        /*
        error.push_back(target);
        error_handler("401", user, chan, error);
        */
        return;
    }
    User *target_user = server->get_user_ptr(target);
    if (chan->user_is_member(target_user) == false)
    {
        //TODO: build reply
        /*
        error.push_back(target);
        error_handler("401", user, chan, error);
        */
        return;
    }
    //sinon renvoyer une erreur
    std::vector<std::string> comment;
    if (size >= 3)
    {
        std::vector<std::string>::iterator itc = param.begin();
        std::vector<std::string>::iterator ite = param.end();
        itc += 2;
        while (itc != ite)
        {
            comment.push_back(*itc);
            itc++;
        }
    }
    //on kick out du channel
    chan->deleteMember(target_user);
    user->remove_channel_from_list(chan);
    //on genere la reponse avec comment ou pas
    //TODO: ajouter appel au nouveau build reply
    //send_kick_message(chan, target_user, server, comment);
    return;
}