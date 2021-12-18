#include <IRC.hpp>

//TODO: a revoir ou supprimer
int    Commands::who_match_user(User *user, IRC *server)
{
    (void)user;
    (void)server;

    /*
    std::vector<User *> users = server->get_users();
    //std::vector<User *>::iterator it = users.begin();
    std::vector<std::string> params = user->get_params();
    server->send_rpl_display_all_users("352", user, user->get_target_channel(), "JOIN");
    */
    return  (0);
}

/**
 * @brief WHO renvoie code 352 x fois (x etant le nombre de membres de la channel)
 * puis un 315 pour finir
 */
//TODO: a finir, valider et refactor
void    Commands::who(User *user, IRC *server)
{
    (void)user;
    (void)server;

    #if MALATINI
        std::cout << RED << "Who command invoked !" << NC << std::endl;
    #endif
    //who_match_user(user, server);
    Channel *channel = NULL;
    channel = user->get_target_channel();
    if (channel)
    {
        unsigned int nb = channel->get_members_nb();
        #if MALATINI == 1
            std::cout << BLUE << "The number of members is " << nb << NC << std::endl; 
        #endif
        //On va toujours noter l user qui a fait la requete ici
        std::string prefix = "127.0.0.1 352 " + user->get_nickname();
        std::vector<std::string> reps;
        std::string tmp;
        std::string channel_name = channel->get_name();
        //int i = 0;
        
        std::vector<User *> users = channel->get_members();
        //Pour chaque user je vais creer la reponse
        std::vector<User *>::iterator it = users.begin();
        std::vector<User *>::iterator ite = users.end();

        while (it != ite)
        {
            tmp = prefix;
            tmp += " " + channel_name + " ";
            //Le 0 correspond a notre domaine name pas defini
            tmp += (*it)->get_nickname() + " 127.0.0.1 0";
            tmp += (*it)->get_realname() + "H ";
            if (channel->user_is_operator(*it) == true)
            {
                tmp += "@";
            }
            //TODO: il y a un char special pour les user away
            tmp += " :0 realname";
            reps.push_back(tmp);
            it++;
            tmp = "";
        }
        //Ajouter la string end of who au vecteur
        //On va devoir envoyer toutes les string du vecteur
        //Je vais implementer la 315 directement ici, a supprimer de server->build_rpl
        tmp += user->get_nickname() + "!" + user->get_username() + "@0 315 : ";
        tmp += channel->get_name() + " :End of WHO list";
        //Je reboucle pour les envoyer une par une
        it = users.begin();
    }
    else
    {
        #if MALATINI == 1
            std::cout << RED << "Error : called WHO but there is no channel target !" << NC << std::endl;
        #endif
    }
    return;
}