#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "../../includes/Headers.hpp"
#include "../User/User.hpp"

#define CHAN_MODES	"bklo"	// biklmnopstv
#define CHAN_PREFIX	'#'

#define CHAN_ILLEGAL_CHARS	"\a,: "

class	Channel
{

private:
	string const		_name;		// Channel's name
	std::set<User *>	_operators;	// List of operators
	std::set<User *>	_users;		// List of users joined

	std::set<std::pair<string,string> >	_banned;	// List of pair nick/user banned
	string	_key;				// Channel's key
	int		_limitNumUsers;		// Maximum number of users
	bool	_secret;			// Is channel secret
	string	_topic;				// Channel's topic

public:
	static bool	NameLegal(string const &name);

	Channel(string const &name, User *creator);
	virtual ~Channel();

	int	TryAddUser(User *user, string const &key);
	int	RemoveUser(User *user);

	bool	IsJoined(User *user);
	bool	IsOperator(User *user);
	bool	IsVisible(User *user);

	friend class IRC;
};

#endif
