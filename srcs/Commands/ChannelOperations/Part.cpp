#include <irc.hpp>

/**
 * @brief
 *
 * @param command
 * @param client
 * @param server
 * Parameters: <channel> *( "," <channel> ) [ <Part Message> ]
 * The PART command causes the user sending the message to be removed
   from the list of active members for all given channels listed in the
   parameter string.
 * Mahaut
 */
void  Commands::part(User *user, IRC *server)
{
  (void)user;
  (void)server;
  // Verifier le nombre d'argument, si il est egal a 1, renvoyer une erreur

  //On parse le deuxieme argument si ce n est pas deja fait ?

  //On verifie que les autres arguments sont corrects (channel existants)

  //Ensuite on va boucler sur les channels et voir si le client en membre
  //si il n est pas membre on retourne une erreur
  //si il est membre on quitte le channel
  return ;
}