#include <irc.hpp>

Channel::Channel(std::string name, User *user, IRC *server): _topic(""), _has_topic(false), _modes(""), _operators(0), _users(0),  _channel_owner(0), _key(""), _has_key(false), _members_nb(0), _serv(server)
{
	(void)user;
	(void)name;
#if DEBUG
	std::cout << "Channel constructor called" << std::endl;
#endif

	//Ajouter le user passe en parametre a la liste des users
	this->newMember(user, true);

	//Ajouter la channel a la liste contenue dans le serveur
	user->_IRCserver->add_channel(this);
	return ;
}

/**
 * @brief Destroy the Channel:: Channel object
 */
Channel::~Channel(void)
{
#if DEBUG
	std::cout << "Channel desconstructor called" << std::endl;
#endif
	//Supprimer de la liste des channels du IRCServer
	this->delete_channel_from_server();
	//Supprimer vider le vecteur de user
	//vider le vecteur d'operateurs
	return ;
}

void		Channel::delete_channel_from_server(void)
{
	this->_serv->drop_channel(this);
	return ;
}


/*** SETTERS ***/
void				Channel::set_name(std::string name)
{
	this->_name = name;
#if DEBUG
	std::cout << "name has been set to " << name << std::endl;
#endif
}

void				Channel::set_topic(std::string topic)
{
	this->_topic = topic;
	this->_has_topic = true;
#if DEBUG
	std::cout << "topic has been set to " << topic << std::endl;
#endif
}

void				Channel::set_modes(std::string modes)
{
	this->_modes = modes;
#if DEBUG
	std::cout << "modes has been set to " << modes << std::endl;
#endif
}

/*** GETTERS ***/
std::string			Channel::get_name(void) const
{
	std::string n = this->_name;
#if DEBUG
	std::cout << "name getter called, name is " << n << std::endl;
#endif
	return n;
}

std::string			Channel::get_topic(void) const
{
	std::string t = this->_topic;
#if DEBUG
	std::cout << "topic getter called, topic is " << t << std::endl;
#endif
	return (t);
}

std::string			Channel::get_modes(void) const
{
	std::string m = this->_modes;
#if DEBUG
	std::cout << "modes getter called, mode is " << m << std::endl;
#endif
	return (m);
}

unsigned int		Channel::get_members_nb(void) const
{
	unsigned int nb = this->_members_nb;
#if DEBUG
	std::cout << "The number of members is " << nb << std::endl;
#endif
	return (nb);
}

/**
 * @brief 
 * TODO: a tester 
 * @return std::vector<User *> 
 */
std::vector<User *>	Channel::get_members(void) const
{
	std::vector<User *> member_list;
	member_list = this->_users;
#if DEBUG
	std::cout << "get_member_list called, the list is : " << std::endl;
#endif
	return (member_list);
}

/*
** Voir comment les operateurs sont ajoutes
*/
std::vector<User *>	Channel::get_operators(void) const
{
	std::vector<User *> operators = this->_operators;
#if DEBUG
	std::cout << "get_operator called, the list is : " << std::endl;
#endif
	return (operators);
}

/** 
* On identifie son Users  grace a son nickname (unique)
* voir cas ou il n'y a qu un seul user (a tester)
* TODO: a remettre a jour avec la version User
*/

bool				Channel::user_is_operator(User  *user)
{
	if (!user)
		return (false);

	std::vector<User *>::iterator it = this->_operators.begin();
	std::vector<User *>::iterator ite = this->_operators.end();
	std::string nickName;

	(void)it;
	(void)ite;
	(void)nickName;
	/*
	while (it != ite)
	{
		nickName = (*it)->get_nickname();
		if (nickName == user->get_nickname())
		{
#if DEBUG
	std::cout << "user " << nickName << " is operator" << std::endl;
#endif
			return (true);
		}
	}
	*/
#if DEBUG
	std::cout << "user_is_operator is returning false" << std::endl;
#endif
	return (false);
}

/**
 * @brief 
 * 
 * @param user 
 * @return * A 
 * TODO: reprendre
 */
bool				Channel::user_is_member(User *user)
{
	if (!user)
		return (false);
	std::vector<User *>::iterator it = this->_users.begin();
	std::vector<User  *>::iterator ite = this->_users.end();
	std::string nickName;
	(void)it;
	(void)ite;
	(void)nickName;
	/*
	while (it != ite)
	{
		nickName = (*it)->get_nickname();
		if (nickName == user->get_nickname())
		{
#if DEBUG
	std::cout << "user " << nickName << " is member of the channel" << std::endl;
#endif
			return (true);
		}
	}
	*/
#if DEBUG
	std::cout << "user_is_member is returning false" << std::endl;
#endif
	return (false);
}


/**
 * @brief 
 * 
 * @param user 
 * @return true 
 * @return false 
 * TODO: revoir
 */
bool				Channel::user_is_owner(User *user)
{
	if (!user)
		return (false);
	/*
	if (user->get_nickname() == this->_channel_owner->get_nickname())
	{
#if DEBUG
		std::cout << "The user " << Users ->get_nickname() << "is the owner of the channel" << std::endl;
#endif
		return (true);
	}
	*/
	return (false);
}

/**
 * @brief 
 * 
 * @param user 
 * @return true 
 * @return false 
 * TODO: a reprendre
 */
bool				Channel::isNicknameUnique(User *user)
{
	if (!user)
		return (false);
	std::vector<User *>::iterator it = this->_users.begin();
	std::vector<User *>::iterator ite = this->_users.end();
	std::string nickName;

	(void)it;
	(void)ite;
	(void)nickName;
	/*
	while (it != ite)
	{
		if ((*it)->get_nickname() == (*ite)->get_nickname())
		{
#if DEBUG
	std::cout << "Nickname is already being used" << std::endl;
#endif
			return (false);
		}
	}
	*/
#if DEBUG
	std::cout << "isNicknameUnique is returning true" << std::endl;
#endif
	return (true);
}

/**
 * @brief 
 * Un user qui cree le channel devient automatiquement un operateur
 * 
 * @param user 
 * @param operator 
 */
void				Channel::newMember(User *user, bool user_operator)
{
	(void)user;
	if (!user)
		return ;
	this->_users.push_back(user);
	this->_members_nb++;
	if (user_operator == true)
		newOperator(user);
	return ;
}

void				Channel::newOperator(User *user)
{
	if (!user)
		return;
	this->_operators.push_back(user);
	this->_operators_nb++;
	return ;

}

/**
 * @brief 
 * 
 * @param user 
 * TODO: a reprendre
 */
void 				Channel::deleteMember(User *user)
{
	if (!user)
		return ;

	std::vector<User *>::iterator it = this->_users.begin();
	std::vector<User *>::iterator ite = this->_users.end();

	(void)it;
	(void)ite;
	/*
	while (it != ite)
	{
		if ((*it)->get_nickname() == (*ite)->get_nickname())
		{
			this->_users.erase(it);
			this->_members_nb--;
#if DEBUG
		std::cout << "Member " << (*it)->get_nickname() << "has been succesfully removed from the Users s vector." << std::endl;
#endif
			return ;
		}
	}
#if DEBUG
	std::cout << "Users  was not found, enable to delete the Users  passed in argument" << std::endl;
#endif
*/
#if DEBUG
	std::cout << "member was not succesfully deleted." << std::endl;
#endif
	return ;
}

/**
 * @brief 
 * 
 * @param user 
 * TODO: a reprendre
 */
void				Channel::printMemberInfo(User *user)
{
	if (!user)
		return ;
#if DEBUG
	std::cout << "printMemberInfo function called" << std::endl;
#endif
	return ;
}

/**
 * @brief 
 * 
 * @param user
 * TODO: a reprendre 
 */
void				Channel::removeFromOperators(User *user)
{
	//Chercher si le Users  est dans la liste
	//si oui, le retirer
	if (!user)
		return ;

	std::vector<User *>::iterator it = this->_operators.begin();
	std::vector<User *>::iterator ite = this->_operators.end();

	(void)it;
	(void)ite;
	/*
	while (it != ite)
	{
		if ((*it)->get_nickname() == (*ite)->get_nickname())
		{
			this->_operators.erase(it);
#if DEBUG
			std::cout << (*it)->get_nickname() << " has been successfully removed from operators." << std::endl;
			return ;
#endif
		}
	}
	*/
#if DEBUG
	std::cout << "user wad not successfully removed from operators" << std::endl;
#endif
	return ;
}

/**
* TODO: A tester
*/
bool				Channel::channelHasOperator(void)
{
	std::vector<User *>::iterator it = this->_operators.begin();
	if (!(*it))
		return (false);
	return (true);
}

/**
 * @brief 
 * 
 * @return true 
 * @return false 
 */
bool				Channel::channelHasUsers(void)
{
	std::vector<User *>::iterator it = this->_users.begin();
	if (!(*it))
		return (false);
#if debug
	std::cout << "Channel has " << this->get_members_nb() << " members" << std::endl;
#endif
	return (true);
}

void				Channel::displayChannelInfo(void)
{
	std::cout << "------- Displaying Channel ["  << this->get_name() << "] -------" << std::endl;
	this->displayTopic();
	this->displayMembers();
	this->displayOperators();
	return ;
}

/**
 * @brief 
 * TODO: a reprendre
 */
void				Channel::displayMembers(void)
{
	std::cout << "------- Listing Members / Users s -------" << std::endl;
	std::vector<User *>::iterator it = this->_users.begin();
	std::vector<User *>::iterator ite = this->_users.end();
	//unsigned int num = 0;
	while (it != ite)
	{
		//std::cout << "Users  " << num << " - " << (*it)->get_nickname() << std::endl;
		it++;
	}
	std::cout << "----------------------------------------" << std::endl;
	return ;
}


void				Channel::displayTopic(void)
{
	std::cout << "--- Displaying topic ---" << std::endl;
	if (this->_has_topic == true)
		std::cout << "It has a topic and it is : " << this->get_topic() << std::endl;
	else
		std::cout << "Channel has no topic." << std::endl;
	std::cout << "------------------------" << std::endl;
	return ;
}

/**
 * @brief 
 * TODO: a reprendre
 */
void				Channel::displayOperators(void)
{
	std::cout << "------- Listing Operators -------" << std::endl;
	if (this->channelHasOperator() == true)
	{
		std::vector<User *>::iterator it = this->_operators.begin();
		std::vector<User *>::iterator ite = this->_operators.end();
		//unsigned int num = 0;
		while (it != ite)
		{
		//	std::cout << "operator " << num << " - " << (*it)->get_nickname() << std::endl;
			it++;
		}
	}
	else
		std::cout << "This channel has no operator" << std::endl;
	std::cout << "----------------------------" << std::endl;
	return ;
}

bool				is_correct_channel_name(std::string target_name)
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

bool				Channel::get_handle_modes(void)
{
	bool res = this->_handle_modes;
#if DEBUG
	std::cout << BLUE << "DEBUG: " << "CHANNEL: does the channel handle modes ? " << res << std::endl;
#endif
	return (res);
}

bool				Channel::has_mode(char mode)
{
	(void)mode;
	std::string modes = this->get_modes();
	if (modes.find(mode) != std::string::npos)
		return (true);
	return (false);
}

bool				Channel::has_key_mode_on(void)
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
bool				Channel::is_correct_channel_key(std::string target_key)
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


void				Channel::set_handle_modes(void)
{
	char prefix = this->get_channel_prefix();
	if (prefix == '+')
	{
		this->set_handle_modes(false);
		this->set_modes("");
	}
	else
	{
		this->set_handle_modes(true);
	}
	return ;
}

void				Channel::set_handle_modes(bool handle)
{
	(void)handle;
	this->_handle_modes = handle;
	return ;
}

void				Channel::set_channel_prefix(void)
{
	std::string name = this->get_name();
	char prefix = name[0];
	this->_prefix = prefix;
#if DEBUG
	std::cout << BLUE << "DEBUG: " << "CHANNEL: " << "Prefix has been set to " << prefix << std::endl;
#endif
	return ;
}

char				Channel::get_channel_prefix(void) const
{
	std::string name = this->get_name();
	char prefix = name[0];
#if DEBUG
	std::cout << BLUE << "DEBUG: " << "CHANNEL: " << "Prefix is " << prefix << std::endl;
#endif
	return (prefix);
}

std::ostream& operator<<(std::ostream &COUT, Channel *channel)
{
	COUT << channel->get_name();
	return (COUT);
}

bool			Channel::check_channel_modes(std::string target_modes)
{
	(void)target_modes;
	//On doit verifier que les char qui constituent la string
	int i = 0;
	std::string	allowed(CHANNEL_VALID_MODES);
	int len = target_modes.length();

	while (i < len)
	{
		if (allowed.find(target_modes[i]) == std::string::npos)
		{
			#if DEBUG
				std::cout << BLUE << "DEBUG: " << "CHANNEL: " << "Find invalid char when checking modes string: " << target_modes[i] << std::endl;
			#endif
			return (false);
		}
		i++;
	}
	return (true);
}

/**
 * @brief 
 * 
 * @param target_modes 
 * TODO: a tester
 */
void			Channel::set_channel_modes(std::string target_modes)
{
	bool ok = check_channel_modes(target_modes);
	if (ok)
		this->_modes = target_modes;
	if (!ok)
	{
		//TODO: voir les modes par defaut (pour l'initialisation?)
		set_channel_modes("");
	}
	return ;
}

bool			Channel::is_full_channel(void) const
{
	unsigned int member = this->get_members_nb();
	if (member >= CHAN_MAXCAPACITY)
	{
#if DEBUG
	std::cout << BLUE << "DEBUG: " << "CHANNEL: The channel is full" << std::endl;
#endif
		return (true);
	}
	return (false);
}