#include "../../includes/irc.hpp"

class Commands;

/**
 * @brief
 *
 * @param command
 * @param client
 * @param server
 * Parameters: <nickname> <comment>
 * ** Will close client / server connection (by the server)
 * Servers generate KILL messages on nickname collisions.
 * It MAY be available to users who have the operator status
 * See more on RFC 2812.
 */

void Commands::kill(Client *client, Server *server)
{
    (void)client;
    (void)server;
    //Si il y a moins de trois parameteres renvoyer une erreur correspondante
    //TODO: error need more param.

    //si la commande kill n'est pas utilisee dans le cadre d un nickname collision
    //il faut retourner une erreur si le client n' est pas une operateur (err no privilege)

    //verifier si le nickname a killer existe, recuperer le client correspondant
    //generer une string qui explicite la raison de l'exclusion
    //preparer la reply a envoyer au serveur
    //envoyer la reply au serveur (voir diff recv et send)

    //Le client doit etre deconnecte du serveur et donc etre retire de toutes les channels
    //Une fois deconnecte, son status doit etre modifie
    //TODO: voir si il doit faire partie de la liste des banned ?
}