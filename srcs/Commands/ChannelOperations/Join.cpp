#include <irc.hpp>

/**
 * @brief
 *
 * @param command
 * @param client
 * @param server
 * Mahaut
 */

void Commands::join(User *client, Server *server)
{
    (void)client;
    (void)server;
    //S'il n'y a qu'un param, retourner
    //erreur ERR_NEEDMOREPARAMS

    //les deux arguments a ce stade on deja ete parse ?
    //On a une string channel_name
    //et une string key

    //on verifie si le channel existe
    //Plusieurs cas de figure en fonction de l existence du channel ou pas
    //on verifie si le user ne fait pas deja partie du channel
    //On verifie si le user ne listen pas deja sur trop de channels
    //On verifie si le channel n'a pas deja trop de user (voir la definition des macros)

    //On verifie la valeur de la cle ?
    //Si la valeur est OK, le client va pouvoir etre ajoute au channel
    //Si la valeur de la cle n est pas correcte, retourner "ERR_BADCHANNELKEY"

    //creer une channel si elle n existe pas deja
    //voir si il faut potentiellement quitter toutes les autres channels

    //verifier si la channel a un nom correct
}