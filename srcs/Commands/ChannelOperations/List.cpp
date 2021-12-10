#include <IRC.hpp>

/**
 * @brief va permettre de lister tous les channels du serveur (et eventuellement leurs topics)
 *
 * @param client
 * @param server
 * Mahaut
 */
void Commands::list(User *user, IRC *server)
{
    (void)user;
    (void)server;
    //Si il n y a qu un argument
    std::vector<Channel *>::iterator it = server->get_channels().begin();
    std::vector<Channel *>::iterator ite = server->get_channels().end();
    //Si il y a plusieurs argument
    //TODO: revoir le parsing avec la virgule
    int size = user->get_params_size();
    std::vector<std::string> params = user->get_params();
    if (size == 0)
    {
        //On va tout lister
        while (it != ite) //RPL_LSI
        {
            server->send_rpl("322", user, (*it), "");
            it++;
        }
        //A la fin envoyer listeend
        server->send_rpl("323", user, NULL, "");
    }
    else
    {
        Channel *tmp;
        int i = 0;
        //pour chaque param on va chercher et afficher
        //On va lister celles qui sont en arguments
        while (i < size)
        {
            if (is_correct_channel_name(params[i]) == true)
            {
                tmp = server->find_channel(params[i]);
                server->send_rpl("322", user, tmp, "");
            }
            i++;
        }
        //A la fin envoyer listend
        server->send_rpl("323", user, NULL, "");
    }
    return;
}