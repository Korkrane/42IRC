#include <IRC.hpp>

//TODO: Mettre d'autre valeur que null?
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
	set_creation(date);
}

IRC::~IRC()
{
	delete this->_commands;
#if DEBUG
	std::cout << BLUE << "DEBUG: IRC destructor called" << NC << std::endl;
#endif
}

void IRC::set_name(std::string name)
{
	this->_name = name;
}

void IRC::set_version(std::string version)
{
	this->_version = version;
}

void IRC::set_creation(std::string date)
{
	date.erase(date.size() - 1); //time command put a \n at the end of the date so i delete it here
	this->_server_creation = date;
}

void IRC::set_password(std::string password)
{
	this->_password = password;
}

std::string IRC::get_name(void)
{
	return (this->_name);
}

std::string IRC::get_version(void)
{
	return (this->_version);
}

std::string IRC::get_password(void)
{
	return (this->_password);
}

int IRC::get_socket(void)
{
	return (this->_socket);
}

std::string IRC::get_server_creation(void)
{
	return (this->_server_creation);
}

User *IRC::get_user(int fd)
{
	for (std::vector<User *>::iterator it = _users.begin(); it != _users.end(); ++it)
		if ((*it)->get_socket() == fd)
			return *it;
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
		while (itc != this->_commands->_cmds.end())
		{
			if (itc->first == (*it)._command_name)
			{
				/*
#if DEBUG
				int i = 0;
				std::vector<std::string> t = user->get_params();
				for (std::vector<std::string>::iterator itr = t.begin(); itr != t.end(); itr++)
				{
					std::cout << YELLOW << "param(" << i << ")= " << *itr << NC << std::endl;
					i++;
				}
#endif
*/
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

//when a user request a /quit, remove it from chans and delete the User instance.
void IRC::delete_user(int fd)
{
#if DEBUG
	std::cout << RED << "ENTER IN DELETE_USER\n" << NC;
#endif
	User *user = this->get_user(fd);

	std::vector<Channel *> chans = this->get_channels();
	for (std::vector<Channel *>::iterator it = chans.begin(); it != chans.end(); it++)
	{
		//delete in members vector channel
		if ((*it)->user_is_member(user))
			(*it)->deleteMember(user);
		//delete in operators vector channel
		if ((*it)->user_is_operator(user))
		{
			(*it)->delete_operator(user);
			// TODO add new operator randomly if it was the only operator in the chan
		}
		//delete in owner if he it was him
		if ((*it)->user_is_owner(user))
			(*it)->delete_owner();
	}
	std::vector<User *> us = this->get_users();

	std::vector<User *>::iterator t= std::find(us.begin(), us.end(), user);
			std::cout << "gonna erase:" << *t << std::endl;

	us.erase(std::find(us.begin(), us.end(), user));
	delete user;
#if DEBUG
	std::cout << RED << "EXIT IN DELETE_USER\n" << NC;
#endif
}

void IRC::process_command(t_clientCmd const &command, std::vector<t_clientCmd> &responseQueue, std::vector<int> &disconnectList)
{
#if DEBUG
	std::cout << BLUE << "\tDEBUG: with clientfd: " << command.first << NC << std::endl;
	std::cout << BLUE << "\tDEBUG: with command: " << command.second << NC;
#endif

	int clientFD = command.first;
	std::string const &cmd = command.second;
	User *current_user;

	if (!(std::find(fds.begin(), fds.end(), clientFD) == fds.end()))
	{
		#if DEBUG
			std::cout << BLUE << "DEBUG: Client found in the user list" << NC << std::endl;
			//std::cout << BLUE << "DEBUG: Client is registered ? " << current_user->user_is_registered() << NC << std::endl;
		#endif
		current_user = this->get_user(clientFD);
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
			//Si on a eu une commande quit
			if (current_user->_to_delete == true)
				disconnectList.push_back(clientFD);
		}
	}
	else //SI PREMIERE FOIS QU'IL SE CONNECTE
	{
#if DEBUG
		std::cout << BLUE << "\tDEBUG: Client first connection" << NC << std::endl;
#endif
		this->fds.push_back(clientFD);
		this->_users.push_back(new User(clientFD));
		current_user = _users.back();

		current_user->set_unparsed_client_command(cmd);
		current_user->split_if_multiple_command();
		this->exec_command(current_user);
#if DEBUG
		std::cout << BLUE << "DEBUG: Client is registered after exec?" << current_user->user_is_registered() << NC << std::endl;
#endif
		if (current_user->user_is_registered() == true)
			this->_commands->welcome_cmd(current_user, this);
		responseQueue = this->_response_queue; //leaks ici
		this->_response_queue.clear();
	}
}


Channel *IRC::add_channel(std::string channel, std::string opt_key)
{
	//On verifie que la channel ne fait pas deja partie de la liste
	Channel *find = this->find_channel(channel);
	if (find)
	{
		#if DEBUG
			std::cout << PURPLE << "DEBUG: IRC: add_channel function called but the channel already exists." << NC << std::endl;
		#endif
		//TODO attention a faire des checks au cas ou je renvois NULL
		return (NULL);
	}
	//TODO On verifie que le serveur n a pas deja trop de channels ?
	Channel *chan = new Channel(channel, opt_key, 0);
	this->_channels.push_back(chan);
	return chan;
}

Channel *IRC::add_channel(std::string channel, std::string opt_key, User *user)
{
	//On verifie que la channel ne fait pas deja partie de la liste
	Channel *find = this->find_channel(channel);
	if (find)
	{
		#if DEBUG
			std::cout << PURPLE << "DEBUG: IRC: add_channel function called but the channel already exists." << NC << std::endl;
		#endif
		//TODO: attention a faire des checks au cas ou je renvois NULL
		return (NULL);
	}
	//TODO On verifie que le serveur n a pas deja trop de channels ?
	Channel *chan = new Channel(channel, opt_key, user);
	this->_channels.push_back(chan);
	return chan;
}

std::vector<User *> IRC::get_users(void)
{
	return (this->_users);
}

std::vector<Channel *> IRC::get_channels(void)
{
	return (this->_channels);
}

void IRC::displayServerChannels(void)
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


void IRC::displayServerUsers(void)
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


bool IRC::has_channel(std::string channel_name)
{
	std::vector<Channel *> chans = this->get_channels();
	std::vector<Channel *>::iterator it = chans.begin();
	std::vector<Channel *>::iterator ite = chans.end();
	std::string check_name;
	while (it != ite)
	{
		check_name = (*it)->get_name();
		if (check_name.compare(channel_name) == 0)
			return (true);
		it++;
	}
	return (false);
}

Channel *IRC::find_channel(std::string channel_name)
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
			std::cout << BLUE << "DEBUG: IRC: found channel" << channel_name << ", returning ptr" << NC << std::endl;
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
			return (true);
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
			return (it);
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

User *IRC::get_user_ptr(std::string name)
{
	for (std::vector<User *>::iterator it = _users.begin(); it != _users.end(); ++it)
	{
		if ((*it)->get_nickname() == name)
			return *it;
	}
	return (NULL);
}

Channel *IRC::get_channel_ptr(std::string name)
{
	for (std::vector<Channel *>::iterator it = _channels.begin(); it != _channels.end(); ++it)
	{
		if ((*it)->get_name() == name)
			return *it;
	}
	return (NULL);
}

bool IRC::user_can_join(Channel *channel)
{
	unsigned int user_nb = channel->get_members_nb();

	if (user_nb >= USER_MAXCHAN)
	{
#if DEBUG
		std::cout << RED << "DEBUG: userCan not join new channel because he reach USER_MAXCHAN" << NC << std::endl;
#endif
		return (false);
	}
	return (true);
}

int IRC::send_rpl(std::string code, User *user, std::vector<std::string> params, std::string command)
{
	std::string rpl = this->build_reply(code, user, params, command);
	this->_response_queue.push_back(std::make_pair(user->get_socket(), rpl));
	return (0);
}

int IRC::send_rpl_to_all_members(std::string code, std::vector<User*> users, std::vector<std::string> params, std::string command)
{
	std::vector<User *>::iterator it = users.begin();
	std::vector<User *>::iterator ite = users.end();
	while (it != ite)
	{
		std::string rpl = this->build_reply(code, (*it), params, command);
		this->_response_queue.push_back(std::make_pair((*it)->get_socket(), rpl));
		it++;
	}
	return (0);
}

unsigned int	IRC::get_channel_nb(void)
{
	unsigned int number = 0;
	std::vector<Channel *> chans = this->get_channels();
	number = chans.size();
	#if DEBUG
		if (number >= SERVER_MAXCHAN)
		{
			std::cout << PURPLE << "DEBUG: IRC: " << "channel nb is exceeding !" << std::endl;
		}
	#endif
	return (number);
}

std::string		IRC::get_port(void)
{
	return (this->_port);
}

void			IRC::set_port(std::string port)
{
	this->_port = port;
}