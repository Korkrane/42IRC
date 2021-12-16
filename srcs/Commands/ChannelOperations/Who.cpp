#include <IRC.hpp>

//Commande Who simplifiee, pas de gestion des masques
void    Commands::who(User *user, IRC *server)
{
    (void)user;
    (void)server;

    std::vector<std::string> params = user->get_params();
    int size = params.size();
    std::vector<std::string>::iterator it = params.begin();
    std::vector<std::string>::iterator ite = params.end();

    if (size == 0)
    {
        //On doit retourner un message avec tous les clients
        return (server->send_rpl_display_all_users(user, server, "WHO"));
    }
    while (it != ite)
    {
        it++;
    }
    return;
}