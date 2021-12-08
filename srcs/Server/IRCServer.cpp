#include "irc.hpp"

/*
** Constructeurs
*/
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
	set_server_creation(date);
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

void				IRC::set_server_creation(std::string date)
{
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

int			IRC::get_socket(void) const
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
	std::cout << "DEBUG: " << "enter in exec_command with command:" << user->get_command_name() << std::endl;
	#endif
	std::map<std::string, void (*)(User *, IRC *)>::iterator it = this->_commands->_cmds.begin();
	int known_command = 0;

	while (it != this->_commands->_cmds.end())
	{
		if (it->first == user->get_command_name())
		{
#if DEBUG
			std::cout << GREEN << "DEBUG: " << it->first << " command is available in our IRC" << NC << std::endl;
#endif
			(*it->second)(user, this);
			known_command += 1;
			break;
		}
		it++;
	}
	if (known_command == 0)
	{
#if DEBUG
		std::cout << RED << "DEBUG: " << user->get_command_name() << " command isn't available in our IRC" << NC << std::endl;
#endif
		this->_commands->unknown_cmd(user, this);
	}
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
	int	clientFD = command.first;
	std::string const	&cmd = command.second;

	/*
	// Add even fds to the disconnect list
	if (cmd == _discEvenFD)
		for (std::vector<int>::const_iterator it = fds.begin(); it != fds.end(); ++it)
			if (*it % 2 == 0)
				disconnectList.push_back(*it);
	*/

	User *current_user;

	if (!(std::find(fds.begin(), fds.end(), clientFD) == fds.end()))
	{
		current_user = this->get_user(clientFD);
		#if DEBUG
			std::cout << BLUE << "DEBUG: Client found in the user list" << NC << std::endl;
			std::cout << BLUE << "DEBUG: Client is registered ? " << current_user->user_is_registered() << NC << std::endl;
		#endif
		current_user->set_unparsed_client_command(cmd);
		current_user->store_prefix();
		current_user->store_command();
		current_user->store_params();
		#if DEBUG
			current_user->display_command();
		#endif
		if(current_user->user_is_registered() == true)
		{
			this->exec_command(current_user);
			responseQueue = this->_response_queue;
			this->_response_queue.clear();
		}
		else
		{
			//TODO do check for pass and nick and realname existence to set it to a registered user.
			//if(!current_user->user_registered_password())
			//if(current_user->user_registered_password() && current_user->user_registered_nickname())
			current_user->set_registered_user(true);
			if(current_user->user_is_registered() == true)
			{
				current_user->set_command("WELCOME");
				this->exec_command(current_user);
				responseQueue = this->_response_queue;
				this->_response_queue.clear();
			}
		}
	}
	else
	{
		#if DEBUG
			std::cout << BLUE << "\tDEBUG: Client not found in the user list" << NC << std::endl;
		#endif
		this->fds.push_back(clientFD);
		current_user = new User(clientFD);
		current_user->set_nickname("user_nickname");
		current_user->set_realname("user_realname");
		current_user->set_hostname("ft_irc.com");
		this->_users.push_back(current_user);
	}
}

void IRC::add_channel(Channel *new_channel)
{
	this->_channels.push_back(new_channel);
}


//Ajout Mahaut - faire une fonction d'affichage + overloads ?
std::vector<User *>	IRC::get_users(void) const
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
void					IRC::displayServerChannels(void) const
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

void					IRC::displayServerUsers(void) const
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

bool				IRC::has_channel(std::string channel_name) const
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

Channel			*IRC::find_channel(std::string channel_name) const
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