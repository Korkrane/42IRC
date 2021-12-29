#include "User.hpp"
#include "../Channel/Channel.hpp"

User::User(int fd) :
	_fd(fd),
	_passwordOK(false),
	_registered(false),
	_nick(DEFAULT_NAME),
	_uname(DEFAULT_NAME),
	_rname(DEFAULT_NAME),
	_invisible(false),
	_oper(false)
{}

User::~User()
{}

// Flag user as registered
void	User::registrationOK()
{
	_registered = true;
	_prefix = string(":") + _nick + '!' + _uname + '@' + USR_HOST;
}

// Check if user's username is default value
bool	User::IsUsernameDefault() const
{
	return (_uname == DEFAULT_NAME);
}

// Check if user is currently idling away
bool	User::IsAway() const
{
	return (!_awayMsg.empty());
}

// Set user's nickname. If user can be registered, register
void	User::SetNick(string const &nick)
{
	_nick = nick;
	if (_uname != DEFAULT_NAME)
		registrationOK();
}

// Set user's username. If user can be registered, register
void	User::SetUsername(string const &uname)
{
	_uname = uname;
	if (_nick != DEFAULT_NAME)
		registrationOK();
}

// Get string representation of user's modes
string	User::GetMode()
{
	string	mode("+");
	if (IsAway())
		mode += "a";
	if (_invisible)
		mode += "i";
	if (_oper)
		mode += "o";
	return mode;
}

// Attempt to join channel. Return 0 if joined successfully, otherwise a
// numeric representation of error if fails
int	User::TryJoin(Channel *chan, string const &key)
{
	if (_joined.find(chan) != _joined.end())
		return 0;

	int	ret(chan->TryAddUser(this, key));
	if (!ret)
		_joined.insert(chan);
	return ret;
}

// Try setting user's mode. Return 0 on success, -1 if ignored, else a
// positive error number
int	User::TrySetMode(bool plus, char mode)
{
	static string	allModes(USR_ALL_MODES);
	static string	validModes(USR_VALID_MODES);

	if (allModes.find(mode) == string::npos)
		// Mode not found
		return ERR_UMODEUNKNOWNFLAG;
	if (validModes.find(mode) == string::npos)
		// Mode ignored by server
		return -1;

	if (mode == 'a' && !plus && IsAway())
	{
		_awayMsg = "";
		return 0;
	}
	else if (mode == 'i' && plus != _invisible)
	{
		_invisible = !_invisible;
		return 0;
	}
	else if (!plus && _oper)	// mode o
	{
		_oper = false;
		return 0;
	}
	return -1;
}
