#include <IRC.hpp>
void Commands::loop_part(User *user, IRC *server, std::string bye_message, unsigned int index)
{
  (void)user;
  (void)server;

  std::vector<std::string> error;
  std::vector<std::string> params = user->get_params();
  std::string channel;

  channel = user->_splitted_channels[index];
  //On verifie que la channel existe bien le nom doit etre correct et la channel doit exister
  if (is_correct_channel_name(channel) == false || server->has_channel(channel) == false)
  {
    error.push_back(channel);
    return (return_error("403", user, server, error, ""));
  }
  //On rececupere le pointeur sur la channel
  Channel *chan = server->find_channel(channel);

  //si il n est pas membre on retourne une erreur
  if (chan->user_is_member(user) == false)
  {
    error.push_back(channel);
    return (return_error("442", user, server, error, ""));
  }
  user_parts(user, server, chan, index, bye_message);
  return;
}

void Commands::part(User *user, IRC *server)
{
  //Preparation du serveur d'arguments en cas d'ereur
  std::vector<std::string> error;
  std::vector<std::string> params = user->get_params();
  std::string channel;
  std::string bye_message;
  unsigned int size = params.size();

  //Preparation du bye message
  get_channel_targets(user, server);
  bye_message = get_bye_message(user, server);
  if (bye_message.empty())
    bye_message = "Leaving";

  // Verifier le nombre d'argument, si il est egal a 1, renvoyer une erreur
  if (size == 1)
  {
    error.push_back(user->get_command_name());
    return (return_error("461", user, server, error, ""));
  }

  unsigned int max = user->_splitted_channels.size();
  unsigned int index = 0;

  while (index < max)
  {
    loop_part(user, server, bye_message, index);
    index++;
  }
  user->_splitted_channels.clear();
  return;
}

void Commands::user_parts(User *user, IRC *server, Channel *chan, int index, std::string bye_message)
{
  if (chan)
  {
    std::vector<std::string> chan_vec;

    chan_vec.push_back(user->get_nickname());
    chan_vec.push_back(user->get_username());

    chan_vec.push_back(user->_splitted_channels[index]);
    chan_vec.push_back(bye_message);

    //server->send_rpl_to_all_members("", chan->get_members(), chan_vec, "PART");
    std::vector<User *> users = chan->get_members();
    std::vector<User *>::iterator it = users.begin();
    std::vector<User *>::iterator ite = users.end();
    while (it != ite)
    {
      server->send_rpl("", (*it), chan_vec, "PART");
      it++;
    }

    chan_vec.clear();
    chan->deleteMember(user);
    //On enleve la cannel de sa liste;
    //bool is_owner = chan->user_is_owner(user);
    user->remove_channel_from_list(chan);
    unsigned int members = chan->get_members_nb();
    if (members == 0)
    {
      std::vector<Channel *> chans = server->get_channels();
      std::vector<Channel *>::iterator it = chans.begin();
      std::vector<Channel *>::iterator ite = chans.end();

      while (it != ite)
      {
        if ((*it) == chan)
        {
          chans.erase(it);
        }
        it++;
      }
      //server->drop_channel(chan);
      //delete chan;
    }
  }
  //si il est membre on quitte le channel enlever de sa liste channel, le retirer de la liste des users de la channel
  //Si c etait le owner qu il n y a pas plus personne il faut la retirer du serveur
  return;
}