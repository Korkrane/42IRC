#include <irc.hpp>
#include <algorithm>

bool Commands::nickIsAvailable(std::string nickname, IRC *server, User *user)
{
  (void)user;

  //Capitalizer pour etre sensible a la casse
  std::string str(nickname);
  std::transform(str.begin(), str.end(),str.begin(), ::toupper);

  //Faire le tour des user et voir si leur nickname correspond
  std::vector <User *> users = server->get_users();
  std::vector<User *>::iterator it = users.begin();
  std::vector<User *>::iterator ite = users.end();
  std::string cmp;
  while (it != ite)
  {
    cmp = (*it)->get_nickname();
    std::transform(cmp.begin(), cmp.end(), cmp.begin(), ::toupper);
    if (cmp.compare(str) == 0)
    {
#if DEBUG
      std::cout << "There must be a nickname collision." << std::endl;
      std::cout << str << "is should be the same as " << cmp << std::endl;
#endif
      return (false);
    }
    it++;
  }
  return (true);
}

bool Commands::checkNickGrammar(std::string nickname, IRC *server, User *user)
{
  (void)server;

  int i = 0;
  int length = nickname.length();

  //Preparation du vector qu'on envoie en cas d'erreur
  std::vector<std::string> param_error;
  param_error.push_back(nickname);

  //La taille du nick ne doit pas depasser 9 idealement
  if (length > 9)
  {
 #if DEBUG
    std::cout << "Nickname size is too big and should be avoided." << std::endl;
 #endif

    error_handler("432", user, NULL, param_error);
    return (false);
  }
  while (i < length)
  {
    if (!std::strchr(NICK_VALID_CHARS, nickname[i]))
    {
#if DEBUG
      std::cout << "Found special char that should be avoided." << std::endl;
#endif
      error_handler("432", user, NULL, param_error);
      return (false);
    }
    i++;
  }
  //Le premier caractere doit etre un alpha (a retester)
  if (!isalpha(nickname[0]))
  {
#if DEBUG
    std::cout << "The nickname does not start with an alpha and that should be avoided." << std::endl;
#endif
    error_handler("432", user, NULL, param_error);
    return (false);
  }

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
 */
void  Commands::nick_cmd(User *user, IRC *server)
{
  (void)server;

 #if DEBUG
   std::cout << RED << "ENTER NICK CMD " << NC << std::endl;
 #endif
  if (user->get_params_size() != 1)
  {
#if DEBUG
    std::cout << "Nick command called but param size is incorrect" << std::endl;
#endif
    //A rechecker
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
  std::vector<std::string> param;
  if (checkNickGrammar(nick_arg, server, user) == false)
  {
    #if DEBUG
      std::cout << RED << "DEBUG: NICK GRAMMAR CHECK RETURN FALSE" << NC << std::endl;
    #endif
    return ;
  }

  //Puis on verifie que le nickname n existe pas deja (-> sinon cas de collision)
  if (nickIsAvailable(nick_arg, server, user) == false)
  {
    param.push_back(user->get_params().front());
    //A tester
    error_handler("433", user, NULL, param);
    return ;
  }

  user->set_nickname(nick_arg);

 #if DEBUG
   std::cout << RED << "EXIT NICK CMD " << NC << std::endl;
 #endif

  //Preparer la reponse pour le serveur
  //std::string reply;
  //Attention, le username et hostname doivent etre set correctement dans le constructeur de User
  //reply = ":" + user->get_nickname() + "!" + user->get_username() + "@" + user->get_hostname() + " NICK " + nick_arg + "\r\n";
}