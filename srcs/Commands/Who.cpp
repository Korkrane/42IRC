#include "../../includes/irc.hpp"

/**
 * @brief
 * Mahaut
 * The WHO command is used by a client to generate a query which returns
 * a list of information which 'matches' the <mask> parameter given by
 * the client.
 * Parameters: [ <mask> [ "o" ] ]
 */

void Commands::who(Client *client, Server *server)
{
  //Voir le nombre de parametre
  //S il n y en a qu un alors appeler une fonction de classe (statique)
  //qui va pernettre d 'afficher tous les clients un par un

  //si il y a deux parametres il faut verifier que celui-ci
  //correspond bien a une channel existant (dans le serveur)
  //Meme si le client n en fait pas partie ?
  return;
}
