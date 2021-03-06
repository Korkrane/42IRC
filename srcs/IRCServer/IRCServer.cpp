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
#if DEBUG == 1
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
#if DEBUG == 1
	std::cout << BLUE << "DEBUG: IRC constructor with pass parameter called" << NC << std::endl;
#endif
	die = false;
	_commands = new Commands();
	time_t now = time(0);
	std::string date = ctime(&now);
	set_creation(date);
}

IRC::~IRC()
{
	delete _commands;
#if DEBUG == 1
	std::cout << BLUE << "DEBUG: IRC destructor called" << NC << std::endl;
#endif
}

void IRC::set_name(std::string name)
{
	_name = name;
}

void IRC::set_version(std::string version)
{
	_version = version;
}

void IRC::set_creation(std::string date)
{
	date.erase(date.size() - 1); //time command put a \n at the end of the date so i delete it here
	_server_creation = date;
}

void IRC::set_password(std::string password)
{
	_password = password;
}

std::string IRC::get_name(void)
{
	return _name;
}

std::string IRC::get_version(void)
{
	return _version;
}

std::string IRC::get_password(void)
{
	return _password;
}

int IRC::get_socket(void)
{
	return _socket;
}

std::string IRC::get_server_creation(void)
{
	return _server_creation;
}

User *IRC::get_user(int fd)
{
	for (std::vector<User *>::iterator it = _users.begin(); it != _users.end(); ++it)
		if ((*it)->get_fd() == fd)
			return *it;
	return NULL;
}

void IRC::exec_command(User *user)
{
#if DEBUG == 1
	std::cout << RED << "ENTER IRC EXEC CMD" << NC << std::endl;
#endif
	int known_command = 0;
	for (std::vector<t_cmd>::iterator it = user->_commands.begin(); it != user->_commands.end(); it++)
	{
		user->set_command((*it)._command);
		user->set_params((*it)._params);
		user->set_prefix((*it)._prefix);
		std::map<std::string, void (*)(User *, IRC *)>::iterator itc = _commands->_cmds.begin();
		while (itc != _commands->_cmds.end())
		{
			if (itc->first == (*it)._command)
			{
				(*itc->second)(user, this);
				known_command++;
				break;
			}
			itc++;
		}
		if (known_command == 0)
			_commands->unknown_cmd(user, this);
		user->get_params().clear();
	}
	user->_commands.clear();
	user->set_command("");
	user->set_prefix("");
	user->_params.clear();
#if DEBUG == 1
	std::cout << RED << "EXIT IRC EXEC CMD" << NC << std::endl;
#endif
}

void IRC::delete_user(int fd)
{
#if DEBUG == 1
	std::cout << RED << "ENTER IN DELETE_USER" << NC << std::endl;
#endif
	User *user = this->get_user(fd);

	std::vector<Channel *> chans = this->get_channels();
	for (std::vector<Channel *>::iterator it = chans.begin(); it != chans.end(); it++)
	{
		if ((*it)->user_is_member(user))
			(*it)->deleteMember(user);
		if ((*it)->user_is_operator(user))
			(*it)->delete_operator(user);
		if ((*it)->user_is_owner(user))
			(*it)->delete_owner();
	}
	_users.erase(std::find(_users.begin(), _users.end(), user));
	delete user;
#if DEBUG == 1
	std::cout << RED << "EXIT IN DELETE_USER" << NC << std::endl;
#endif
}

void IRC::process_command(t_clientCmd const &command, std::vector<t_clientCmd> &responseQueue, std::vector<int> &disconnectList)
{
#if DEBUG == 1
	std::cout << BLUE << "\tDEBUG: with clientfd: " << command.first << NC << std::endl;
	std::cout << BLUE << "\tDEBUG: with command: " << command.second << NC;
#endif

	int clientFD = command.first;
	std::string const &cmd = command.second;
	User *user;

	if (!(std::find(fds.begin(), fds.end(), clientFD) == fds.end()))
	{
#if DEBUG == 1
		std::cout << BLUE << "DEBUG: Client found in the user list" << NC << std::endl;
#endif
		user = this->get_user(clientFD);
		user->set_request(cmd);
		user->fill_commands_vector();
		//SI CLIENT CONNECTE MAIS PAS ENCORE REGISTER CONTINUE FONCTION DE REGISTRATION
		if ((user->_commands[0]._command == "NICK" || user->_commands[0]._command == "PASS" || user->_commands[0]._command == "USER") && !user->is_registered())
		{
			exec_command(user);
			if (user->is_registered() == true)
				_commands->welcome_cmd(user, this);
			responseQueue = _response_queue;
			_response_queue.clear();
		} //SI DEJA CO ET REGISTER ALORS EXEC LA COMMANDE
		else if (user->is_registered() == true)
		{
			exec_command(user);
			responseQueue = _response_queue;
			_response_queue.clear();
			if (user->_to_delete == true)
				disconnectList.push_back(clientFD);
		}
	}
	else //SI PREMIERE FOIS QU'IL SE CONNECTE
	{
#if DEBUG == 1
		std::cout << BLUE << "\tDEBUG: Client first connection" << NC << std::endl;
#endif
		fds.push_back(clientFD);
		_users.push_back(new User(clientFD));
		user = _users.back();

		user->set_request(cmd);
		user->fill_commands_vector();
		exec_command(user);

		if (user->is_registered() == true)
			_commands->welcome_cmd(user, this);
		responseQueue = _response_queue;
		_response_queue.clear();
	}
	disconnectList = _disconnect_list;
}

Channel *IRC::add_channel(std::string channel, User *user)
{
	Channel *chan = new Channel(channel, user);
	_channels.push_back(chan);
	_totChannels++;
	return chan;
}

std::vector<User *> IRC::get_users(void)
{
	return _users;
}

std::vector<Channel *> IRC::get_channels(void)
{
	return _channels;
}

void IRC::displayServerChannels(void)
{
#if DEBUG
	std::cout << BLUE << "DEBUG: Displaying all current server chans" << NC << std::endl;
#endif
	std::vector<Channel *> chans = get_channels();

	for (std::vector<Channel *>::iterator it = chans.begin(); it != chans.end(); it++)
		std::cout << (*it)->get_name() << std::endl;
}

void IRC::displayServerUsers(void)
{
#if DEBUG
	std::cout << BLUE << "DEBUG: Displaying all current server users" << NC << std::endl;
#endif
	std::vector<User *> users = get_users();

	for (std::vector<User *>::iterator it = users.begin(); it != users.end(); it++)
		std::cout << (*it)->get_nickname() << std::endl;
}

bool IRC::has_channel(std::string channel_name)
{
	std::vector<Channel *> chans = get_channels();

	for (std::vector<Channel *>::iterator it = chans.begin(); it != chans.end(); it++)
	{
		if ((*it)->get_name().compare(channel_name) == 0)
			return (true);
	}
	return (false);
}

Channel *IRC::find_channel(std::string channel_name)
{
	std::vector<Channel *> chans = get_channels();

	for (std::vector<Channel *>::iterator it = chans.begin(); it != chans.end(); it++)
	{
		if ((*it)->get_name().compare(channel_name) == 0)
			return (*it);
	}
	return (NULL);
}

//TODO check if used cuz it does nothing atm
void IRC::drop_channel(Channel *to_drop)
{
#if MALATINI
	std::cout << BLUE << "Drop channel function called" << NC << std::endl;
#endif
	//On cherche si le channel fait partie du vecteur
	std::vector<Channel *> chans = get_channels();

	//Si on le trouve, on l enleve du vecteur
	if (find_channel(to_drop) == true)
	{
		//std::vector<Channel *>::iterator it = get_channel_it(to_drop);
		//chan.erase(it);
	}
}

bool IRC::find_channel(Channel *to_find)
{
	std::vector<Channel *> chans = get_channels();
	std::vector<Channel *>::iterator it = chans.begin();
	std::vector<Channel *>::iterator ite = chans.end();
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

//TODO: a supprimer ?
std::vector<Channel *>::iterator IRC::get_channel_it(Channel *to_find)
{
	std::vector<Channel *> chans = get_channels();
	std::vector<Channel *>::iterator it = chans.begin();
	std::vector<Channel *>::iterator ite = chans.end();
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
	//it++;
	return (ite);
}

bool IRC::find_user(std::string nickname)
{
	for (std::vector<User *>::iterator it = _users.begin(); it != _users.end(); ++it)
		if (nickname.compare((*it)->get_nickname()) == false)
			return (true);
	return (false);
}

//Nickname
User *IRC::get_user_ptr(std::string name)
{
	for (std::vector<User *>::iterator it = _users.begin(); it != _users.end(); ++it)
		if ((*it)->get_nickname() == name)
			return *it;
	return (NULL);
}

Channel *IRC::get_channel_ptr(std::string name)
{
	for (std::vector<Channel *>::iterator it = _channels.begin(); it != _channels.end(); ++it)
		if ((*it)->get_name() == name)
			return *it;
	return (NULL);
}

bool IRC::user_can_join(Channel *channel)
{
	unsigned int user_nb = channel->get_members_nb();

	if (user_nb >= USER_MAXCHAN)
	{
#if DEBUG == 1
		std::cout << RED << "DEBUG: user can't join new channel because he reach USER_MAXCHAN" << NC << std::endl;
#endif
		return (false);
	}
	return (true);
}

//Va permettre de retouner uen reponse avec tous les membres d'une channel
int IRC::send_rpl_chan(std::string code, Channel *channel, IRC *server, User *user)
{
	(void)code;
	(void)channel;
	(void)server;
	(void)user;

	std::vector<User *> users = channel->get_members();
	std::vector<User *>::iterator it = users.begin();
	std::vector<User *>::iterator ite = users.end();

	while (it != ite)
	{
		server->send_rpl_display_user(user, (*it), channel, "", code);
		it++;
	}
	return (0);
}

int IRC::send_rpl(std::string code, User *user, std::vector<std::string> params, std::string command)
{
#if DEBUG
	std::cout << PURPLE << "DEBUG: SEND REPLY: RPL/ERR code is " << code << NC << std::endl;
#endif
	std::string rpl = this->build_reply(code, user, params, command);
#if malatini == 1
	std::cout << PURPLE << "Send reply rpl is: " << NC << std::endl;
	std::cout << GREEN << "Rpl sent to socket: " << user->get_fd() << std::endl;
#endif
	this->_response_queue.push_back(std::make_pair(user->get_fd(), rpl));
	return (0);
}

int IRC::send_rpl_to_all_members(std::string code, std::vector<User *> users, std::vector<std::string> params, std::string command)
{
	std::vector<User *>::iterator it = users.begin();
	std::vector<User *>::iterator ite = users.end();
	while (it != ite)
	{
		std::string rpl = this->build_reply(code, (*it), params, command);
#if MALATINI
		std::cout << GREEN << rpl << NC << std::endl;
#endif
		this->_response_queue.push_back(std::make_pair((*it)->get_fd(), rpl));
		it++;
	}
	return (0);
}

int IRC::send_rpl_display_user(User *user, User *target, Channel *chan, std::string command, std::string code)
{
	(void)command;

	std::string rpl;
	//Generation du prefix
	//TODO: (special a NAMES?)
	rpl += ":127.0.0.1 " + code + " ";

	//TODO: revoir si c est le nickname a chaque fois ou le realname
	//Va permettre d afficher les informations relatives aux users et notamment son statut
	rpl += user->get_nickname() + " " + chan->get_name() + " " + target->get_nickname();
	rpl += "127.0.0.1 0 " + target->get_nickname() + " ";
	rpl += "H";
	if (chan->user_is_operator(target) == true)
		rpl += "@";
	rpl += " :0 realname\r\n";
#if MALATINI
	std::cout << BLUE << "send_rpl_display_user called." << std::endl;
	std::cout << GREEN << rpl << NC << std::endl;
	std::cout << GREEN << "Rpl sent to socket: ";
	std::cout << user->get_fd() << std::endl;
#endif
	this->_response_queue.push_back(std::make_pair(user->get_fd(), rpl));
	return (0);
}

//TODO: a tester
int IRC::send_rpl_display_all_users(std::string code, User *user, Channel *channel, std::string command)
{
#if MALATINI
	std::cout << BLUE << "send_rpl_display_all_users called" << NC << std::endl;
#endif
	(void)user;
	(void)command;
	/* */
	std::vector<User *> users = this->get_users();
	std::vector<User *>::iterator it = users.begin();
	std::vector<User *>::iterator ite = users.end();

	while (it != ite)
	{
		this->send_rpl_display_user(user, (*it), channel, command, code);
		it++;
	}
	//END OF WHO
#if MALATINI
	std::cout << BLUE << "END OF WHO" << NC << std::endl;
#endif
	this->send_rpl("315", user, user->get_params(), "");
	return (0);
}

unsigned int IRC::get_channel_nb(void)
{
	unsigned int number = 0;
	std::vector<Channel *> chans = get_channels();
	number = chans.size();
	return (number);
}

std::string IRC::get_port(void)
{
	return _port;
}

void IRC::set_port(std::string port)
{
	_port = port;
}

void IRC::add_chan(Channel *chan)
{
	_channels.push_back(chan);
}