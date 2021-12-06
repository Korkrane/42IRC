#include <irc.hpp>

/**
 * @brief
 *
 * @param nickname
 * @return true
 * @return false
 * Mahaut
 */

/*TODO: a reprendre
static bool checkNickGrammar(std::string nickname)
{
  (void)nickname;
  //Attention a certains caracteres speciaux
  std::string special("[]\\_^{|}");
  //Le premier caractere doit etre un alpha
  //le premier caractere ne doit pas faire partie du charset special
  //voir autres cas
  return true;
}
*/

/**
 * @brief
 *
 * @param command
 * @param user
 * @param server
 * Parameters: <nickname>
 * NICK command is used to give user a nickname or change the existing
   one.
 * La commande nick va etre appelee pendant la client registration puis "manuellement"
 * a la guise du client ensuite.
 * TODO: voir si throw exceptions
 */
void  Commands::nick(User *user, Server *server)
{
  (void)user;
  (void)server;
/*
#if DEBUG
  user->display_command();
#endif
*/
  if (user->get_params_size() != 2)
  {
#if DEBUG
    std::cout << "Nick command called but param size is incorrect" << std::endl;
#endif
    std::vector<std::string> command;
    std::string cmd_str = user->get_command_name();
    command.push_back(cmd_str);
    error_handler("461", user, NULL, command);
  }
  //Puis on verifie si le nickname est correct grammaticallement (fonction de grammar)

  //Puis on verifie que le nickname n existe pas deja (-> sinon cas de collision)
  //Preparer la reponse pour le serveur
  //Modifier les infos relatives au client pour enregistrer le nickname
  return;
}
