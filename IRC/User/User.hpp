#ifndef USER_HPP
#define USER_HPP

#include "../../includes/Headers.hpp"

#define USR_HOST	"user.ft-irc.42.fr"
#define USR_MODES	"ios"

#define DEFAULT_NAME	"*"

enum	UserMode
{
	MODE_A,		//	away			(no)
	MODE_I,		//	invisible
	MODE_O,		//	operator
	MODE_R,		//	restricted		(no)
	MODE_W,		//	wallops			(no)
	MODE_S,		//	receive NOTICE
	MODE_BO,	//	local operator	(no)
	MODE_BB		//	bot				(no)
};

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
	bool	_mode[8];		// User's modes

	std::set<Channel *>	_channelsJoined;	// List of channels user has joined

	void	registrationOK();

public:
	User(int fd);
	virtual ~User();

	void	SetNick(string const &nick);
	void	SetUsername(string const &uname);
	void	SetMode(string const &modes);
	int		JoinChannel(Channel *chan, string const &key);

	friend class IRC;
};

#endif
