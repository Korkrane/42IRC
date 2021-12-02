#include "../../includes/irc.hpp"

/**
 * @brief 
 * 
 * @param client 
 * @param server 
 */
void		topic(Client *client, Server *server)
{
    // verifier le nombre d argument (ne peut pas etre egal a 1)
        //retourner erreur ERR_NEEDMOREPARAMS
    
    //verifier que la channel passe en parametre existe
    //et que le client y est registered
    //sinon retourner erreur

    //verifier si il y a deja un topic ou pas
    //si oui, le modifier, et envoyer une reply au serveur
    //si non, la creer et envoyer une reply au serveur

}