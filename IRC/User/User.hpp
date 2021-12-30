#ifndef USER_HPP
#define USER_HPP

#include "../../includes/Headers.hpp"

#define USR_HOST		"user.ft-irc.42.fr"
#define USR_VALID_MODES	"aio"
#define USR_ALL_MODES	"aiorwsO"

#define DEFAULT_NAME	"*"
#define VALID_CHARS		"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-^_[]{}\\|"

class	User
{

private:
	int		_fd;			// fd of user's network client, used for unique identifier
	bool	_passwordOK;	// Has user entered good password ?
	bool	_registered;	// Is user registered ?
	string	_nick;			// Nickname
	string	_uname;			// Username
	string	_rname;			// Real name
	string	_prefix;		// User's prefix in network messages
	std::set<Channel *>	_joined;	// List of channels user has joined

	// User's modes

	string	_awayMsg;		// (a) Away message
	bool	_invisible;		// (i) Is invisible
	bool	_oper;			// (o) Is server operator

	void	registrationOK();

public:
	static bool	CheckNickValidChars(string const &nick);

	User(int fd);
	virtual ~User();

	bool	IsUsernameDefault() const;
	bool	IsAway() const;

	void	SetNick(string const &nick);
	void	SetUsername(string const &uname);
	string	GetModes() const;

	int		TryJoin(Channel *chan, string const &key);
	int		TrySetMode(bool plus, char mode);

	friend class IRC;
};

#endif
