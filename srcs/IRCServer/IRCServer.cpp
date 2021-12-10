#include <IRC.hpp>

IRC::IRC(void) : _socket(0),
				 _totChannels(0),
				 _totUsers(0),
				 _name("null"),
				 _password("null"),
				 _version("null"),
				 _server_creation("null"),
				 _svPassword("null")
{
#if DEBUG
	std::cout << BLUE << "DEBUG: IRC default constructor called" << NC << std::endl;
#endif
	_commands = new Commands();
}

/**
 * @brief Construct a new IRC:: IRC object
 *
 * @param port
 * @param password
 */
IRC::IRC(std::string const &password) : _socket(0),
										_totChannels(0),
										_totUsers(0),
										_channels(0),
										_name("null"),
										_password("null"),
										_version("null"),
										_server_creation("null"),
										_svPassword(password)
{
#if DEBUG
	std::cout << BLUE << "DEBUG: IRC constructor with pass parameter called" << NC << std::endl;
#endif
	_commands = new Commands();

	time_t now = time(0);
	std::string date = ctime(&now);
	//TODO: a reprendre ? Pb de compil Mahaut merge
	set_creation(date, now);
}

/**
 * @brief Destroy the IRC:: IRC object
 *
 */
IRC::~IRC()
{
	delete this->_commands;
#if DEBUG
	std::cout << BLUE << "DEBUG: IRC destructor called" << NC << std::endl;
#endif
	return;
}

/*
** Setters
*/
void IRC::set_name(std::string name)
{
	this->_name = name;
#if DEBUG
	std::cout << "Name has been set successfully to " << name << std::endl;
#endif
	return;
}

/**
** TODO: checker si les chaine sont correctes (voir rfc)
** pour l'ensemble des attributs membres
*/
void IRC::set_version(std::string version)
{
	this->_version = version;
#if DEBUG
	std::cout << "Version has been set successfully to " << version << std::endl;
#endif
	return;
}

//TODO: A reprendre ? Pb compil merge Mahaut
void IRC::set_creation(std::string date, time_t time)
{
	(void)time;
	date.erase(date.size() - 1); //time command put a \n at the end of the date so i delete it here
	this->_server_creation = date;
#if DEBUG
	std::cout << "Creation date has been set successfully to " << date << std::endl;
#endif
	return;
}

void IRC::set_password(std::string password)
{
	this->_password = password;
#if DEBUG
	std::cout << "password has been set successfully to " << password << std::endl;
#endif
	return;
}

/*
** Getters
*/
std::string IRC::get_name(void) const
{
	std::string name = this->_name;
#if DEBUG
	std::cout << "IRC version is " << _version << std::endl;
#endif
	return (name);
}

std::string IRC::get_version(void) const
{
	std::string version = this->_version;
#if DEBUG
	std::cout << "IRC version is " << version << std::endl;
#endif
	return (version);
}

std::string IRC::get_password(void) const
{
	std::string password = this->_password;
#if DEBUG
	std::cout << "IRC password is " << password << std::endl;
#endif
	return (password);
}

int IRC::get_socket(void) const
{
	int socket = this->_socket;
#if DEBUG
	std::cout << "IRC socket is " << socket << std::endl;
#endif
	return (socket);
}

std::string IRC::get_server_creation(void) const
{
	std::string server_creation = this->_server_creation;
#if DEBUG
	std::cout << BLUE << "IRC_DEBUG: IRC creation is " << server_creation << NC << std::endl;
#endif
	return (server_creation);
}

User *IRC::get_user(int fd)
{
	for (std::vector<User *>::iterator it = _users.begin(); it != _users.end(); ++it)
	{
		if ((*it)->get_socket() == fd)
			return *it;
	}
	return NULL;
}

void IRC::exec_command(User *user)
{
#if DEBUG
	std::cout << RED << "ENTER IRC::exec_command" << NC << std::endl;
#endif
	std::map<std::string, void (*)(User *, IRC *)>::iterator itc = this->_commands->_cmds.begin();

	for (std::vector<t_cmd>::iterator it = user->_commands.begin(); it != user->_commands.end(); it++)
	{
		int known_command = 0;
		user->set_command((*it)._command_name);
		user->set_params((*it)._params);
		user->set_prefix((*it)._prefix);
		std::cout << user->get_command_name();
		std::cout << user->get_prefix();

		while (itc != this->_commands->_cmds.end())
		{
			if (itc->first == (*it)._command_name)
			{

#if DEBUG
				int i = 0;
				std::vector<std::string> t = user->get_params();
				for (std::vector<std::string>::iterator itr = t.begin(); itr != t.end(); itr++)
				{
					std::cout << YELLOW << "param(" << i << ")= " << *itr << NC << std::endl;
					i++;
				}
#endif

				(*itc->second)(user, this);
				known_command += 1;
				break;
			}
			itc++;
		}
		if (known_command == 0)
			this->_commands->unknown_cmd(user, this);
		user->get_params().clear();
	}
	user->_commands.clear();
	user->set_command("");
	user->set_prefix("");
	user->_params.clear();
#if DEBUG
	std::cout << RED << "EXIT IRC::exec_command" << NC << std::endl;
#endif
}

void IRC::process_command(t_clientCmd const &command, std::vector<t_clientCmd> &responseQueue, std::vector<int> &disconnectList)
{

	(void)responseQueue;
	(void)disconnectList;

#if DEBUG
	std::cout << BLUE << "\tDEBUG: Enter in IRC::ProcessCommand" << NC << std::endl;
	std::cout << BLUE << "\tDEBUG: with clientfd: " << command.first << NC << std::endl;
	std::cout << BLUE << "\tDEBUG: with command: " << command.second << NC;
#endif

	int clientFD = command.first;
	std::string const &cmd = command.second;
	User *current_user;

	if (!(std::find(fds.begin(), fds.end(), clientFD) == fds.end()))
	{
		current_user = this->get_user(clientFD);
#if DEBUG
		std::cout << BLUE << "DEBUG: Client found in the user list" << NC << std::endl;
		std::cout << BLUE << "DEBUG: Client is registered ? " << current_user->user_is_registered() << NC << std::endl;
#endif
		current_user->set_unparsed_client_command(cmd);
		current_user->split_if_multiple_command();
		//SI CLIENT CONNECTE MAIS PAS ENCORE REGISTER CONTINUE FONCTION DE REGISTRATION
		if ((current_user->_commands[0]._command_name == "NICK" || current_user->_commands[0]._command_name == "PASS" || current_user->_commands[0]._command_name == "USER") && !current_user->user_is_registered())
		{
			this->exec_command(current_user);
			if (current_user->user_is_registered() == true)
				this->_commands->welcome_cmd(current_user, this);
			responseQueue = this->_response_queue;
			this->_response_queue.clear();
		} //SI DEJA CO ET REGISTER ALORS EXEC LA COMMANDE
		else if (current_user->user_is_registered() == true)
		{
			this->exec_command(current_user);
			responseQueue = this->_response_queue;
			this->_response_queue.clear();
		}
	}
	else //SI PREMIERE FOIS QU'IL SE CONNECTE
	{
#if DEBUG
		std::cout << BLUE << "\tDEBUG: Client not found in the user list" << NC << std::endl;
#endif
		this->fds.push_back(clientFD);
		current_user = new User(clientFD);

		current_user->set_unparsed_client_command(cmd);
		current_user->split_if_multiple_command();
#if DEBUG
		std::cout << BLUE << "DEBUG: Client is registered before exec ?" << current_user->user_is_registered() << NC << std::endl;
#endif
		this->exec_command(current_user);
#if DEBUG
		std::cout << BLUE << "DEBUG: Client is registered after exec?" << current_user->user_is_registered() << NC << std::endl;
#endif
		if (current_user->user_is_registered() == true)
			this->_commands->welcome_cmd(current_user, this);
		responseQueue = this->_response_queue;
		this->_response_queue.clear();
		this->_users.push_back(current_user);
	}
}

/**
 * @brief
 *
 * @param new_channel
 * TODO: verifier que la channel ne fait pas deja partie de la liste
 */
Channel *IRC::add_channel(std::string channel, std::string opt_key)
{
	Channel *chan = new Channel(channel, opt_key);
	this->_channels.push_back(chan);
	return chan;
}

//Ajout Mahaut - faire une fonction d'affichage + overloads ?
std::vector<User *> IRC::get_users(void) const
{
	std::vector<User *> users;
	users = this->_users;
#if DEBUG
	std::cout << "get_users function called" << std::endl;
#endif
	return (users);
}

/**
 * @brief
 *
 * @return std::vector<Channel *>
 */
std::vector<Channel *> IRC::get_channels(void) const
{
#if DEBUG
	std::cout << BLUE << "DEBUG: "
			  << "get_channels function called" << std::endl;
#endif
	return (this->_channels);
}

/**
 * @brief
 * TODO: a tester
 */
void IRC::displayServerChannels(void) const
{
	std::vector<Channel *> channels = get_channels();
	std::vector<Channel *>::iterator it = channels.begin();
	std::vector<Channel *>::iterator ite = channels.end();

	std::cout << "Displaying all current server channels" << std::endl;
	while (it != ite)
	{
		std::cout << (*it)->get_name() << std::endl;
		it++;
	}
}

void IRC::displayServerUsers(void) const
{
	std::vector<User *> users = get_users();
	std::vector<User *>::iterator it = users.begin();
	std::vector<User *>::iterator ite = users.end();

	std::cout << "Displaying all current server channels" << std::endl;
	while (it != ite)
	{
		std::cout << (*it)->get_nickname() << std::endl;
		it++;
	}
}

bool IRC::has_channel(std::string channel_name) const
{
	std::vector<Channel *> chans = this->get_channels();
	std::vector<Channel *>::iterator it = chans.begin();
	std::vector<Channel *>::iterator ite = chans.end();
	std::string check_name;
	while (it != ite)
	{
		check_name = (*it)->get_name();
		if (check_name.compare(channel_name) == 0)
		{
			return (true);
		}
		it++;
	}
	return (false);
}

Channel *IRC::find_channel(std::string channel_name) const
{
	(void)channel_name;
	std::vector<Channel *> chans = this->get_channels();
	std::vector<Channel *>::iterator it = chans.begin();
	std::vector<Channel *>::iterator ite = chans.end();
	std::string check_name;
	while (it != ite)
	{
		check_name = (*it)->get_name();
		if (check_name.compare(channel_name) == 0)
		{
#if DEBUG
			std::cout << BLUE << "DEBUG: "
					  << "IRCServ: found channel, returning ptr" << std::endl;
#endif
			return (*it);
		}
		it++;
	}
	return (NULL);
}

/**
 * @brief
 *
 * @param to_drop
 * TODO: a tester
 */
void IRC::drop_channel(Channel *to_drop)
{
	(void)to_drop;
	if (!to_drop)
		return;
	//On cherche si le channel fait partie du vecteur
	std::vector<Channel *> chan = this->get_channels();

	bool res = find_channel(to_drop);
	//Si on le trouve, on l enleve du vecteur
	if (res == true)
	{
		std::vector<Channel *>::iterator it = this->get_channel_it(to_drop);
		chan.erase(it);
	}
	return;
}

bool IRC::find_channel(Channel *to_find)
{
	std::vector<Channel *> chan = this->get_channels();
	std::vector<Channel *>::iterator it = chan.begin();
	std::vector<Channel *>::iterator ite = chan.end();
	std::string check_name;
	std::string to_find_name = to_find->get_name();
	while (it != ite)
	{
		check_name = (*it)->get_name();
		if (to_find_name.compare(check_name) == 0)
		{
			return (true);
		}
		it++;
	}
	return (false);
}

std::vector<Channel *>::iterator IRC::get_channel_it(Channel *to_find)
{
	std::vector<Channel *> chan = this->get_channels();
	std::vector<Channel *>::iterator it = chan.begin();
	std::vector<Channel *>::iterator ite = chan.end();
	std::string check_name;
	std::string to_find_name = to_find->get_name();
	while (it != ite)
	{
		check_name = (*it)->get_name();
		if (to_find_name.compare(check_name) == 0)
		{
			return (it);
		}
		it++;
	}
	//Sera superieur a end si il n est pas trouve ?
	it++;
	return (it);
}

bool IRC::find_user(std::string nickname)
{
	bool res = false;
	std::vector<User *> users;
	users = this->get_users();
	std::vector<User *>::iterator it = users.begin();
	std::vector<User *>::iterator ite = users.end();
	std::string tmp;
	while (it != ite)
	{
		tmp = (*it)->get_nickname();
		if (nickname.compare(tmp) == false)
		{
			res = true;
			break;
		}
		it++;
	}
	return (res);
}

//TODO: A tester
User *IRC::get_user_ptr(std::string nick)
{
	(void)nick;

	for (std::vector<User *>::iterator it = _users.begin(); it != _users.end(); ++it)
	{
		if ((*it)->get_nickname() == nick)
			return *it;
	}
	return (NULL);
}

bool IRC::user_can_join(Channel *channel)
{
	unsigned int user_nb = channel->get_members_nb();

	if (user_nb >= USER_MAXCHAN)
	{
#if USERDEBUG
		std::cout << BLUE << "USERDEBUG: USER :"
				  << "Can not join new channel" << std::endl;
#endif
		return (false);
	}
	return (true);
}

void IRC::send_rpl_to_all_members(Channel *channel, std::string rpl)
{
	std::vector<User *> members = channel->get_members();
	std::vector<User *>::iterator it = members.begin();
	std::vector<User *>::iterator ite = members.end();
	User *user = (*it);
	while (it != ite)
	{
		this->_response_queue.push_back(std::make_pair(user->get_socket(), rpl));
		it++;
	}
	return;
}

void IRC::send_rpl(std::string error_code, User *user, Channel *channel, std::string arg)
{
	unsigned int code;

	(void)channel;
	code = atoi(error_code.c_str());
	std::string rpl;
	switch (code)
	{
	case 1:
	{
		rpl += "Welcome to the Internet Relay Network " + user->get_nickname() + "\r\n";
		break;
	}
	case 2:
	{
		rpl += "Your host is " + user->get_server_name() + ", running on version [1]\r\n";
		break;
	}
	case 3:
	{
		rpl += "This server was created " + user->get_server()->get_server_creation() + "\r\n";
		break;
	}
	case 4:
	{
		rpl += user->get_server_name() + " version [1]. Available user MODE : +Oa . Avalaible channel MODE : none. \r\n";
		break;
	}
	case 5:
	{
		rpl += "Sorry IRC's capacity is full. Please retry connection later\r\n";
		break;
	}
	case 221: //RPL_UMODEIS
	{
		if (user->user_is_operator() == false || user->user_is_away())
			rpl += user->get_nickname() + " :no mode set";
		else
			rpl += user->get_nickname() + " :active mode +";
		if (user->user_is_away() == true)
			rpl += "a";
		if (user->user_is_away() == true)
			rpl += "O";
		rpl += "\r\n";
		break;
	}
	case 301: //RPL_AWAY
	{
		rpl += (arg + "\r\n");
		break;
	}
	case 305: //RPL_UNAWAY
	{
		rpl += "You are no longer marked as being away\r\n";
		break;
	}
	case 306: //RPL_NOWAWAY
	{
		rpl += "You have been marked as being away\r\n";
		break;
	}
	case 315: //RPL_ENDWHO
	{
		if (arg.empty())
			rpl += user->get_server_name();
		else
			rpl += arg;
		rpl += " :End of WHO list\r\n";
		break;
	}
	case 322: //RPL_LIST
	{
		rpl += (user->get_server_name() + " :" + channel->get_topic() + "\r\n");
		break;
	}
	case 323: //RPL_LISTEND
	{
		rpl += " :End of LIST\r\n";
		break;
	}
	case 331: //RPL_NOTOPIC
	{
		rpl += (channel->get_name() + " :No topic is set\r\n");
		break;
	}
	case 332: //RPL_TOPIC
	{
		rpl += (channel->get_name() + " :" + channel->get_topic() + "\r\n");
		break;
	}
	//TODO: a tester
	case 341:
	{
		rpl = init_rpl(user);
		rpl += channel->get_name();
		rpl += " " + user->get_nickname();
		rpl += "\r\n";
		break;
	}
	case 352: //RPL_WHO
	{
		rpl = ":127.0.0.1 " + error_code + " " + user->get_nickname() + " ";
		rpl += arg;
		break;
	}
	case 353: // RPL_NAMEREPLY
	{
		rpl = ":127.0.0.1 " + error_code + " " + user->get_nickname();
		rpl += (" = " + channel->get_name() + " :");
		std::vector<User *> tmp = channel->get_members();
		std::vector<User *>::iterator it = tmp.begin();
		std::vector<User *>::iterator ite = tmp.end();
		while (it != ite)
		{
			if (channel->user_is_operator(*it) == 1)
				rpl += "@";
			rpl += ((*it)->get_nickname() + " ");
			it++;
		}
		rpl += "\r\n";
		//std::cout << "rpl: |" << rpl << "|" << std::endl;
		break;
	}
	case 366: // ENDOFNAMES
	{
		rpl = ":127.0.0.1 " + error_code + " " + user->get_nickname() + " ";
		if (channel)
			rpl += channel->get_name();
		else
			rpl += arg;
		rpl += " :End of NAMES list\r\n";
		break;
	}
	case 375:
	{
		rpl += ":- " + user->get_server_name() + " Message of the day - \r\n";
		break;
	}
	case 376:
	{
		rpl += ":End of MOTD command\r\n";
		break;
	}
	case 381: // YOUREOPER
	{
		rpl += "You are now an IRC operator\r\n";
		break;
	}
	case 4242:
	{
		rpl += ":" + user->get_server_name() + " " + error_code + " " + user->get_nickname() + " :";
		rpl = "[CAP] : IRC_90'S does not handle capabilities\r\n";
		break;
	}
	case 4243:
	{
		rpl += user->get_nickname() + ": sets mode " + arg + " on " + user->get_nickname() + "\r\n";
		break;
	}
	case 4244: // customhelp
	{
		// Liste des commandes dispo sur notre IRC
		rpl += "Available commands:\n";
		rpl += "---> Globales: NICK | OPER | MODE | WHO | AWAY | HELP | KILL | QUIT \n";
		rpl += "---> On Channels: JOIN | PART | TOPIC | NAMES | LIST | KICK\n";
		rpl += "---> To send messages: PRIVMSG | NOTICE";
		rpl += "\r\n";
		break;
	}
	case 4245:
	{
		rpl += arg + "\r\n";
		break;
	}
	default:
	{
		rpl = "No RPL set \r\n";
		break;
	}
	}
	//Envoie du message a la queue du serveur
	this->_response_queue.push_back(std::make_pair(user->get_socket(), rpl));
	return;
}

std::string IRC::init_rpl(User *user)
{
	std::string rpl;
	rpl = ":" + user->get_nickname() + "!" + user->get_username() + "@" + "0";
	return rpl;
}