#include <irc.hpp>

/**
 * @brief 
 * 
 * @param nickname 
 * @return true 
 * @return false 
 */
bool nickIsAvailable(std::string nickname)
{
  (void)nickname;
  //Capitalizer pour etre sensible a la casse g
  //Faire le tour des user et voir si leur nickname correspond
  //J'ai fait le test pour voir si c etait sensible a la casse et ca avat l'air
  //de faire timeout freenode

  return (true);
}

/**
 * @brief 
 * 
 * @param nickname 
 */
bool checkNickGrammar(std::string nickname)
{
  (void)nickname;

  //Attention a certains caracteres speciaux
  std::string special("[]\\_^{|}");

  //Le premier caractere doit etre un alpha

  //le premier caractere ne doit pas faire partie du charset special

  return true;
}

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
  if (user->get_params_size() != 1)
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
  std::string nick_arg = user->get_params().front();
#if DEBUG
  std::cout << "param for nick command is " << nick_arg << std::endl;
#endif
  bool res = checkNickGrammar(nick_arg);
  //Puis on verifie que le nickname n existe pas deja (-> sinon cas de collision)
  //Preparer la reponse pour le serveur
  //Modifier les infos relatives au client pour enregistrer le nickname
  return;
}
