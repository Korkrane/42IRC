#include "../IRC.hpp"

// Execute MODE for a channel
void	IRC::chanMODE(User *user, string const &chanName, string const &modes, std::vector<t_clientCmd> &responseQueue)
{
	
}

// Execute MODE for a user
void	IRC::userMODE(User *user, string const &nick, string const &modes, std::vector<t_clientCmd> &responseQueue)
{
	string	resp;

	if (nick != user->_nick)
		resp = getResponseFromCode(user, ERR_USERSDONTMATCH, NULL);
	else if (modes.empty())
		resp = getResponseFromCode(user, RPL_UMODEIS, (string[]){ user->GetMode() });
	if (!resp.empty())
	{
		responseQueue.push_back(std::make_pair(user->_fd, resp));
		return;
	}

	bool	plus(modes[0] != '-');
	size_t	i = ((plus && modes[0] == '+') || !plus);	// if first char is +/-, start at second char
	string	succeeded = plus ? "+" : "-";

	for (; i < modes.size(); ++i)
	{
		int	res(user->TrySetMode(plus, modes[i]));
		if (!res)
			succeeded += modes[i];
		else if (res > 0)
			resp += getResponseFromCode(user, res, (string[]){ modes.substr(i,1) });
	}
	resp += _prefix + " MODE " + nick + " :" + succeeded + CMD_DELIM;
	responseQueue.push_back(std::make_pair(user->_fd, resp));
}


void	IRC::execMODE(Command const &cmd, std::vector<t_clientCmd> &responseQueue)
{
	User	*user(cmd._user);

	if (cmd._params.empty())
	{
		string resp(getResponseFromCode(user, ERR_NEEDMOREPARAMS, (string[]){ cmd._type }));
		responseQueue.push_back(std::make_pair(user->_fd, resp));
		return;
	}

	string const	&name(cmd._params[0]);
	string const	&mode = (cmd._params.size() == 1)
						  ? "" : cmd._params[1];
	if (Channel::IsPrefix(name[0]))
		chanMODE(user, name, mode, responseQueue);
	else
		userMODE(user, name, mode, responseQueue);
}
