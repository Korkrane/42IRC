#include <IRC.hpp>
#include <User.hpp>

User::User(void) : _nickname(""),
				   _username(""),
				   _hostname(""),
				   _realname(""),
				   _modes(""),
				   _away_mssg(""),
				   _password(""),
				   _channels(0),
				   _channels_nb(0),
				   _is_oper(false),
				   _is_away(false),
				   _user_has_registered_pass(false),
				   _user_has_registered_nick(false),
				   _is_registered(false),
				   _display_who(false),
				   _topic_params(0),
				   _request(""),
				   _prefix(""),
				   _command(""),
				   _target_channel(0),
				   _params(0),
				   _splitted_channels(0),
				   _splitted_args(0),
				   _commands(0),
				   _to_delete(false)
{
}

User::User(int fd) : _fd(fd),
					 _nickname(""),
					 _username(""),
					 _hostname(""),
					 _realname(""),
					 _modes(""),
					 _away_mssg(""),
					 _password(""),
					 _channels(0),
					 _channels_nb(0),
					 _is_oper(false),
					 _is_away(false),
					 _user_has_registered_pass(false),
					 _user_has_registered_nick(false),
					 _is_registered(false),
					 _display_who(false),
					 _topic_params(0),
					 _request(""),
					 _prefix(""),
					 _command(""),
					 _target_channel(0),
					 _params(0),
					 _splitted_channels(0),
					 _splitted_args(0),
					 _commands(0),
					 _to_delete(false)
{
#if DEBUG == 1
	std::cout << BLUE << "DEBUG: User constructor called with fd param" << NC << std::endl;
#endif
}

User::~User(void)
{
	//TODO delete tout ce qui a été alloué par des new
#if DEBUG == 1
	std::cout << BLUE << "DEBUG: User destructor" << NC << std::endl;
#endif
}

void User::set_nickname(std::string nickname)
{
	_nickname = nickname;
}

void User::set_username(std::string username)
{
	_username = username;
}

void User::set_realname(std::string realname)
{
	_realname = realname;
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

void User::fill_commands_vector()
{
	t_cmd new_command;
	std::string s = _request;
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
		_commands.push_back(new_command);
		s.erase(0, pos + delimiter.length());
	}
	int i = 0;
	for (std::vector<t_cmd>::iterator it = _commands.begin(); it != _commands.end(); it++)
	{
#if DEBUG == 1
		std::cout << "--COMMAND N° " << i++ << "--" << std::endl;
#endif
		store_prefix(it);
		store_command(it);
		store_params(it);
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
}

std::string User::get_nickname(void) const
{
	return _nickname;
}

std::string User::get_username(void) const
{
	return _username;
}

std::string User::get_realname(void) const
{
	return _realname;
}

std::string User::get_hostname(void) const
{
	return _hostname;
}

std::string User::get_modes(void) const
{
	return _modes;
}

std::string User::get_away_mssg(void) const
{
	return _away_mssg;
}

std::string User::get_password(void) const
{
	return _password;
}

int User::get_fd(void) const
{
	return _fd;
}

int User::get_channels_nb(void) const
{
	return _channels.size();
}

std::vector<std::string> User::get_params(void) const
{
	return _params;
}

std::string User::get_prefix(void) const
{
	return _prefix;
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
	return _params.size();
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

void User::store_command(std::vector<t_cmd>::iterator it)
{
	if (!(*it)._unparsed.empty())
	{
		int i = 0;
		i = store_string_until_char(&(*it)._command, &(*it)._unparsed, ' ', i);
		(*it)._unparsed.replace(0, i, "");
		if (ft::string_end_with((*it)._command, "\r\n"))
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
		if (ft::string_end_with(_command, "\r\n"))
			_command.resize(_command.size() - 2);
	}
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
		ft::split_string_to_vector(&(*it)._params, &(*it)._unparsed, ' ');
		patch_params(&(*it)._params);
	}
}

void User::store_params()
{
	if (_request != "")
	{
		ft::split_string_to_vector(&_params, &_request, ' ');
		patch_params(&_params);
	}
}

void User::set_params(std::vector<std::string> params)
{
	_params = params;
}
void User::set_prefix(std::string prefix)
{
	_prefix = prefix;
}
void User::set_command(std::string command)
{
	_command = command;
}

void User::be_added_to_channel(Channel *channel)
{
	if (channel->get_members_nb() >= 1)
		channel->new_member(this, false);
	else
	{
		//TODO Si non on va devenir operateur
		channel->new_member(this, true);
	}
}

void User::set_fd(int fd)
{
	_fd = fd;
}

void User::increase_channel_nb(void)
{
	if (_channels_nb >= 0)
		_channels_nb++;
	else
	{
#if DEBUG == 1
		std::cout << RED << "USER: Error with nb of channels (++)." << std::endl;
#endif
	}
}

void User::decrease_channel_nb(void)
{
	if (_channels_nb == USER_MAXCHAN)
	{
#if DEBUG == 1
		std::cout << RED << "USER: Error with nb of channels (--)." << std::endl;
#endif
	}
	_channels_nb--;
}

//Les verifications en termes de USER_MACHAN doivent etre faites au prealable
//TODO: si la channel existe pas on l'ajoute pas mais on increase qd meme (question baudoin)
void User::add_channel_to_list(Channel *channel)
{
	if (channel)
		_channels.push_back(channel);
	increase_channel_nb();
}

void User::remove_channel_from_list(Channel *channel)
{
	std::string targeted_chan = channel->get_name();

	for (std::vector<Channel *>::iterator it = _channels.begin(); it != _channels.end(); it++)
	{
		if (targeted_chan.compare((*it)->get_name()) == 0)
		{
			_channels.erase(it);
			decrease_channel_nb();
			break;
		}
	}
}

Channel *User::get_target_channel(void) const
{
#if MALATINI == 1
	std::cout << PURPLE << _target_channel->get_name() << NC << std::endl;
#endif
	return _target_channel;
}

void User::set_target_channel(Channel *channel)
{
	_target_channel = channel;
#if MALATINI == 1
	if (!channel)
		std::cout << RED << "Error : set a target channel that is NULL!" << NC << std::endl;
	else
		std::cout << PURPLE << "Channel has been set to" << channel->get_name() << NC << std::endl;
#endif
}

bool User::get_display_who(void) const
{
	return _display_who;
}

std::vector<Channel *> User::get_channels(void) const
{
	return _channels;
}

std::vector<std::string> User::get_topic_params(void) const
{
	return _topic_params;
}

void User::set_display_who(bool display)
{
	_display_who = display;
}

void User::add_topic_params(std::string str)
{
	_topic_params.push_back(str);
}

void User::clear_topic_params(void)
{
	_topic_params.clear();
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

void User::display_params(void)
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

std::ostream &operator<<(std::ostream &COUT, User *user)
{
	COUT << user->get_nickname();
	return (COUT);
}