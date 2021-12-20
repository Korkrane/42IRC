#include <IRC.hpp>

//TODO: a revoir ou supprimer
int Commands::who_match_user(User *user, IRC *server)
{
    (void)user;
    (void)server;

    /*
    std::vector<User *> users = server->get_users();
    //std::vector<User *>::iterator it = users.begin();
    std::vector<std::string> params = user->get_params();
    server->send_rpl_display_all_users("352", user, user->get_target_channel(), "JOIN");
    */
    return (0);
}

/**
 * @brief WHO renvoie code 352 x fois (x etant le nombre de membres de la channel)
 * puis un 315 pour finir
 */
//TODO: a finir, valider et refactor
void Commands::who(User *user, IRC *server)
{
#if MALATINI
    std::cout << RED << "Who command invoked !" << NC << std::endl;
#endif
    (void)server;

    if (user->get_display_who() == true)
    {
        std::string prefix = "";
        std::vector<std::string> reps;
        std::string tmp = "";
        Channel *channel = user->get_target_channel();
        if (channel)
        {
            std::string channel_name = channel->get_name();
            std::vector<User *> users;
            unsigned int nb = channel->get_members_nb();
#if MALATINI == 1
            std::cout << BLUE << "The number of members is " << nb << NC << std::endl;
#endif
            //On va toujours noter l user qui a fait la requete ici
            prefix = ":127.0.0.1 352 " + user->get_nickname();
            channel_name = channel->get_name();

            tmp = prefix;
            tmp += " " + channel_name + " ";
            //TODO: reprendre le domain name defini ici
            tmp += user->get_nickname() + " 127.0.0.1 irc.irc42.com ";
            //TODO: pb pour baudoin = realname = "realname", donc j ai mis nickname en attendant
            tmp += user->get_nickname() + " H";
            if (channel->user_is_operator(user) == true)
            {
                tmp += "@";
            }
            //TODO: il y a un char special pour les user away
            tmp += " :0 realname\r\n";
            reps.push_back(tmp);
            tmp = "";
            tmp += ":" + user->get_nickname() + "!" + user->get_username() + "@irc.irc42.com 315 : ";
            tmp += channel->get_name() + " :End of WHO list \r\n";
            reps.push_back(tmp);
            std::vector<std::string>::iterator its = reps.begin();
            std::vector<std::string>::iterator itse = reps.end();
            while (its != itse)
            {

#if MALATINI == 1
                std::cout << GREEN << (*its) << NC << std::endl;
                std::cout << BLUE << "was sent to" << user->get_fd() << NC << std::endl;
#endif
                server->_response_queue.push_back(std::make_pair(user->get_fd(), (*its)));
                its++;
            }
            user->set_display_who(false);
        }
        else
        {
#if MALATINI == 1
            std::cout << RED << "Error : called WHO but there is no channel target !" << NC << std::endl;
#endif
        }
    }
    return;
}