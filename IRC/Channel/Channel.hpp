#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "../../includes/Headers.hpp"
#include "../User/User.hpp"

#define CHAN_MODES	"ikot"	// biklmnopstv
#define CHAN_PREFIX	"#"

#define CHAN_ILLEGAL_CHARS	"\a,: "

class	Channel
{

private:
	string const		_name;		// Channel's name
	std::set<User *>	_users;		// List of users joined

	// Channel's modes

	std::set<User *>	_operators;	// List of operators
	string	_key;					// Channel's key
	string	_topic;					// Channel's topic
	bool	_invitationOnly;		// Only invited user can join

public:
	static bool	IsPrefix(char c);
	static bool	NameLegal(string const &name);

	Channel(string const &name, User *creator);
	virtual ~Channel();

	int	TryAddUser(User *user, string const &key);
	int	RemoveUser(User *user);

	bool	HasJoined(User *user) const;
	bool	IsOperator(User *user) const;

	friend class IRC;
};

#endif
