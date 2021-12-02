#include "../../includes/channel.hpp"

/*
** Last editor: Mahaut
** TODO: voir comment initialiser la clients list
*/
Channel::Channel(std::string name, Client *client) : _name(name), _topic("null"), _modes("null"), _operators(0), _clients(0), _banned_clients(0), _invited_clients(0), _voice_priv_clients(0), _channel_owner(0), _members_nb(0), _topic_set(false)
{
#if DEBUG
	std::cout << "Channel constructor called" << std::endl;
#endif
	return ;
}

/*
** TODO: voir si il faut mieux le mettre en prive et ne pas l'utiliser
*/
Channel::Channel(void) : _name("null"), _topic("null"), _modes("null"), _operators(0), _clients(0), _banned_clients(0), _invited_clients(0), _voice_priv_clients(0), _channel_owner(0), _members_nb(0), _topic_set(false)
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
std::vector<Client *>	Channel::get_member_list(void) const
{
	std::vector<Client *> member_list;
	member_list = this->_clients;
#if DEBUG
	std::cout << "get_member_list called, the list is : " << std::endl;
	//TODO: faire fonction pour afficher tous les clients
#endif
	return (member_list);
}

/*
** Voir comment les operateurs sont ajoutes
*/
std::vector<Client *>	Channel::get_operators(void) const
{
	std::vector<Client *> operators = this->_operators;
#if DEBUG
	std::cout << "get_operator called, the list is : " << std::endl;
	//TODO: faire fonction pour afficher les operateurs
#endif
	return (operators);
}

/*
** Utils - clients
*/


//TODO: a tester
//L'user doit etre identifiable par son nickname
//fonction dediee
bool				Channel::user_is_banned(Client *client)
{
	if (!client)
		return (false);

	/*
	** On va chercher si le client fait partie du vecteur
	*/
	std::vector<Client *>::iterator it = this->_banned_clients.begin();
	std::vector<Client *>::iterator ite = this->_banned_clients.end();
	std::string nickName;
	while (it != ite)
	{
		nickName = (*it)->get_nickname();
		if (nickName == client->get_nickname())
		{
#if DEBUG
	std::cout << "user " << nickName << " is banned" << std::endl;
#endif
			return (true);
		}
	}
	return (false);
}

/*
** On identifie son client grace a son nickname (unique)
** voir cas ou il n'y a qu un seul user (a tester)
*/
bool				Channel::user_is_operator(Client *client)
{
	if (!client)
		return (false);

	std::vector<Client *>::iterator it = this->_operators.begin();
	std::vector<Client *>::iterator ite = this->_operators.end();
	std::string nickName;
	while (it != ite)
	{
		nickName = (*it)->get_nickname();
		if (nickName == client->get_nickname())
		{
#if DEBUG
	std::cout << "user " << nickName << " is operator" << std::endl;
#endif
			return (true);
		}
	}
	return (false);
}

/*
** A tester (voir s il n y a qu'un seul user)
*/
bool				Channel::user_is_member(Client *client)
{
	if (!client)
		return (false);
	std::vector<Client *>::iterator it = this->_clients.begin();
	std::vector<Client *>::iterator ite = this->_clients.end();
	std::string nickName;
	while (it != ite)
	{
		nickName = (*it)->get_nickname();
		if (nickName == client->get_nickname())
		{
#if DEBUG
	std::cout << "user " << nickName << " is member of the channel" << std::endl;
#endif
			return (true);
		}
	}
	return (false);
}

/*
** A tester, voir si necessaire pour la partie mandatory
*/
bool				Channel::user_is_invited(Client *client)
{
	if (!client)
		return (false);
	std::vector<Client *>::iterator it = this->_invited_clients.begin();
	std::vector<Client *>::iterator ite = this->_invited_clients.end();
	std::string nickName;
	while (it != ite)
	{
		nickName = (*it)->get_nickname();
		if (nickName == client->get_nickname())
		{
#if DEBUG
	std::cout << "user " << nickName << " is invited to the channel" << std::endl;
#endif
			return (true);
		}
	}
	return (false);
}

/*
** voir cas d'utilisation
*/
bool				Channel::user_is_owner(Client *client)
{
	if (!client)
		return (false);
	if (client->get_nickname() == this->_channel_owner->get_nickname())
	{
#if DEBUG
		std::cout << "The user " << client->get_nickname() << "is the owner of the channel" << std::endl;
#endif
		return (true);
	}
	return (false);
}

/*
** Utils pour ajouter un user sans doublon
** A tester
*/
bool				Channel::isNicknameUnique(Client *client)
{
	if (!client)
		return (false);
	std::vector<Client *>::iterator it = this->_clients.begin();
	std::vector<Client *>::iterator ite = this->_clients.end();
	std::string nickName;
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
	return (true);
}

/*
** Adds a member to the client's list
** It is a vector so it's easy to add something
** TODO: A tester (voir free membres client ?)
*/
void				Channel::newMember(Client *client)
{
	if (!client)
		return ;
	if (this->isNicknameUnique(client) == true)
	{
		this->_clients.push_back(client);
		this->_members_nb++;
		return ;
	}
#if DEBUG
	std::cout << "New member added, nickname is " << client->get_nickname() << std::endl;
#endif
	return ;
}

/*
** Il faut le chercher dans la liste et si on le trouve on le supprime
*/
void 				Channel::deleteMember(Client *client)
{
	if (!client)
		return ;

	std::vector<Client *>::iterator it = this->_clients.begin();
	std::vector<Client *>::iterator ite = this->_clients.end();

	while (it != ite)
	{
		if ((*it)->get_nickname() == (*ite)->get_nickname())
		{
			this->_clients.erase(it);
			this->_members_nb--;
#if DEBUG
		std::cout << "Member " << (*it)->get_nickname() << "has been succesfully removed from the clients vector." << std::endl;
#endif
			return ;
		}
	}
#if DEBUG
	std::cout << "Client was not found, enable to delete the client passed in argument" << std::endl;
#endif
	return ;
}
void				Channel::printMemberInfo(Client *client)
{
	if (!client)
		return ;
	return ;
}

/*
** Va permettre d'enlever le client de la liste des operateurs
** A priori celui-ci peut choisir de se retirer via une commande
** a revoir
*/
void				Channel::removeFromOperators(Client *client)
{
	//Chercher si le client est dans la liste
	//si oui, le retirer

	if (!client)
		return ;

	std::vector<Client *>::iterator it = this->_operators.begin();
	std::vector<Client *>::iterator ite = this->_operators.end();

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
	return ;
}

/*
** Info supplementaire sur la channel
** A tester
*/
bool				Channel::channelHasOperator(void)
{
	std::vector<Client *>::iterator it = this->_operators.begin();
	if (!(*it))
		return (false);
	return (true);
}

/*
** A tester
*/
bool				Channel::channelHasBanned(void)
{
	std::vector<Client *>::iterator it = this->_banned_clients.begin();
	if (!(*it))
		return (false);
	return (true);
}

bool				Channel::channelHasClients(void)
{
	std::vector<Client *>::iterator it = this->_clients.begin();
	if (!(*it))
		return (false);
#if debug
	std::cout << "Channel has " << this->get_members_nb() << " members" << std::endl;
#endif
	return (true);
}

/*
** Display / Debug
*/
void				Channel::displayChannelInfo(void)
{
	std::cout << "------- Displaying Channel ["  << this->get_name() << "] -------" << std::endl;
	this->displayTopic();
	this->displayMembers();
	this->displayOperators();
	this->displayBanned();
	return ;
}

/*
** Voir si on veut afficher autre chose que nickname
*/
void				Channel::displayMembers(void)
{
	std::cout << "------- Listing Members / Clients -------" << std::endl;
	std::vector<Client*>::iterator it = this->_clients.begin();
	std::vector<Client*>::iterator ite = this->_clients.end();
	unsigned int num = 0;
	while (it != ite)
	{
		std::cout << "client " << num << " - " << (*it)->get_nickname() << std::endl;
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

void				Channel::displayOperators(void)
{
	std::cout << "------- Listing Operators -------" << std::endl;
	if (this->channelHasOperator() == true)
	{
		std::vector<Client*>::iterator it = this->_operators.begin();
		std::vector<Client*>::iterator ite = this->_operators.end();
		unsigned int num = 0;
		while (it != ite)
		{
			std::cout << "operator " << num << " - " << (*it)->get_nickname() << std::endl;
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

void				Channel::displayBanned(void)
{
	//faire un check pour savoir s'il y a des banned ?
	std::cout << "------- Listing banned -------" << std::endl;
	if (this->channelHasBanned() == true)
	{
		std::vector<Client*>::iterator it = this->_banned_clients.begin();
		std::vector<Client*>::iterator ite = this->_banned_clients.end();
		unsigned int num = 0;
		while (it != ite)
		{
			std::cout << "Banned " << num << " - " << (*it)->get_nickname() << std::endl;
			it++;
		}
	}
	std::cout << "------------------------------" << std::endl;
	return ;
}
