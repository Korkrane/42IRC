#include <irc.hpp>

/**
 * @brief
 *
 * @param command
 * @param client
 * @param server
 * Mahaut
 * 1ere fonction de la liste des Channel Operations dans la rfc
 * TODO: a tester
 */

void Commands::join(User *user, IRC *server)
{
    (void)user;
    (void)server;
    std::vector<std::string> error;

    //On verifie le nombre minimum de param
    //TODO: revoir si mon get params est d'actualite ou si le resultat du parsing est ailleurs
    if (user->get_params_size() == 1)
    {
        error.push_back(user->get_command_name());
        error_handler("461", user, NULL, error);
        return ;
    }
    //Dans nos tests via hexchat seuls 2 params sont pris en compte (1 channel et 2 key)
    if (user->get_params_size() == 2)
    {
        std::string channel = user->get_params().front();
        std::string opt_key = user->get_params().back();

        //On verifie si l'argument channel est correct
        if (is_correct_channel_name(channel) == false)
        {
            error.push_back(channel);
            error_handler("403", user, NULL, error);
            return ;
        }
        //On verifie si la channel existe, sinon on va la creer
        Channel *chan = NULL;
        if (server->has_channel(channel) == false)
        {
            //Si la channel n'existe pas il faut pouvoir la creer
            chan = user->creates_channel(channel);
        }
        else
        {
            //Fonction qui permet de recuperer le pointeur de la channel correspondante
            chan = server->find_channel(channel);
            //On verifie si la channel n est pas full
            if (chan->is_full_channel() == true)
            {
                error.push_back(channel);
                error_handler("471", user, chan, error);
                return ;
            }
        }
        if (chan->is_correct_channel_key(opt_key) == false)
        {
            error.push_back(channel);
            error_handler("475", user, NULL, error);
            return ;
        }
        //on verifie si le user n'a pas atteint son quota max de channel
        if (user->can_join() == true)
        {
            //On verifie si le user ne listen pas deja sur trop de channels
            if (chan->get_members_nb >= CHAN_MAXCAPACITY)
            {
                error.push_back(channel);
                error_handler("471", user, NULL, error);
                return ;
            }
            //si oui, rajouter au channel 
            //TODO: a tester
            user->_be_added_to_channel(chan);
        }
        //Erreur to many channels car l user fait partie de trop de channels
        else
        {
            error.push_back(channel);
            error_handler("405", user, NULL, error);
            return ;
        }
        //voir cas ou il y aurait plus de params mais qu ils pourraient etre ignores ?
    }
    return ;
}