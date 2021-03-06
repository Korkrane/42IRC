#include <IRC.hpp>

Channel::Channel(std::string name, User *user) : _name(name), _prefix(name[0]), _topic("No topic is set"), _has_topic(false), _modes(CHANNEL_MODES), _handle_modes(true), _channel_owner(user), _key(""), _has_key(false), _members_nb(0), _operators_nb(0) //Attention a incrementer les deux derniers
{
#if DEBUG == 1
	std::cout << "Channel constructor called" << std::endl;
#endif
	set_owner(user);
}

Channel::~Channel(void)
{
#if DEBUG == 1
	std::cout << "Channel desconstructor called" << std::endl;
#endif
	///TODO: Attention verifier pas de leaks
	//this->delete_channel_from_server();
}

void Channel::set_owner(User *user)
{
	_channel_owner = user;
}

User *Channel::get_owner(void)
{
	return _channel_owner;
}

bool Channel::is_channel_owner(User *user)
{
	return (user == get_owner()) ? true : false;
}

void Channel::set_name(std::string name)
{
	_name = name;
}

void Channel::set_topic(std::string topic)
{
	_topic = topic;
	_has_topic = true;
}

void Channel::set_modes(std::string modes)
{
	_modes = modes;
}

std::string Channel::get_name(void) const
{
	return _name;
}

std::string Channel::get_topic(void) const
{
	return _topic;
}

std::string Channel::get_modes(void) const
{
	return _modes;
}

unsigned int Channel::get_members_nb(void) const
{
	return _members_nb;
}

std::vector<User *> Channel::get_members(void) const
{
	return _users;
}

std::vector<User *> Channel::get_operators(void) const
{
	return _operators;
}

bool Channel::user_is_operator(User *user)
{
	for (std::vector<User *>::iterator it = _operators.begin(); it != _operators.end(); it++)
	{
		if ((*it)->get_nickname() == user->get_nickname())
			return (true);
	}
	return (false);
}

bool Channel::user_is_member(User *user)
{
	for (std::vector<User *>::iterator it = _users.begin(); it != _users.end(); it++)
	{
		if ((*it)->get_nickname() == user->get_nickname())
			return (true);
	}
	return (false);
}

bool Channel::user_is_owner(User *user)
{
	if (user->get_nickname().compare(this->_channel_owner->get_nickname()) == 0)
	{
#if DEBUG
		std::cout << "The user " << user->get_nickname() << "is owner of the channel" << std::endl;
#endif
		return (true);
	}
	return (false);
}

//TODO: Attention si c'est egal a true et qu il n y a pas d'owner le user devient channel owner
//Baudoin: attention on check pas si pas d'owner ici du coup par rapport au comment ci dessus
void Channel::new_member(User *user, bool user_operator)
{
	_users.push_back(user);
	_members_nb++;
	if (user_operator == true)
		new_operator(user);
}

void Channel::new_operator(User *user)
{
	_operators.push_back(user);
	_operators_nb++;
}

void Channel::delete_owner()
{
	_channel_owner = 0;
}

void Channel::delete_operator(User *user)
{
	for (std::vector<User *>::iterator it = _operators.begin(); it != _operators.end(); it++)
	{
		if ((*it)->get_nickname() == user->get_nickname())
		{
			this->_operators.erase(it);
			this->_members_nb--;
			return;
		}
	}
}

void Channel::deleteMember(User *user)
{
	for (std::vector<User *>::iterator it = _users.begin(); it != _users.end(); it++)
	{
		if ((*it)->get_nickname() == user->get_nickname())
		{
			this->_users.erase(it);
			this->_members_nb--;
			return;
		}
	}
}

//TODO Question baudoin: Doublon de delete_operator ? + fonctions pas exactement identique, et quand on delete un ops on decrease le members_nb?
void Channel::removeFromOperators(User *user)
{
	for (std::vector<User *>::iterator it = _operators.begin(); it != _operators.end(); it++)
	{
		if ((*it)->get_nickname() == user->get_nickname())
		{
			_operators.erase(it);
			return;
		}
	}
}

bool Channel::channelHasOperator(void)
{
	return (_operators.size() <= 0) ? false : true;
}

bool Channel::channelHasUsers(void)
{
	return (_users.size() <= 0) ? false : true;
}

unsigned int Channel::get_operators_nb(void) const
{
	return _operators.size();
}

void Channel::displayChannelInfo(void)
{
	std::cout << "------- Displaying Channel [" << this->get_name() << "] -------" << std::endl;
	std::cout << "Number of members :" << this->get_members_nb() << std::endl;
	std::cout << "Number of operators :" << this->get_operators_nb() << std::endl;
	this->displayTopic();
	this->displayMembers();
	this->displayOperators();
	return;
}

void Channel::displayMembers(void)
{
	std::cout << "------- Listing Members / Users s -------" << std::endl;
	std::vector<User *>::iterator it = this->_users.begin();
	std::vector<User *>::iterator ite = this->_users.end();
	unsigned int num = 0;
	while (it != ite)
	{
		std::cout << "Users  " << num << " - " << (*it)->get_nickname() << std::endl;
		it++;
		num++;
	}
	std::cout << "----------------------------------------" << std::endl;
	return;
}

void Channel::displayTopic(void)
{
	std::cout << "--- Displaying topic ---" << std::endl;
	if (this->_has_topic == true)
		std::cout << "It has a topic and it is : " << this->get_topic() << std::endl;
	else
		std::cout << "Channel has no topic." << std::endl;
	std::cout << "------------------------" << std::endl;
	return;
}

void Channel::displayOperators(void)
{
	std::cout << "------- Listing Operators -------" << std::endl;
	if (this->channelHasOperator() == true)
	{
		std::vector<User *>::iterator it = this->_operators.begin();
		std::vector<User *>::iterator ite = this->_operators.end();
		unsigned int num = 0;
		while (it != ite)
		{
			std::cout << "operator " << num << " - " << (*it)->get_nickname() << std::endl;
			it++;
			num++;
		}
	}
	else
		std::cout << "This channel has no operator" << std::endl;
	std::cout << "----------------------------" << std::endl;
	return;
}

bool is_correct_channel_name(std::string target_name)
{
	std::string valid(CHANNEL_VALID_CHARS);
	//Le premier char doit faire partie des CHANNEL_VALID_CHARS (channel prefix)
	if (valid.find(target_name[0]) == std::string::npos)
		return (false);
	int length = target_name.length();
	if (length > 50)
		return (false);
	int i = 1;
	std::string forbidden(CHANNEL_FORBIDDEN_CHARS);
	while (i < length)
	{
		if (forbidden.find(target_name[1]) != std::string::npos)
			return (false);
		i++;
	}
	return (true);
}

bool Channel::get_handle_modes(void)
{
	return _handle_modes;
}

bool Channel::has_mode(char mode)
{
	std::string modes = this->get_modes();
	if (modes.find(mode) != std::string::npos)
		return (true);
	return (false);
}

bool Channel::has_key_mode_on(void)
{
	std::string modes = this->get_modes();

	return (modes.find('k') != std::string::npos) ? true : false;
}

//TODO:  tester, je n'ai pas trouve d'exigences dans la rfc concernant les key
bool Channel::is_correct_channel_key(std::string target_key)
{
	(void)target_key;
	//Si le channel n a pas de key, pas besoin de verifier si elle est correcte (on l'ignorera)

	//Est-ce que la commande gere les modes ?
	if (!this->get_handle_modes())
		return (true);
	//Est-ce que la commande gere le mode key ?
	if (!this->has_key_mode_on())
		return (true);
	//Ensuite on doit verifier qu elle respecte bien les regles grammaticales
	int len = target_key.length();
	if (len <= 0)
		return (false);
	return (true);
}

void Channel::set_handle_modes(void)
{
	char prefix = this->get_channel_prefix();
	if (prefix == '+')
	{
		this->set_handle_modes(false);
		this->set_modes("");
	}
	else
		this->set_handle_modes(true);
}

void Channel::set_handle_modes(bool handle)
{
	_handle_modes = handle;
}

void Channel::set_channel_prefix(void)
{
	_prefix = _name[0];
}

char Channel::get_channel_prefix(void) const
{
	return _name[0];
}

std::ostream &operator<<(std::ostream &COUT, Channel *channel)
{
	COUT << channel->get_name();
	return (COUT);
}

bool Channel::check_channel_modes(std::string target_modes)
{
	//On doit verifier que les char qui constituent la string
	int i = 0;
	std::string allowed(CHANNEL_VALID_MODES);
	int len = target_modes.length();

	while (i < len)
	{
		if (allowed.find(target_modes[i]) == std::string::npos)
			return (false);
		i++;
	}
	return (true);
}

//TODO: a tester
std::string Channel::get_unknown_mode(std::string target_modes)
{
	(void)target_modes;
	int i = 0;
	std::string allowed(CHANNEL_VALID_MODES);
	int len = target_modes.length();
	std::string error;
	while (i < len)
	{
		if (allowed.find(target_modes[i]) == std::string::npos)
		{
			error = target_modes[i];
			return (error);
		}
		i++;
	}
	return (" ");
}

void Channel::set_channel_modes(std::string target_modes)
{
	bool ok = check_channel_modes(target_modes);
	if (ok)
		this->_modes = target_modes;
	if (!ok)
	{
		//TODO: voir les modes par defaut (pour l'initialisation?)
		set_channel_modes("");
	}
}

bool Channel::is_full_channel(void) const
{
	return (this->get_members_nb() >= CHAN_MAXCAPACITY) ? true : false;
}

std::vector<int> Channel::get_members_fd(void)
{
	std::vector<int> fds;

	for (std::vector<User *>::iterator it = _users.begin(); it != _users.end(); it++)
		fds.push_back((*it)->get_fd());
	return (fds);
}

bool Channel::get_has_topic(void) const
{
	return _has_topic;
}

bool Channel::get_has_key(void)
{
	return _has_key;
}

void Channel::set_has_key(void)
{
	_has_key = true;
}

void Channel::unset_has_key(void)
{
	_has_key = false;
}

void Channel::set_key(std::string key)
{
	_key = key;
}

void Channel::drop_key(void)
{
	_key = "";
}

//TODO modif prot to remove user & server
void Channel::set_topic(User *user, IRC *server, std::vector<std::string> topic)
{
	(void)user;
	(void)server;

	this->set_has_topic();
	std::string str_topic;
	std::vector<std::string>::iterator it = topic.begin();
	it++;
	std::vector<std::string>::iterator ite = topic.end();
	unsigned int size = topic.size();
#if MALATINI == 1
	std::cout << PURPLE << "The size is " << size << NC << std::endl;
#endif
	std::string tmp;
	while (it != ite)
	{
		tmp = (*it);
		if (tmp[0] == ':')
		{
			tmp.erase(0, 1);
		}
		str_topic += tmp;
		if (it + 1 == ite)
			break;
		str_topic += " ";
		it++;
	}
	_topic = str_topic;
}

//TODO modif proto to remove everything and make it void
void Channel::clear_topic(User *user, IRC *server, std::vector<std::string> topic)
{
	(void)user;
	(void)server;
	(void)topic;
	_topic = "";
	_has_topic = false;
}

void Channel::set_has_topic()
{
	_has_topic = true;
}

std::string Channel::get_key(void)
{
	return _key;
}