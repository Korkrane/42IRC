#include <IRC.hpp>

//Peut d avoir des infos sur les members connectes au serveur, 
//sur les membres d'un channel ou sur une personne en particulier

//TODO: a revoir (segfault) + codes a implementer
int    Commands::who_match_user(User *user, IRC *server)
{
    (void)user;
    (void)server;

    return (1);
}
    /*
    std::vector<User *> users = server->get_users();
    std::vector<User *>::iterator it = users.begin();
    std::vector<User *>::iterator ite = users.end();
    std::vector<std::string> params = user->get_params();
    //On va chercher si un user correspond au param passe en parametre
    std::string target_user = params.front();
    User *tmp = NULL;
    unsigned int count = 0;
    while (it != ite)
    {
        tmp = server->get_user_ptr(target_user);
        if (tmp)
        {
            server->send_rpl_display_user(user, tmp, NULL, "WHO", "315");
            count++;
        }
        tmp = server->get_user_ptr_realname(target_user);
        {
            server->send_rpl_display_user(user, tmp, NULL, "WHO");
            count++;
        }
        tmp = server->get_user_ptr_username(target_user);
        {
            server->send_rpl_display_user(user, tmp, NULL, "WHO");
            count++;
        }
        it++;
    }
    if (count > 0)
    {
        server->send_rpl("315", user, params, "");//End of who
    }
    return  (count);
}
*/

void    Commands::who(User *user, IRC *server)
{
    (void)user;
    (void)server;

    return;
}
    /*
    std::vector<std::string> params = user->get_params();
    int size = params.size();

    //TODO: tester les cas d erreurs
    Channel *chan = server->find_channel(params[0]);
    if (size == 0)
    {
        if (chan)
        {
            //On doit retourner un message avec tous les clients
            server->send_rpl_display_all_users(code, user, chan,"WHO");
            return;
        }
    }
    else
    {
        std::string channel = params[0];
        Channel *chan = server->find_channel(channel);
        if (chan)
        {
            //On doit verifier si le user est member
            bool is_member = chan->user_is_member(user);
            if (is_member == 1)
            {
                server->send_rpl_chan("", chan, server, user);
                server->send_rpl("315", user, params, "");//END OF WHO
            }
            //TODO: tester ce si n est pas le cas?
            return;
        }
        else
        {
            who_match_user(user, server);
            //if (who_match_user(user, server) == 0)
                //server->send_rpl_display_all_users(user, chan, "WHO");
            return;
        }
    }
    return;
}
*/