#include <IRC.hpp>
#include <User.hpp>

User::User(void)
/*
: _nickname("null"), _username("null"), _hostname("null"), _realname("null"), _modes("null"), _has_operator_status(false), _is_away(false), _away_mssg("null"), _password("null"), _message_status(0), _message("null"), _server_name("null"), _server_ip("null"), _server_creation("null"), _channels(0), _port("null"), _user_is_oper(0), _user_is_away(0), _user_has_registered_pass(0), _user_has_registered_nick(0), _user_is_registered(0) */
{
#if USERDEBUG
	std::cout << "User default constructor called" << std::endl;
#endif
}

User::User(int fd) : _socket(fd)
{
	#if DEBUG
		std::cout << BLUE << "DEBUG: User constructor called with fd param" << NC << std::endl;
	#endif
	_to_delete = false;
	_user_is_registered = false;
	_is_away = false;
}

User::~User(void)
{
#if DEBUG
	std::cout << BLUE << "DEBUG: User destructor" << NC << std::endl;
#endif
}

void User::set_nickname(std::string nickname)
{
	this->_nickname = nickname;
}

void User::set_username(std::string username)
{
	this->_username = username;
}

void User::set_realname(std::string realname)
{
	this->_realname = realname;
}

void User::set_hostname(std::string hostname)
{
	this->_hostname = hostname;
}

void User::set_modes(std::string modes)
{
	this->_modes = modes;
}

void User::set_operator_status(bool value)
{
	this->_has_operator_status = value;
}

void User::set_is_away(bool value)
{
	if(value == true && this->get_away_mssg().empty())
		this->set_away_mssg("I'm away");
	this->_is_away = value;
}

void User::set_away_mssg(std::string message)
{
	this->_away_mssg = message;
}

void User::set_registered_user(bool is_set)
{
	this->_user_is_registered = is_set;
}

void User::set_operator(bool is_set)
{
	this->_has_operator_status = is_set;
}

void User::set_message_status(int status)
{
	this->_message_status = status;
}

void User::set_init_socket(int socket)
{
	this->_socket = socket;
}

void User::set_unparsed_client_command(std::string client_command)
{
	this->_unparsed_client_command = client_command;
}

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
		std::cout << "unparsed command pushed to vector:" << token << std::endl;
		new_command._unparsed = s;
		this->_commands.push_back(new_command);
		s.erase(0, pos + delimiter.length());
	}
	int i = 0;
	for (std::vector<t_cmd>::iterator it = _commands.begin(); it != _commands.end(); it++)
	{
		std::cout << "--COMMAND N° " << i++ <<  "--" << std::endl;
		this->store_prefix(it);
		this->store_command(it);
		this->store_params(it);
#if DEBUG
		std::cout << "prefix= " << (*it)._prefix << std::endl;
		std::cout << "command= " << (*it)._command_name << std::endl;

		int i = 0;
		for (std::vector<std::string>::iterator itr = (*it)._params.begin(); itr != (*it)._params.end(); itr++)
		{
			std::cout << "param(" << i << ")= " << *itr << std::endl;
			i++;
		}
		std::cout << std::endl;
#endif
	}
	std::cout << RED << "EXIT SPLIT_MULTI_COMMD" << NC << std::endl;
}

std::string User::get_nickname(void) const
{
	return (this->_nickname);
}

std::string User::get_username(void) const
{
	return (this->_username);
}

std::string User::get_realname(void) const
{
	return (this->_realname);
}

std::string User::get_hostname(void) const
{
	return (this->_hostname);
}

std::string User::get_modes(void) const
{
	return (this->_modes);
}

bool User::get_operator_status(void) const
{
	return (this->_has_operator_status);
}

bool User::get_is_away(void) const
{
	return (this->_is_away);
}

std::string User::get_away_mssg(void) const
{
	return (this->_away_mssg);
}

std::string User::get_password(void) const
{
	return (this->_password);
}

std::string User::get_message(void) const
{
	return (this->_message);
}

int User::get_message_status(void) const
{
	return (this->_message_status);
}

int User::get_socket(void) const
{
	return (this->_socket);
}

int User::get_channels_nb(void) const
{
	return (this->_channels.size());
}

std::vector<std::string> User::get_params(void) const
{
	return (this->_params);
}

std::string User::get_prefix(void) const
{
	return (this->_prefix);
}

std::string User::get_command_name(void) const
{
	std::string command_name = this->_command_name;
	if (command_name.empty())
		return ("");
	return (command_name);
}

std::string User::get_unparsed_client_command(void) const
{
	std::string unparsed = this->_unparsed_client_command;
	if (unparsed.empty())
		return ("");
	return (unparsed);
}

unsigned int User::get_params_size(void) const{return (this->get_params().size());}


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
	return (this->_user_is_registered);
}

bool User::user_is_away(void) const
{
	return (this->_is_away);
}

bool User::user_is_operator(void) const
{
	return (this->_has_operator_status);
}

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

bool User::string_end_with(std::string const &fullString, std::string const &ending)
{
	if (fullString.length() >= ending.length())
		return (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
	else
		return false;
}

void User::store_command(std::vector<t_cmd>::iterator it)
{
	std::string command;
	if (!(*it)._unparsed.empty())
	{
		int i = 0;
		i = store_string_until_char(&(*it)._command_name, &(*it)._unparsed, ' ', i);
		(*it)._unparsed.replace(0, i, "");
		if (string_end_with((*it)._command_name, "\r\n"))
		{
			(*it)._command_name.resize((*it)._command_name.size() - 2);
		}
		std::transform((*it)._command_name.begin(), (*it)._command_name.end(),(*it)._command_name.begin(), ::toupper);
	}
}

void User::store_command()
{
	std::string command;
	if (!this->_unparsed_client_command.empty())
	{
		int i = 0;
		i = store_string_until_char(&this->_command_name, &this->_unparsed_client_command, ' ', i);
		this->_unparsed_client_command.replace(0, i, "");
		if (string_end_with(this->_command_name, "\r\n"))
			this->_command_name.resize(this->_command_name.size() - 2);
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

void User::display_client_info(void)
{
	std::cout << "----- Displaying User Info -----" << std::endl;
	std::cout << "Nickname : " << this->get_nickname() << std::endl;
	std::cout << "Username : " << this->get_username() << std::endl;
	this->display_channels();
}

void User::display_channels(void)
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

void	User::display_params_bis(void)
{
	std::vector<std::string> params = this->get_params();
	std::vector<std::string>::iterator it = params.begin();
	std::vector<std::string>::iterator ite = params.end();

	int index = 0;
	std::string tmp;
	std::cout << PURPLE << "Printing params" << std::endl;
	while (it != ite)
	{
		tmp = (*it);
		std::cout << PURPLE << "Params " << index << ": " << tmp << std::endl;
		index++;
		it++;
	}
	return ;
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

void User::be_added_to_channel(Channel *channel)
{
	if (!channel)
		return;
	unsigned int member = channel->get_members_nb();
	if (member >= 1)
		channel->newMember(this, false);
	else
	{
		//TODO Si non on va devenir operateur
		channel->newMember(this, true);
	}
	#if DEBUG
		std::cout << PURPLE << "USER: be_added_to_channel called for: " << this->get_nickname() << std::endl;
	#endif
	return;
}

void User::set_socket(int socket)
{
	this->_socket = socket;
}

void User::increase_channel_nb(void)
{
	if (this->_channels_nb > 0)
		this->_channels_nb++;
	else
	{
#if DEBUG
		std::cout << RED << "USER: Error with nb of channels (++)." << std::endl;
#endif
	}
}

void User::decrease_channel_nb(void)
{
	if (this->_channels_nb == USER_MAXCHAN)
	{
		#if DEBUG
			std::cout << RED << "USER: Error with nb of channels (--)." << std::endl;
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
}

/**
 * @brief On doit avoir verifie au prealable que le user etait bien membre
 *
 * @param channel
 */
void User::remove_channel_from_list(Channel *channel)
{
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
			chans.erase(it);
			this->decrease_channel_nb();
		}
		it++;
	}
	return;
}

std::ostream &operator<<(std::ostream &COUT, User *user)
{
	COUT << user->get_nickname();
	return (COUT);
}

//Va permettre de boucler quand il y a plusieurs users ou channel passes en parametres
unsigned int User::count_commas(void) const
{
	unsigned int commas = 0;
	std::vector<std::string> params = this->get_params();
	std::vector<std::string>::iterator it = params.begin();
	std::vector<std::string>::iterator ite = params.end();

	std::string tmp;
	//int pos = 0;
	while (it != ite)
	{
		tmp = (*it);
		//pos = tmp.find(' ');
		if (tmp.find(' ') == std::string::npos)
		{
			//On a pas trouve d'espace
			commas++;
		}
		it++;
	}
	#if DEBUG
		std::cout << PURPLE << "DEBUG: " << "USER: Counting " << commas << " commas in the params" << std::endl;
	#endif
	return (commas);
}