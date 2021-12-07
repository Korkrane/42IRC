#include <irc.hpp>

/*
** Constructeurs
*/
IRC::IRC(void):
	_socket(0),
	_port(PORT_SERVER),
	_totChannels(0),
	_totUsers(0),
	_name("null"),
	_password("null"),
	_version("null"),
	_userModes("null"),
	_channelModes("null"),
	_init_time(),
	_date("null"),
	_serv_info(NULL),
	_hints(NULL),
	_server_ip("null"),
	_server_creation("null"),
	_svPassword("null"),
	_discEvenFD("delete even\r\n")
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
 * TODO: implementer proprement
 */
IRC::IRC(std::string const &password):
	_socket(0),
	_port(PORT_SERVER),
	_totChannels(0),
	_totUsers(0),
	_name("null"),
	_password("null"),
	_version("null"),
	_userModes("null"),
	_channelModes("null"),
	_init_time(),
	_date("null"),
	_serv_info(NULL),
	_hints(NULL),
	_server_ip("null"),
	_server_creation("null"),
	_svPassword(password),
	_discEvenFD("delete even\r\n")
{
	//gerer les attributs membres relatifs au temps
	//initialiser hints
#if DEBUG
	std::cout << BLUE << "DEBUG: IRC constructor with pass parameter called" << NC << std::endl;
#endif
	_commands = new Commands();
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

void				IRC::set_creation(std::string date, time_t time)
{
	this->_date = date;
    this->_init_time = time;
#if DEBUG
	std::cout << "Creation date has been set successfully to " << date << std::endl;
#endif
	return ;
}

void				IRC::set_port(int port)
{
	this->_port = port;
#if DEBUG
	std::cout << "port has been set successfully to " << port << std::endl;
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

int			IRC::get_port(void) const
{
	int port = this->_port;
#if DEBUG
	std::cout << "IRC port is " << port << std::endl;
#endif
	return (port);
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

struct addrinfo*			IRC::get_serv_info(void) const
{
    struct addrinfo* serv_info = this->_serv_info;
	return (serv_info);
}

std::string			IRC::get_ip(void) const
{
	std::string ip = this->_server_ip;
#if DEBUG
	std::cout << "IRC ip is " << ip << std::endl;
#endif
	return (ip);
}

std::string			IRC::get_server_creation(void) const
{
	std::string server_creation = this->_server_creation;
#if DEBUG
	std::cout << "IRC creation is " << server_creation << std::endl;
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
	#if DEBUG
		std::cout << BLUE << "DEBUG: fail to get user in list " << NC << std::endl;
	#endif
	return NULL;
}

void IRC::exec_command(User *user)
{
#if DEBUG
	std::cout << "IRC::exec_command function called." << std::endl;
 #endif
	std::map<std::string, void (*)(User *, IRC *)>::iterator it = this->_commands->_cmds.begin();
	int known_command = 0;

	while (it != this->_commands->_cmds.end())
	{
		if (it->first == user->get_command_name())
		{
#if DEBUG
			std::cout << GREEN << "DEBUG: " << it->first << " execute the command -->" << NC << std::endl;
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
		std::cout << RED << "DEBUG: " << user->get_command_name() << " return the error command -->" << NC << std::endl;
#endif
		this->_commands->unknown_cmd(user, this);
	}
}

void IRC::ProcessCommand(t_clientCmd const &command, std::vector<t_clientCmd> &responseQueue, std::vector<int> &disconnectList)
{
	#if DEBUG
		std::cout << BLUE << "\tDEBUG: Enter in IRC::ProcessCommand" << NC << std::endl;
		std::cout << BLUE << "\tDEBUG: with clientfd: " << command.first << NC << std::endl;
		std::cout << BLUE << "\tDEBUG: with command: " << command.second << NC;
	#endif
	int	clientFD = command.first;
	std::string const	&cmd = command.second;


	for (std::vector<int>::const_iterator it = fds.begin(); it != fds.end(); ++it)
		if (*it != clientFD)
			responseQueue.push_back(std::make_pair(*it, cmd));


	// Add even fds to the disconnect list
	if (cmd == _discEvenFD)
		for (std::vector<int>::const_iterator it = fds.begin(); it != fds.end(); ++it)
			if (*it % 2 == 0)
				disconnectList.push_back(*it);

	//TODO
	//if new user --> do registration
	//if user is a valid client --> parse the incoming command
	  //process the command
	  //build reply
	  //put reply to responseQueue


	//Check if the Client has already been created. If yes parse and execute his command
	//otherwise, create a new client //TODO execute command too
	User *current_user;

	if (!(std::find(fds.begin(), fds.end(), clientFD) == fds.end()))
	{
		#if DEBUG
			std::cout << BLUE << "DEBUG: Client found in the user list" << NC << std::endl;
		#endif
		current_user = this->get_user(clientFD);
		current_user->set_unparsed_client_command(cmd);
		current_user->store_prefix();
		current_user->store_command();
		current_user->store_params();
		#if DEBUG
			current_user->display_command();
		#endif
		this->exec_command(current_user);
	}
	else
	{
		#if DEBUG
			std::cout << BLUE << "\tDEBUG: Client not found in the user list" << NC << std::endl;
		#endif
		this->fds.push_back(clientFD);
		current_user = new User(clientFD);
		current_user->set_nickname("test");
		this->_users.push_back(current_user);
		//parse command
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
	Channel *chan = NULL;
	(void)channel_name;
	return (chan);
}