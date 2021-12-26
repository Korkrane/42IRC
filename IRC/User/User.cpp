#include "User.hpp"
#include "../Channel/Channel.hpp"

User::User(int fd) :
	_fd(fd),
	_passwordOK(false),
	_registered(false),
	_nick(DEFAULT_NAME),
	_uname(DEFAULT_NAME),
	_rname(DEFAULT_NAME)
{
	bzero(_mode, sizeof(_mode));
}

User::~User()
{}

void	User::registrationOK()
{
	_registered = true;
	_prefix = string(":") + _nick + '!' + _uname + '@' + USR_HOST;
}

void	User::SetNick(string const &nick)
{
	_nick = nick;
	if (_uname != DEFAULT_NAME)
		registrationOK();
}

void	User::SetUsername(string const &uname)
{
	_uname = uname;
	if (_nick != DEFAULT_NAME)
		registrationOK();
}

void	User::SetMode(string const &modes)
{
	bool	plus = (modes[0] != '-');
	string	letters((modes[0] == '+' || modes[0] == '-')
						? modes.substr(1, modes.size() - 1)
						: modes);
	for (string::iterator it(letters.begin()); it != letters.end(); ++it)
	{
		int		numMode;
		switch (*it)
		{
			case 'a': numMode = MODE_A; break;
			case 'i': numMode = MODE_I; break;
			case 'o': numMode = MODE_O; break;
			case 'r': numMode = MODE_R; break;
			case 'w': numMode = MODE_W; break;
			case 's': numMode = MODE_S; break;
			case 'O': numMode = MODE_BO; break;
			case 'B': numMode = MODE_BB; break;
			default: continue;
		}
		_mode[numMode] = plus;
	}
}

// Attempt to join channel. Return 0 if joined successfully, otherwise a
// numeric representation of error if fails
int	User::JoinChannel(Channel *chan, string const &key)
{
	if (_channelsJoined.find(chan) != _channelsJoined.end())
		return 0;

	int	ret(chan->AddUser(this, key));
	if (!ret)
		_channelsJoined.insert(chan);
	return ret;
}
