#include <IRC.hpp>

//TODO: faire une sous fonction d'initialisation du debut de rpl qui reservira a chaque fois
void Commands::send_part_message(Channel *channel, User *user, std::vector<std::string> message, IRC *server)
{
  std::string rpl = server->init_rpl(user);
  rpl += " PART " + channel->get_name();

  //Faire le tour de message
  std::vector<std::string>::iterator it = message.begin();
  std::vector<std::string>::iterator ite = message.end();
  while (it != ite)
  {
    rpl += (*it);
    rpl += " ";
    it++;
  }
  //On termine
  rpl += "\r\n";
#if DEBUG
  std::cout << BLUE << "DEBUG: "
            << "COMMAND PART: the repply is" << rpl << std::endl;
#endif
  //Maintenant que j ai la reply, je dois l'envoyer a tout le monde
  server->send_rpl_to_all_members(channel, rpl);
}

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
 * Le premier param est la channel a quitter et le reste est un potentiel message
 * Si il n y a pas de message on replace par le username du participant ? En faisant nos tests on a vu "Leaving"
 */
void Commands::part(User *user, IRC *server)
{
  (void)user;
  (void)server;
  //Preparation du serveur d'arguments en cas d'ereur
  std::vector<std::string> error;
  std::vector<std::string> params = user->get_params();
  // Verifier le nombre d'argument, si il est egal a 1, renvoyer une erreur
  if (user->get_params_size() == 1)
  {
    error.push_back(user->get_command_name());
    error_handler("461", user, NULL, error);
  }
  //On sauvegarde les arguments qui suivent
  std::string channel = params.front();
  std::vector<std::string> message;

  if (user->get_params_size() > 2)
  {
    std::vector<std::string>::iterator it = params.begin();
    it++;
    std::vector<std::string>::iterator ite = params.end();
    //TODO: faire une fonction separee pour pouvoir la reutiliser et tester
    while (it != ite)
    {
      message.push_back(*it);
      it++;
    }
  }
  //Le message sera simplement "leaving"
  else
  {
    message.push_back("Leaving");
  }

  //On va sauvegarer tous les arguments qui suivent comme le message qui peut etre en differentes strings

  //On verifie que la channel existe bien le nom doit etre correct et la channel doit exister
  if (is_correct_channel_name(channel) == false || server->has_channel(channel) == false)
  {
    //NOSUCHCHANNEL
    error.push_back(channel);
    error_handler("403", user, NULL, error);
    return;
  }
  //On rececupere le pointeur sur la channel
  Channel *chan = server->find_channel(channel);

  //si il n est pas membre on retourne une erreur
  if (chan->user_is_member(user) == false)
  {
    //NOTONCHANNEL
    error.push_back(channel);
    error_handler("442", user, chan, error);
    return;
  }
  //TODO: Attention ici je fais un peu les choses en deux facons, faire des tests pour verifier que ce n est pas source d'erreur
  //si il est membre on quitte le channel
  chan->deleteMember(user);
  //On enleve la cannel de sa liste;
  user->remove_channel_from_list(chan);
  //Envoyer un message au serveur pour qu'il le transmette?
  return;
}