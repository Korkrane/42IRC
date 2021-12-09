#include <IRC.hpp>

IRC::IRC(void):
	_socket(0),
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
IRC::IRC(std::string const &password):
	_socket(0),
	_totChannels(0),
	_totUsers(0),
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

	time_t      now    = time(0);
    std::string date   = ctime(&now);
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
void				IRC::set_name(std::string name)
{
	this->_name = name;
#if DEBUG
	std::cout << "Name has been set successfully to " << name << std::endl;
#endif
	return ;
}

/**
** TODO: checker si les chaine sont correctes (voir rfc)
** pour l'ensemble des attributs membres
*/
void				IRC::set_version(std::string version)
{
	this->_version = version;
#if DEBUG
	std::cout << "Version has been set successfully to " << version << std::endl;
#endif
	return ;
}

//TODO: A reprendre ? Pb compil merge Mahaut
void				IRC::set_creation(std::string date, time_t time)
{
	(void)time;
	date.erase(date.size() - 1); //time command put a \n at the end of the date so i delete it here
	this->_server_creation = date;
#if DEBUG
	std::cout << "Creation date has been set successfully to " << date << std::endl;
#endif
	return ;
}

void				IRC::set_password(std::string password)
{
	this->_password = password;
#if DEBUG
	std::cout << "password has been set successfully to " << password << std::endl;
#endif
	return ;
}

/*
** Getters
*/
std::string			IRC::get_name(void) const
{
	std::string name = this->_name;
#if DEBUG
	std::cout << "IRC version is " << _version << std::endl;
#endif
	return (name);
}

std::string			IRC::get_version(void) const
{
	std::string version = this->_version;
#if DEBUG
	std::cout << "IRC version is " << version << std::endl;
#endif
	return (version);
}

std::string			IRC::get_password(void) const
{
	std::string password = this->_password;
#if DEBUG
	std::cout << "IRC password is " << password << std::endl;
#endif
	return (password);
}

int					IRC::get_socket(void) const
{
	int socket = this->_socket;
#if DEBUG
	std::cout << "IRC socket is " << socket << std::endl;
#endif
	return (socket);
}

std::string			IRC::get_server_creation(void) const
{
	std::string server_creation = this->_server_creation;
#if DEBUG
	std::cout << BLUE << "IRC_DEBUG: IRC creation is " << server_creation << NC << std::endl;
#endif
	return (server_creation);
}

User* IRC::get_user(int fd)
{
	for (std::vector<User *>::iterator it = _users.begin(); it != _users.end(); ++it)
	{
		if((*it)->get_socket() == fd)
			return *it;
	}
	return NULL;
}

void IRC::exec_command(User *user)
{
	#if DEBUG
	std::cout  << RED << "ENTER IRC::exec_command" << NC << std::endl;
	#endif
	std::map<std::string, void (*)(User *, IRC *)>::iterator itc = this->_commands->_cmds.begin();

	for(std::vector<t_cmd>::iterator it = user->_commands.begin(); it != user->_commands.end(); it++)
	{
		int known_command = 0;
		user->set_command((*it)._command_name);
		user->set_params((*it)._params);
		user->set_prefix((*it)._prefix);
		while (itc != this->_commands->_cmds.end())
		{
			if (itc->first == (*it)._command_name)
			{
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
		std::cout  << RED << "EXIT IRC::exec_command" << NC << std::endl;
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

	int					clientFD = command.first;
	std::string const	&cmd = command.second;
	User 				*current_user;

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
		if((current_user->_commands[0]._command_name == "NICK" || current_user->_commands[0]._command_name == "PASS" || current_user->_commands[0]._command_name == "USER") && !current_user->user_is_registered())
		{
			this->exec_command(current_user);
			if(current_user->user_is_registered() == true)
				this->_commands->welcome_cmd(current_user, this);
			responseQueue = this->_response_queue;
			this->_response_queue.clear();
		}//SI DEJA CO ET REGISTER ALORS EXEC LA COMMANDE
		else if(current_user->user_is_registered() == true)
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
		if(current_user->user_is_registered() == true)
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
void 					IRC::add_channel(Channel *new_channel)
{
	this->_channels.push_back(new_channel);
}


//Ajout Mahaut - faire une fonction d'affichage + overloads ?
std::vector<User *>		IRC::get_users(void) const
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
std::vector<Channel *>	IRC::get_channels(void) const
{
	std::vector<Channel *> chans;
	chans = this->_channels;
#if DEBUG
	std::cout << BLUE << "DEBUG: " << "get_channels function called" << std::endl;
#endif
	return (chans);
}

/**
 * @brief
 * TODO: a tester
 */
void						IRC::displayServerChannels(void) const
{
	std::vector<Channel *>channels = get_channels();
	std::vector<Channel *>::iterator it = channels.begin();
	std::vector<Channel *>::iterator ite = channels.end();

	std::cout << "Displaying all current server channels" << std::endl;
	while (it != ite)
	{
		std::cout << (*it)->get_name() << std::endl;
		it++;
	}
}

void						IRC::displayServerUsers(void) const
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

bool						IRC::has_channel(std::string channel_name) const
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

Channel						*IRC::find_channel(std::string channel_name) const
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
			std::cout << BLUE << "DEBUG: " << "IRCServ: found channel, returning ptr" << std::endl;
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
void							IRC::drop_channel(Channel *to_drop)
{
	(void)to_drop;
	if (!to_drop)
		return ;
	//On cherche si le channel fait partie du vecteur
	std::vector<Channel *> chan = this->get_channels();

	bool res = find_channel(to_drop);
	//Si on le trouve, on l enleve du vecteur
	if (res == true)
	{
		std::vector<Channel *>::iterator it = this->get_channel_it(to_drop);
		chan.erase(it);
	}
	return ;
}

bool							IRC::find_channel(Channel *to_find)
{
	std::vector<Channel *> chan = this->get_channels();
	std::vector<Channel *>::iterator it = chan.begin();
	std::vector<Channel *>::iterator ite = chan.end();
	std::string check_name;
	std::string	to_find_name = to_find->get_name();
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

std::vector<Channel *>::iterator	IRC::get_channel_it(Channel *to_find)
{
	std::vector<Channel *> chan = this->get_channels();
	std::vector<Channel *>::iterator it = chan.begin();
	std::vector<Channel *>::iterator ite = chan.end();
	std::string check_name;
	std::string	to_find_name = to_find->get_name();
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

bool								IRC::find_user(std::string nickname)
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
User								*IRC::get_user_ptr(std::string nick)
{
	(void)nick;

	for (std::vector<User *>::iterator it = _users.begin(); it != _users.end(); ++it)
	{
		if((*it)->get_nickname() == nick)
			return *it;
	}
	return (NULL);
}