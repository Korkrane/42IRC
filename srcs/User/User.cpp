#include <IRC.hpp>
#include <User.hpp>

User::User(void)
/*
: _nickname("null"), _username("null"), _hostname("null"), _realname("null"), _modes("null"), _has_operator_status(false), _is_away(false), _away_mssg("null"), _password("null"), _message_status(0), _message("null"), _server_name("null"), _server_ip("null"), _server_creation("null"), _channels(0), _port("null"), _user_is_oper(0), _user_is_away(0), _user_has_registered_pass(0), _user_has_registered_nick(0), _user_is_registered(0) */
{
#if USERDEBUG
	std::cout << "User default constructor called" << std::endl;
#endif
	return;
}

User::User(int fd) : _socket(fd)
/*: _nickname("null"), _username("null"), _hostname("null"), _realname("null"), _modes("null"), _has_operator_status(false), _is_away(false), _away_mssg("null"), _password("null"), _message_status(0), _message("null"), _server_name(server_name), _server_ip(server_ip), _server_creation(server_creation), _channels(0), _port(port), _user_is_oper(0), _user_is_away(0), _user_has_registered_pass(0), _user_has_registered_nick(0), _user_is_registered(0) */
{
	_to_delete = false;
	_user_is_registered = false;
#if USERDEBUG
	std::cout << BLUE << "\t\tDEBUG: User default constructor called with fd parameter only" << NC << std::endl;
	//displayClientInfo();
#endif
	return;
}

/*
** Destructeur
*/
User::~User(void)
{
#if USERDEBUG
	std::cout << "User destructor called" << std::endl;
#endif
	return;
}

/*
** Setters
*/

void User::set_nickname(std::string nickname)
{
	this->_nickname = nickname;
#if USERDEBUG
	std::cout << "User's nickname has been set to " << nickname << std::endl;
#endif
	return;
}

void User::set_username(std::string username)
{
	this->_username = username;
#if USERDEBUG
	std::cout << "User's username has been set to " << username << std::endl;
#endif
}

void User::set_realname(std::string realname)
{
	this->_realname = realname;
#if USERDEBUG
	std::cout << "User's realname has been set to " << realname << std::endl;
#endif
}

void User::set_hostname(std::string hostname)
{
	this->_hostname = hostname;
#if USERDEBUG
	std::cout << "User's hostname has been set to " << hostname << std::endl;
#endif
}

void User::set_modes(std::string modes)
{
	this->_modes = modes;
#if USERDEBUG
	std::cout << "User's modes has been set to " << modes << std::endl;
#endif
}

void User::set_operator_status(bool value)
{
	this->_has_operator_status = value;
#if USERDEBUG
	std::cout << "User's operator status has been set to " << value << std::endl;
#endif
}

void User::set_is_away(bool value)
{
	this->_is_away = value;
#if USERDEBUG
	std::cout << "User's is away status has been set to " << value << std::endl;
#endif
}

void User::set_away_mssg(std::string message)
{
	this->_away_mssg = message;
#if USERDEBUG
	std::cout << "User's is away message has been set to " << message << std::endl;
#endif
}

void User::set_registered_user(bool is_set)
{
	this->_user_is_registered = is_set;
#if USERDEBUG
	std::cout << "user is registered ? " << is_set << std::endl;
#endif
}

void User::set_operator(bool is_set)
{
	this->_has_operator_status = is_set;
#if USERDEBUG
	std::cout << "user is operator ? " << is_set << std::endl;
#endif
}

void User::set_message_status(int status)
{
	this->_message_status = status;
#if USERDEBUG
	std::cout << "User Operator status " << status << std::endl;
#endif
}

/*
** revoir si on prefere utiliser select ou socket
*/
void User::set_init_socket(int socket)
{
	this->_socket = socket;
	//this->fd = socket;
#if USERDEBUG
	std::cout << "User socket is " << socket << std::endl;
#endif
}

void User::set_unparsed_client_command(std::string client_command)
{
	this->_unparsed_client_command = client_command;
}

#include <fstream>
#include <string>

void User::split_if_multiple_command()
{

	std::cout << RED << "ENTER SPLIT_MULTI_COMMD" << NC << std::endl;
	t_cmd new_command;
	std::string s = this->_unparsed_client_command;
	std::string delimiter = "\r\n";

	size_t pos = 0;
	std::string token;
	while ((pos = s.find(delimiter)) != std::string::npos)
	{
		token = s.substr(0, pos);
		std::cout << "splitted command on parsing the _unparsed:" << token << std::endl;
		new_command._unparsed = s;
		this->_commands.push_back(new_command);
		s.erase(0, pos + delimiter.length());
	}
	int i = 0;
	for (std::vector<t_cmd>::iterator it = _commands.begin(); it != _commands.end(); it++)
	{
		std::cout << std::endl
				  << "--COMMAND N° " << i++ << std::endl;

		this->store_prefix(it);
		this->store_command(it);
		this->store_params(it);
#if DEBUG
		std::cout << "prefix=" << (*it)._prefix << std::endl;
		std::cout << "command=" << (*it)._command_name << std::endl;

		int i = 0;
		for (std::vector<std::string>::iterator itr = (*it)._params.begin(); itr != (*it)._params.end(); itr++)
		{
			std::cout << "param(" << i << ")= " << *itr << std::endl;
			i++;
		}

#endif
	}
	std::cout << RED << "EXIT SPLIT_MULTI_COMMD" << NC << std::endl;
}

/*
** Getters
*/
std::string User::get_nickname(void) const
{
	std::string nick = this->_nickname;
#if USERDEBUG
	std::cout << "User's nickname is " << nick << std::endl;
#endif
	return (nick);
}

std::string User::get_username(void) const
{
	std::string user = this->_username;
#if USERDEBUG
	std::cout << "User's username is " << user << std::endl;
#endif
	return (user);
}

std::string User::get_realname(void) const
{
	std::string real = this->_realname;
#if USERDEBUG
	std::cout << "User's realname is " << real << std::endl;
#endif
	return (real);
}

std::string User::get_hostname(void) const
{
	std::string host = this->_hostname;
#if USERDEBUG
	std::cout << "User's hostname is " << host << std::endl;
#endif
	return (host);
}

std::string User::get_modes(void) const
{
	std::string modes;
	modes = this->_modes;
#if USERDEBUG
	std::cout << "User's modes is " << modes << std::endl;
#endif
	return (modes);
}

bool User::get_operator_status(void) const
{
	bool op = this->_has_operator_status;
#if USERDEBUG
	std::cout << "User's operator status is " << op << std::endl;
#endif
	return (op);
}

bool User::get_is_away(void) const
{
	bool op = this->_is_away;
#if USERDEBUG
	std::cout << "User's away status is " << op << std::endl;
#endif
	return (op);
}

std::string User::get_away_mssg(void) const
{
	std::string away = this->_away_mssg;
#if USERDEBUG
	std::cout << "User's away message is " << away << std::endl;
#endif
	return (away);
}

/*
** Added
*/
std::string User::get_password(void) const
{
	std::string pass = this->_password;
#if USERDEBUG
	std::cout << "User's password is " << pass << std::endl;
#endif
	return (pass);
}

std::string User::get_message(void) const
{
	std::string message = this->_message;
#if USERDEBUG
	std::cout << "User's message is " << message << std::endl;
#endif
	return (message);
}

/*
** voir message status
*/
int User::get_message_status(void) const
{
	int status = this->_message_status;
#if USERDEBUG
	std::cout << "User's message_status is " << status << std::endl;
#endif
	return (status);
}

/*
** Voir quand la socket est necessaire
*/
int User::get_socket(void) const
{
	int socket = this->_socket;
#if USERDEBUG
	std::cout << "User's socket is " << socket << std::endl;
#endif
	return (socket);
}

/*
** Puisqu'il s'agit d'un vecteur il est aisé de retrouver sa taille
** A tester
*/
int User::get_channels_nb(void) const
{
	int size = this->_channels.size();
#if USERDEBUG
	std::cout << "This client is in " << size << " channels" << std::endl;
#endif
	return (size);
}

std::vector<std::string> User::get_params(void) const
{
	return (this->_params);
}

std::string User::get_prefix(void) const
{
	std::string prefix = this->_prefix;
#if USERDEBUG
	if (!prefix.empty())
		std::cout << "This client cmd prefix is " << prefix << std::endl;
#endif
	return (prefix);
}

std::string User::get_command_name(void) const
{
	std::string command_name = this->_command_name;
	if (command_name.empty())
	{
#if USERDEBUG
		std::cout << "Command name is empty." << std::endl;
#endif
		return ("");
	}

#if USERDEBUG
	//std::cout << "This client cmd command_name is " << command_name << std::endl;
#endif
	return (command_name);
}

/*
** Utils parsing
*/
std::string User::get_unparsed_client_command(void) const
{
	std::string unparsed;

	unparsed = this->_unparsed_client_command;
	if (unparsed.empty())
	{
#if USERDEBUG
		std::cout << "Unparsed command is empty." << std::endl;
#endif
		return ("");
	}
#if USERDEBUG
	//std::cout << "The unparsed command is : " << unparsed << std::endl;
#endif
	return (unparsed);
}

unsigned int User::get_params_size(void) const
{
	unsigned int size;

	size = this->get_params().size();
#if USERDEBUG
	std::cout << "The param size of the current command is " << std::endl;
#endif
	return (size);
}

/*
** Utils
*/

bool User::check_if_prefix(void) const
{
	char colon = ':';
	std::string check = this->get_unparsed_client_command();
	if (check.find(colon) != std::string::npos)
		return (true);
	return (false);
}

bool User::user_is_registered(void) const
{
	bool registered = this->_user_is_registered;
#if USERDEBUG
	std::cout << "The client is registered ? " << registered << std::endl;
#endif
	return (registered);
}

bool User::user_is_away(void) const
{
	bool away = this->_user_is_away;
#if USERDEBUG
	std::cout << "The client is away ? " << away << std::endl;
#endif
	return (away);
}

bool User::user_is_operator(void) const
{
	bool ope = this->_user_is_oper;
#if USERDEBUG
	std::cout << "The client is operator ? " << ope << std::endl;
#endif
	return (ope);
}

/*
** Parsing client message
*/

int User::store_string_until_char(std::string *dest, std::string *src, char c, int len)
{
	std::string::iterator it = src->begin();
	while (it != src->end())
	{
		if (*it == c)
		{
			*dest = src->substr(0, len);
			len++;
			break;
		}
		it++;
		len++;
	}
	if (it == src->end())
		*dest = src->substr(0, len);
	return (len);
}

void User::store_prefix(std::vector<t_cmd>::iterator it)
{
	if ((*it)._unparsed != "")
	{
		/*
		#if DEBUG
			std::cout << YELLOW << "DEBUG: STORE PREFIX WITH:" << (*it)._unparsed << NC << std::endl;
		#endif
		*/
		std::string::iterator it2 = (*it)._unparsed.begin();

		int i = 0;
		if (*it2 == ':')
		{
			i = store_string_until_char(&(*it)._prefix, &(*it)._unparsed, ' ', i);
			(*it)._unparsed.replace(0, i, "");
		}
	}
}

void User::store_prefix()
{
	if (this->_unparsed_client_command != "")
	{
		std::string::iterator it = this->_unparsed_client_command.begin();

		int i = 0;
		if (*it == ':')
		{
			i = store_string_until_char(&this->_prefix, &this->_unparsed_client_command, ' ', i);
			this->_unparsed_client_command.replace(0, i, "");
		}
	}
}

bool User::hasEnding(std::string const &fullString, std::string const &ending)
{
	if (fullString.length() >= ending.length())
	{
		return (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
	}
	else
	{
		return false;
	}
}

void User::store_command(std::vector<t_cmd>::iterator it)
{
	std::string command;
	if (!(*it)._unparsed.empty())
	{
		int i = 0;
		i = store_string_until_char(&(*it)._command_name, &(*it)._unparsed, ' ', i);
		(*it)._unparsed.replace(0, i, "");
		if (hasEnding((*it)._command_name, "\r\n"))
		{
			(*it)._command_name.resize((*it)._command_name.size() - 2);
		}
	}
}

void User::store_command()
{
	std::string command;
	if (!this->_unparsed_client_command.empty())
	{
#if USERDEBUG
		std::cout << BLUE << "USERDEBUG: The resulting unparsed command is: " << this->_unparsed_client_command << NC << std::endl;
#endif
		int i = 0;
		i = store_string_until_char(&this->_command_name, &this->_unparsed_client_command, ' ', i);
		this->_unparsed_client_command.replace(0, i, "");
		if (hasEnding(this->_command_name, "\r\n"))
			this->_command_name.resize(this->_command_name.size() - 2);

		/*
		//Proposition Mahaut
		if (this->check_if_prefix() == false)
		{
			//La commande doit etre le premier mot
			//Attention si quelqu'un s'amusait a mettre des " ?
			//Dans la command unparsed, ajouter un check de
			std::string::size_type pos = this->get_unparsed_client_command().find(' ');
			if (pos != std::string::npos)
			{
				//je mets 1 pour me separer du / ?
				//ou je devrais verifier qu'il s'agit bien d'un \ ?
				command = this->get_unparsed_client_command().substr(0, pos);
			}
			else
				command = this->get_unparsed_client_command();
			this->set_command(command);
		}
		*/
	}
}

void User::split_string_to_vector(std::vector<std::string> *vec, std::string *str, char c)
{
	size_t pos = str->find(c);
	size_t initialPos = 0;

	while (pos != std::string::npos)
	{
		vec->push_back(str->substr(initialPos, pos - initialPos));
		initialPos = pos + 1;
		pos = str->find(c, initialPos);
	}
	vec->push_back(str->substr(initialPos, std::min(pos, str->size()) - initialPos + 1));
}

void User::patch_params(std::vector<std::string> *params)
{
	int elem_to_erase = 0;
	for (std::vector<std::string>::iterator it = params->begin(); it != params->end(); it++)
	{
		if ((*it)[0] == ':')
		{
			for (std::vector<std::string>::iterator it2 = it + 1; it2 != params->end(); it2++)
			{
				(*it).append(" " + *it2);
				elem_to_erase++;
			}
			break;
		}
	}

	std::vector<std::string>::iterator ite = params->end();
	for (int erase = elem_to_erase; erase != 0; --erase)
		params->erase(ite);
}

void User::store_params(std::vector<t_cmd>::iterator it)
{
	if ((*it)._unparsed != "")
	{
		size_t rn = (*it)._unparsed.find("\r\n");
		(*it)._unparsed = (*it)._unparsed.substr(0, rn);
		split_string_to_vector(&(*it)._params, &(*it)._unparsed, ' ');
		patch_params(&(*it)._params);
	}
}

void User::store_params()
{
	if (this->_unparsed_client_command != "")
	{
		std::cout << "Enter in store_params:" << this->_unparsed_client_command << std::endl;
		split_string_to_vector(&this->_params, &this->_unparsed_client_command, ' ');
		patch_params(&this->_params);
	}
}

void User::set_params(std::vector<std::string> value)
{
	this->_params = value;
}
void User::set_prefix(std::string value)
{
	this->_prefix = value;
}
void User::set_command(std::string value)
{
	this->_command_name = value;
}

/*
** Display / Debug
*/
void User::displayClientInfo(void)
{
	std::cout << "----- Displaying User Info -----" << std::endl;
	std::cout << "Nickname : " << this->get_nickname() << std::endl;
	std::cout << "Username : " << this->get_username() << std::endl;
	this->displayChannels();
}

void User::displayChannels(void)
{
	std::cout << "--- Listing Channels ---" << std::endl;
	std::vector<Channel *>::iterator it = this->_channels.begin();
	std::vector<Channel *>::iterator ite = this->_channels.end();
	while (it != ite)
	{
		(*it)->displayChannelInfo();
		it++;
	}
	std::cout << "------------------------" << std::endl;
}

void User::display_params(void) //const
{
	int i = 0;
	if (this->_params.size() >= 1)
	{
		for (std::vector<std::string>::iterator itr = this->_params.begin(); itr != this->_params.end(); itr++)
		{
			std::cout << "param(" << i << ") =" << *itr << std::endl;
			i++;
		}
	}
	else
		std::cout << "There are no params" << std::endl;
	return;
}

void User::display_command(void)
{
	std::cout << "--- Displaying Last command parsed ---" << std::endl;
	if (!this->get_prefix().empty())
		std::cout << "Prefix = " << this->_prefix << std::endl;
	else
		std::cout << "There is no prefix" << std::endl;
	if (!this->_command_name.empty())
		std::cout << "Command = " << this->_command_name << std::endl;
	else
		std::cout << "No command parsed" << std::endl;
	this->display_params();
}

IRC *User::get_server(void) const
{
	IRC *serv = this->_IRCserver;
	return serv;
}

Channel *User::creates_channel(std::string channel_name)
{
	//Le channel name a deja ete verifie au prealable

	Channel *chan = new Channel(channel_name, this, this->get_server());
	//Le constructeur de channel doit faire le reste;
	return (chan);
}

bool User::is_channel_user(Channel *channel)
{
	if (!channel)
		return (false);
	std::vector<User *> users = channel->get_members();
	std::vector<User *>::iterator it = users.begin();
	std::vector<User *>::iterator ite = users.end();
	std::string check_nick;
	std::string user_nick = this->get_nickname();
	while (it != ite)
	{
		check_nick = (*it)->get_nickname();
		if (user_nick.compare(check_nick) == 0)
		{
#if USERDEBUG
			std::cout << BLUE << "USERDEBUG: "
					  << "USER: "
					  << "The user is indeed a member of the given channel." << std::endl;
#endif
			return (true);
		}
	}
	return (false);
}

/**
 * @brief Va permettre de savoir si on a atteint le quota max de chan
 *
 * @return true
 * @return false
 * TODO: a reprendre
 */
/*
bool User::can_join(void)
{
	//Faire le tour de tous les channels du serveur
	std::vector<Channel *> chans = this->_IRCserver->get_channels();
	std::vector<Channel *>::iterator it = chans.begin();
	std::vector<Channel *>::iterator ite = chans.end();

	unsigned int is_user = 0;
	while (it != ite)
	{
		if (is_user >= USER_MAXCHAN)
		{
#if USERDEBUG
			std::cout << BLUE << "USERDEBUG: "
					  << "USER :"
					  << "Can not join new channel" << std::endl;
#endif
			return (false);
		}
		if (this->is_channel_user(*it) == true)
		{
			is_user++;
		}
		it++;
	}
	return (true);
}
*/

void User::be_added_to_channel(Channel *channel)
{
	if (!channel)
		return;
	//Verifier si il y a deja des membres ? Normalement c'est deja fait
	unsigned int member = channel->get_members_nb();
	//Si oui on va etre ajoute simplement
	if (member >= 1)
	{
		channel->newMember(this, false);
	}
	else
	{
		//Si non on va devenir operateur
		channel->newMember(this, true);
	}
	return;
}

void User::set_socket(int socket)
{
	this->_socket = socket;
	return;
}

void User::increase_channel_nb(void)
{
	if (this->_channels_nb > 0)
		this->_channels_nb++;
	else
	{
#if DEBUG
		std::cout << BLUE << "DEBUG: "
				  << "USER: Error with nb of channels (++)." << std::endl;
#endif
	}
	return;
}

void User::decrease_channel_nb(void)
{
	if (this->_channels_nb == USER_MAXCHAN)
	{
#if DEBUG
		std::cout << BLUE << "DEBUG: "
				  << "USER: Error with nb of channels (--)." << std::endl;
#endif
	}
	this->_channels_nb--;
}

/**
 * @brief Les verifications en termes de USER_MACHAN doivent etre faites au prealable
 *
 * @param channel
 */
void User::add_channel_to_list(Channel *channel)
{
	if (channel)
		this->_channels.push_back(channel);
	this->increase_channel_nb();
	return;
}

/**
 * @brief On doit avoir verifie au prealable que le user etait bien membre
 *
 * @param channel
 */
void User::remove_channel_from_list(Channel *channel)
{
	//Il faut trouver la channel dans la liste
	std::vector<Channel *> chans = this->_channels;
	std::vector<Channel *>::iterator it = chans.begin();
	std::vector<Channel *>::iterator ite = chans.end();
	std::string channel_name = channel->get_name();
	std::string check_name;
	while (it != ite)
	{
		check_name = (*it)->get_name();
		if (channel_name.compare(check_name) == 0)
		{
			//TODO: voir s'il faut faire un delete ?
			chans.erase(it);
			this->decrease_channel_nb();
		}
		it++;
	}
	return;
}

std::string User::get_server_name(void) const
{
	std::string server_name = this->get_server()->get_name();
#if DEBUG
	std::cout << BLUE << "DEBUG: "
			  << "USER: server_name is " << server_name << std::endl;
#endif
	return (server_name);
}

std::ostream &operator<<(std::ostream &COUT, User *user)
{
	COUT << user->get_nickname();
	return (COUT);
}