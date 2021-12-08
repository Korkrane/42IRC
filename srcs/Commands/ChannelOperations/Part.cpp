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
  //Preparation du serveur d'arguments en cas d'ereur
  std::vector<std::string> error;
  // Verifier le nombre d'argument, si il est egal a 1, renvoyer une erreur
  if (user->get_params_size() == 1)
  {
      error.push_back(user->get_command_name())
      error_handler("461", user, this, error);
  }
  //On sauvegarde les arguments qui suivent
  std::string channel = params.front()

  //On va sauvegarer tous les arguments qui suivent comme le message qui peut etre en differentes strings
  std::vector<std::string>::iterator it = params.begin()++;
  std::vector<std::string>::iterator ite  = params.end();
  std::vector<std::string> message;

  //TODO: faire une fonction separee pour pouvoir la reutiliser et tester
  while (it != ite)
  {
    message.push_back(*it);
    i++;
  }
  //On verifie que la channel existe bien le nom doit etre correct et la channel doit exister
  if (is_correct_channel_name == false)
  {
      //NOSUCHCHANNEL
      error.push_back();
  }

  //Ensuite on va boucler sur les channels et voir si le client en membre
  //si il n est pas membre on retourne une erreur
  //si il est membre on quitte le channel
  return ;
}