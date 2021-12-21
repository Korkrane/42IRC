#include <IRC.hpp>
#include <User.hpp>

//TODO: revoir l init list de user !
User::User(void)
/*
: _nickname("null"), _username("null"), _hostname("null"), _realname("null"), _modes("null"), _is_oper(false), _is_away(false), _away_mssg("null"), _password("null"), _message("null"), _server_name("null"), _server_ip("null"), _server_creation("null"), _channels(0), _port("null"), _user_has_registered_pass(0), _user_has_registered_nick(0), is_registered(0) */
{
#if USERDEBUG == 1
	std::cout << "User default constructor called" << std::endl;
#endif
	this->_target_channel = NULL;
}

User::User(int fd) : _fd(fd)
{
#if DEBUG == 1
	std::cout << BLUE << "DEBUG: User constructor called with fd param" << NC << std::endl;
#endif
	_to_delete = false;
	_is_registered = false;
	_is_oper = false;
	_is_away = false;

	_channels_nb = 0;
}

User::~User(void)
{
#if DEBUG == 1
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
	_hostname = hostname;
}

void User::set_modes(std::string modes)
{
	_modes = modes;
}

void User::is_operator(bool value)
{
	_is_oper = value;
}

void User::is_away(bool value)
{
	if (value == true && get_away_mssg().empty())
		set_away_mssg("I'm away");
	_is_away = value;
}

void User::set_away_mssg(std::string message)
{
	_away_mssg = message;
}

void User::is_registered(bool value)
{
	_is_registered = value;
}

void User::set_request(std::string request)
{
	_request = request;
}

void User::split_if_multiple_command()
{
#if DEBUG == 1
	std::cout << RED << "ENTER SPLIT_MULTI_COMMD" << NC << std::endl;
#endif
	t_cmd new_command;
	std::string s = this->_request;
	std::string delimiter = "\r\n";

	size_t pos = 0;
	std::string token;
	while ((pos = s.find(delimiter)) != std::string::npos)
	{
		token = s.substr(0, pos);
#if DEBUG == 1
		std::cout << "unparsed command pushed to vector:" << token << std::endl;
#endif
		new_command._unparsed = s;
		this->_commands.push_back(new_command);
		s.erase(0, pos + delimiter.length());
	}
	int i = 0;
	(void)i;
	for (std::vector<t_cmd>::iterator it = _commands.begin(); it != _commands.end(); it++)
	{
#if DEBUG == 1
		std::cout << "--COMMAND N° " << i++ << "--" << std::endl;
#endif
		this->store_prefix(it);
		this->store_command(it);
		this->store_params(it);
#if DEBUG == 1
		std::cout << "prefix= " << (*it)._prefix << std::endl;
		std::cout << "command= " << (*it)._command << std::endl;

		int i = 0;
		for (std::vector<std::string>::iterator itr = (*it)._params.begin(); itr != (*it)._params.end(); itr++)
		{
			std::cout << "param(" << i << ")= " << *itr << std::endl;
			i++;
		}
		std::cout << std::endl;
#endif
	}
#if DEBUG == 1
	std::cout << RED << "EXIT SPLIT_MULTI_COMMD" << NC << std::endl;
#endif
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

int User::get_fd(void) const
{
	return _fd;
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
	return _command.empty() ? "" : _command;
}

std::string User::get_request(void) const
{
	return _request.empty() ? "" : _request;
}

unsigned int User::get_params_size(void) const
{
	return this->get_params().size();
}

bool User::is_registered(void) const
{
	return _is_registered;
}

bool User::is_away(void) const
{
	return _is_away;
}

bool User::is_operator(void) const
{
	return _is_oper;
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
	if (_request != "")
	{
		std::string::iterator it = _request.begin();
		int i = 0;
		if (*it == ':')
		{
			i = store_string_until_char(&_prefix, &_request, ' ', i);
			_request.replace(0, i, "");
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
	if (!(*it)._unparsed.empty())
	{
		int i = 0;
		i = store_string_until_char(&(*it)._command, &(*it)._unparsed, ' ', i);
		(*it)._unparsed.replace(0, i, "");
		if (string_end_with((*it)._command, "\r\n"))
			(*it)._command.resize((*it)._command.size() - 2);
		std::transform((*it)._command.begin(), (*it)._command.end(), (*it)._command.begin(), ::toupper);
	}
}

void User::store_command()
{
	if (!_request.empty())
	{
		int i = 0;
		i = store_string_until_char(&_command, &_request, ' ', i);
		_request.replace(0, i, "");
		if (string_end_with(_command, "\r\n"))
			_command.resize(_command.size() - 2);
	}
}

void User::split_string_to_vector(std::vector<std::string> *vec, std::string *str, char c)
{
	size_t pos = str->find(c);
	size_t init_pos = 0;

	while (pos != std::string::npos)
	{
		vec->push_back(str->substr(init_pos, pos - init_pos));
		init_pos = pos + 1;
		pos = str->find(c, init_pos);
	}
	vec->push_back(str->substr(init_pos, std::min(pos, str->size()) - init_pos + 1));
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
	if (this->_request != "")
	{
		split_string_to_vector(&this->_params, &this->_request, ' ');
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
	this->_command = value;
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

void User::display_params_bis(void)
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
	return;
}

void User::display_command(void)
{
	std::cout << "--- Displaying Last command parsed ---" << std::endl;
	if (!this->get_prefix().empty())
		std::cout << "Prefix = " << this->_prefix << std::endl;
	else
		std::cout << "There is no prefix" << std::endl;
	if (!this->_command.empty())
		std::cout << "Command = " << this->_command << std::endl;
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
#if DEBUG == 1
	std::cout << PURPLE << "USER: be_added_to_channel called for: " << this->get_nickname() << std::endl;
#endif
	return;
}

void User::set_fd(int fd)
{
	_fd = fd;
}

void User::increase_channel_nb(void)
{
	if (this->_channels_nb > 0)
		this->_channels_nb++;
	else
	{
#if DEBUG == 1
		std::cout << RED << "USER: Error with nb of channels (++)." << std::endl;
#endif
	}
}

void User::decrease_channel_nb(void)
{
	if (this->_channels_nb == USER_MAXCHAN)
	{
#if DEBUG == 1
		std::cout << RED << "USER: Error with nb of channels (--)." << std::endl;
#endif
	}
	this->_channels_nb--;
}

/**
 * @brief Les verifications en termes de USER_MACHAN doivent etre faites au prealable
 * TODO: si la channel existe pas on l'ajoute pas mais on increase qd meme (question baudoin)
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
	std::string channel_name = channel->get_name();
	std::string check_name;
	for (std::vector<Channel *>::iterator it = _channels.begin(); it != _channels.end(); it++)
	{
		check_name = (*it)->get_name();
		if (channel_name.compare(check_name) == 0)
		{
			_channels.erase(it);
			decrease_channel_nb();
			break;
		}
	}
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
#if DEBUG == 1
	std::cout << PURPLE << "DEBUG: USER: Counting " << commas << " commas in the params" << std::endl;
#endif
	return (commas);
}

Channel *User::get_target_channel(void) const
{
	Channel *chan = this->_target_channel;
#if MALATINI == 1
	std::cout << PURPLE << chan->get_name() << NC << std::endl;
#endif
	return (chan);
}

void User::set_target_channel(Channel *channel)
{
	this->_target_channel = channel;
#if MALATINI == 1

	if (!channel)
	{
		std::cout << RED << "Error : set a target channel that is NULL!" << NC << std::endl;
	}
	else
	{
		std::cout << PURPLE << "Channel has been set to" << channel->get_name() << NC << std::endl;
	}
#endif
	return;
}

bool User::get_display_who(void) const
{
	return (this->_display_who);
}

void User::set_display_who(bool display)
{
	this->_display_who = display;
}

std::vector<Channel *> User::get_channels(void) const
{
	return (this->_channels);
}

std::vector<std::string> User::get_topic_params(void) const
{
	return (this->_topic_params);
}

void User::add_topic_params(std::string str)
{
	this->_topic_params.push_back(str);
}

void User::clear_topic_params(void)
{
	this->_topic_params.clear();
}