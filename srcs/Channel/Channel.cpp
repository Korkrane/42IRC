//#include "../../includes/irc.hpp"
#include <irc.hpp>

/*
** Last editor: Mahaut
** TODO: voir comment initialiser la Users s list
*/
Channel::Channel(std::string name, User *user) : _name(name), _topic("null"), _modes("null"), _operators(0), _users(0),  _channel_owner(0), _members_nb(0), _topic_set(false)
{
	(void)user;
#if DEBUG
	std::cout << "Channel constructor called" << std::endl;
#endif
	return ;
}

/*
** TODO: voir si il faut mieux le mettre en prive et ne pas l'utiliser
*/
Channel::Channel(void) : _name("null"), _topic("null"), _modes("null"), _operators(0), _users(0), _channel_owner(0), _members_nb(0), _topic_set(false)
{
#if DEBUG
	std::cout << "Channel default constructor called" << std::endl;
#endif
	return ;
}

/**
** TODO: fonction de delete pour tous les pointeurs
*/
Channel::~Channel(void)
{
#if DEBUG
	std::cout << "Channel desconstructor called" << std::endl;
#endif
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
	this->_topic_set = true;
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

/*
** A tester
** Voir comment les membres sont ajoutes
*/
std::vector<User *>	Channel::get_member_list(void) const
{
	std::vector<User *> member_list;
	member_list = this->_users;
#if DEBUG
	std::cout << "get_member_list called, the list is : " << std::endl;
	//TODO: faire fonction pour afficher tous les Users s
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
	//TODO: faire fonction pour afficher les operateurs
#endif
	return (operators);
}

/*
bool				Channel::user_is_banned(Users  *Users )
{
	if (!Users )
		return (false);

	std::vector<Users  *>::iterator it = this->_banned_users.begin();
	std::vector<Users  *>::iterator ite = this->_banned_users.end();
	std::string nickName;
	while (it != ite)
	{
		nickName = (*it)->get_nickname();
		if (nickName == Users ->get_nickname())
		{
#if DEBUG
	std::cout << "user " << nickName << " is banned" << std::endl;
#endif
			return (true);
		}
	}
	return (false);
}
*/

/**
** On identifie son Users  grace a son nickname (unique)
** voir cas ou il n'y a qu un seul user (a tester)
TODO: a remettre a jour avec la version User
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

/* A reprendre*/
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


/* A reprendre*/
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

/* */
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
** Adds a member to the Users 's list
** It is a vector so it's easy to add something
* TODO: a faire
*/
void				Channel::newMember(User *user)
{
	(void)user;
	/*
	if (!Users )
		return ;
	if (this->isNicknameUnique(Users ) == true)
	{
		this->_users.push_back(Users );
		this->_members_nb++;
		return ;
	}
#if DEBUG
	std::cout << "New member added, nickname is " << Users ->get_nickname() << std::endl;
#endif
*/
#if DEBUG
	std::cout << "new member was not added succesfully" << std::endl;
#endif
	return ;
}

/* */
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

//A reprendre
void				Channel::printMemberInfo(User *user)
{
	if (!user)
		return ;
#if DEBUG
	std::cout << "printMemberInfo function called" << std::endl;
#endif
	return ;
}

/* */
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

/*
** Info supplementaire sur la channel
** A tester
*/
bool				Channel::channelHasOperator(void)
{
	std::vector<User *>::iterator it = this->_operators.begin();
	if (!(*it))
		return (false);
	return (true);
}

/*
bool				Channel::channelHasBanned(void)
{
	std::vector<User *>::iterator it = this->_banned_users.begin();
	if (!(*it))
		return (false);
	return (true);
}
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

/**
** Display / Debug
*TODO: a reprendre
*/
void				Channel::displayChannelInfo(void)
{
	std::cout << "------- Displaying Channel ["  << this->get_name() << "] -------" << std::endl;
	this->displayTopic();
	this->displayMembers();
	this->displayOperators();
	//this->displayBanned();
	return ;
}

/* A reprendre */
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
	if (this->_topic_set == true)
		std::cout << "It has a topic and it is : " << this->get_topic() << std::endl;
	else
		std::cout << "Channel has no topic." << std::endl;
	std::cout << "------------------------" << std::endl;
	return ;
}

/* A reprendre */
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
	{
		std::cout << "This channel has no operator" << std::endl;
	}
	std::cout << "----------------------------" << std::endl;
	return ;
}

std::ostream& operator<<(std::ostream &COUT, Channel *channel)
{
	COUT << channel->get_name();
	return (COUT);
}
