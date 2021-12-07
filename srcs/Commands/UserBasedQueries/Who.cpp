#include <irc.hpp>

/**
 * @brief
 * Mahaut
 * The WHO command is used by a client to generate a query which returns
 * a list of information which 'matches' the <mask> parameter given by
 * the client.
 * Parameters: [ <mask> [ "o" ] ]
 * Dans le cas de la commande WHO la reponse ne sera jamais transmise dans
 * le channel mais sur la page du serveur.
 */

void Commands::who(User *client, IRC *server)
{
  (void)client;
  (void)server;
  /* Gestion des erreurs en fonction des parametres */
  /* Le serveur renvoie une erreur - pas dans le channel */
  /*
  if (client->get_params_size() == 0)
  {
    //le serveur doit renvoyer deux lignes de reponses
    //ERR_NEEDMOREPARAMS
    std::string help = whoHelpParameter();
    //WHO :<server>|<nick>|<channel>|<realname>|<host>|0 [[Aafhilmnoprstux][%acdfhilnorstu] <server>|<nick>|<channel>|<realname>|<host>|0]
  }
  */
  //S il n y en a qu un alors appeler une fonction de classe (statique)
  //qui va pernettre d 'afficher tous les clients un par un

  //si il y a deux parametres il faut verifier que celui-ci
  //correspond bien a une channel existant (dans le serveur)
  //Meme si le client n en fait pas partie ?
  return;
}

/*
** Utils pour la fonction
*/
std::string Commands::whoHelpParameter(void)
{
  std::string server_to_rep = "WHO :<server>|<nick>|<channel>|<realname>|<host>|0 [[Aafhilmnoprstux]\%acdfhilnorstu] <server>|<nick>|<channel>|<realname>|<host>|0]";
  return (server_to_rep);
}