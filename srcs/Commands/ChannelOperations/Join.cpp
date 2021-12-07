#include <irc.hpp>

/**
 * @brief
 *
 * @param command
 * @param client
 * @param server
 * Mahaut
 * 1ere fonction de la liste des Channel Operations dans la rfc
 */

void Commands::join(User *user, Server *server)
{
    (void)user;
    (void)server;
    std::vector<std::string> error;

    //On verifie le nombre minimum de param
    if (user->get_params_size() == 1)
    {
        error.push_back(user->get_command_name());
        error_handler("461", user, NULL, error);
    }
    //les deux arguments a ce stade on deja ete parse ?
    //On a une string channel_name - On va verifier que le channel name est correct
    
    //et une string key ?

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
    return ;
}