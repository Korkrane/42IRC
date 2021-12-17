#include <IRC.hpp>

Channel::Channel(std::string name, User *user) : _name(name), _prefix(name[0]), _topic(""), _has_topic(false), _modes(CHANNEL_MODES), _handle_modes(true), _channel_owner(user), _key(""), _has_key(false), _members_nb(0), _operators_nb(0) //Attention a incrementer les deux derniers
{
#if DEBUG == 1
	std::cout << "Channel constructor called" << std::endl;
#endif
	this->set_owner(user);
	return;
}

void Channel::set_owner(User *user)
{
	this->_channel_owner = user;
}

User *Channel::get_owner(void)
{
	return (this->_channel_owner);
}

bool Channel::is_channel_owner(User *user)
{
	if (user == this->get_owner())
		return (true);
	return (false);
}

char Channel::get_mode_sign(void)
{
	return (this->_mode_sign);
}

void Channel::set_mode_sign(char c)
{
	this->_mode_sign = c;
}

Channel::~Channel(void)
{
#if DEBUG == 1
	std::cout << "Channel desconstructor called" << std::endl;
#endif
	///TODO: Attention verifier pas de leaks
	//this->delete_channel_from_server();
	return;
}

void Channel::set_name(std::string name)
{
	this->_name = name;
#if DEBUG == 1
	std::cout << "name has been set to " << name << std::endl;
#endif
}

void Channel::set_topic(std::string topic)
{
	this->_topic = topic;
	this->_has_topic = true;
}

void Channel::set_modes(std::string modes)
{
	this->_modes = modes;
}

/*** GETTERS ***/
std::string Channel::get_name(void) const
{
	return this->_name;
}

std::string Channel::get_topic(void) const
{
	std::string topic = this->_topic;
	return (topic);
}

std::string Channel::get_modes(void) const
{
	return (this->_modes);
}

unsigned int Channel::get_members_nb(void) const
{
	return (this->_members_nb);
}

std::vector<User *> Channel::get_members(void) const
{
	return (this->_users);
}

std::vector<User *> Channel::get_operators(void) const
{
	return (this->_operators);
}

bool Channel::user_is_operator(User *user)
{
	if (!user)
		return (false);

	std::vector<User *>::iterator it = this->_operators.begin();
	std::vector<User *>::iterator ite = this->_operators.end();
	std::string nick_name;

	while (it != ite)
	{
		nick_name = (*it)->get_nickname();
		if (nick_name == user->get_nickname())
		{
			return (true);
		}
	}
	return (false);
}

bool Channel::user_is_member(User *user)
{
	std::vector<User *>::iterator it = this->_users.begin();
	std::vector<User *>::iterator ite = this->_users.end();
	std::string nick_name;

	while (it != ite)
	{
		nick_name = (*it)->get_nickname();
		if (nick_name == user->get_nickname())
		{
			return (true);
		}
		it++;
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

void Channel::newMember(User *user, bool user_operator)
{
	//TODO: Attention si c'est egal a true et qu il n y a pas d'owner le user devient channel owner
	(void)user;
	(void)user_operator;
	if (!user)
	{
		//	std::cout << "ERROR ! User is NULL" << std::endl;
		return;
	}
	/* */
	this->_users.push_back(user);
	//std::cout << "ICI" << std::endl;
	this->_members_nb++;
	if (user_operator == true)
		newOperator(user);
	return;
}

void Channel::newOperator(User *user)
{
	if (!user)
	{
		//std::cout << "ERROR ! User is NULL" << std::endl;
		return;
	}
	/* */
	this->_operators.push_back(user);
	this->_operators_nb++;
	return;
}

void Channel::delete_owner()
{
	this->_channel_owner = 0;
}

void Channel::delete_operator(User *user)
{

	std::vector<User *>::iterator it = this->_operators.begin();
	std::vector<User *>::iterator ite = this->_operators.end();

	while (it != ite)
	{
		if ((*it)->get_nickname() == user->get_nickname())
		{
			this->_operators.erase(it);
			this->_members_nb--;
			return;
		}
		it++;
	}
}

void Channel::deleteMember(User *user)
{
	std::vector<User *>::iterator it = this->_users.begin();
	std::vector<User *>::iterator ite = this->_users.end();

	while (it != ite)
	{
		if ((*it)->get_nickname() == user->get_nickname())
		{
#if DEBUG == 1
			std::cout << "test" << std::endl;
#endif
			this->_users.erase(it);
			this->_members_nb--;
			return;
		}
		it++;
	}
}

void Channel::removeFromOperators(User *user)
{
	//Chercher si le Users  est dans la liste
	//si oui, le retirer
	if (!user)
		return;

	std::vector<User *>::iterator it = this->_operators.begin();
	std::vector<User *>::iterator ite = this->_operators.end();

	(void)it;
	(void)ite;
	/* */
	while (it != ite)
	{
		if ((*it)->get_nickname() == (*ite)->get_nickname())
		{
			this->_operators.erase(it);
			return;
		}
	}
	return;
}

//TODO à tester
bool Channel::channelHasOperator(void)
{
	unsigned int size = this->_operators.size();
	if (size <= 0)
		return (false);
	std::vector<User *>::iterator it = this->_operators.begin();
	if (!(*it))
		return (false);
	return (true);
}

bool Channel::channelHasUsers(void)
{
	unsigned int size = this->_operators.size();
	if (size <= 0)
		return (false);
	std::vector<User *>::iterator it = this->_users.begin();
	if (!(*it))
		return (false);
	return (true);
}

unsigned int Channel::get_operators_nb(void) const
{
	std::vector<User *> operators = this->get_operators();
	unsigned int size = operators.size();
	return (size);
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
	(void)target_name;
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
	bool res = this->_handle_modes;
	return (res);
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
	char k = 'k';
	std::string modes = this->get_modes();
	if (modes.find(k) != std::string::npos)
		return (true);
	return (false);
}

/**
 * @brief
 *
 * @param target_key
 * @return true
 * @return false
 * TODO:  tester, je n'ai pas trouve d'exigences dans la rfc concernant les key
 */
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
	return;
}

void Channel::set_handle_modes(bool handle)
{
	this->_handle_modes = handle;
}

void Channel::set_channel_prefix(void)
{
	std::string name = this->get_name();
	char prefix = name[0];
	this->_prefix = prefix;
	return;
}

char Channel::get_channel_prefix(void) const
{
	std::string name = this->get_name();
	char prefix = name[0];
	return (prefix);
}

std::ostream &operator<<(std::ostream &COUT, Channel *channel)
{
	COUT << channel->get_name();
	return (COUT);
}

bool Channel::check_channel_modes(std::string target_modes)
{
	(void)target_modes;
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
	if (this->get_members_nb() >= CHAN_MAXCAPACITY)
		return (true);
	return (false);
}

std::vector<int> Channel::get_members_fd(void) const
{
	std::vector<int> fds;
	std::vector<User *> users = this->get_members();
	std::vector<User *>::iterator it = users.begin();
	std::vector<User *>::iterator ite = users.end();
	int tmp;
	while (it != ite)
	{
		tmp = (*it)->get_fd();
		fds.push_back(tmp);
		it++;
	}
	return (fds);
}

bool Channel::get_has_topic(void) const
{
	return (this->_has_topic);
}

bool Channel::get_has_key(void)
{
	return (this->_has_key);
}

void Channel::set_has_key(void)
{
	this->_has_key = true;
}

void Channel::unset_has_key(void)
{
	this->_has_key = false;
}

//TODO : check si la cle est correcte devrait etre fait au prealable
void Channel::set_key(std::string key)
{
	this->_key = key;
}

void Channel::drop_key(void)
{
	this->_key = "";
}

void Channel::set_topic(User *user, IRC *server, std::vector<std::string> topic)
{
	(void)user;
	(void)server;

	this->set_has_topic();
	std::string str_topic;
	std::vector<std::string>::iterator it = topic.begin();
	std::vector<std::string>::iterator ite = topic.end();

	while (it != ite)
	{
		str_topic += (*it);
		if (it + 1 == ite)
			break;
		str_topic += " ";
		it++;
	}
	this->_topic = str_topic;
}

void Channel::clear_topic(User *user, IRC *server, std::vector<std::string> topic)
{
	(void)user;
	(void)server;
	(void)topic;
	this->_topic = "";
	this->_has_topic = false;
}

void Channel::set_has_topic()
{
	this->_has_topic = true;
}

void Channel::displayMode(void)
{
	bool handles = this->get_handle_modes();
	if (handles)
	{
		//if (this->get_channel_prefix() != '+')//Does not support channel modes
		//std::cout << "Channel :" << this->get_name() << " has mode(s) " << this->get_modes() << std::cout;
	}
	else
	{
		//std::cout << "Channel : careful, this channel should not handle modes : " << this->get_modes() << std::cout;
	}
	return;
}

std::string Channel::get_key(void)
{
	std::string key = this->_key;
	return (key);
}