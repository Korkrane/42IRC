#include "../IRC.hpp"

void	IRC::execJOIN(Command const &cmd, std::vector<t_clientCmd> &responseQueue)
{
	User	*user(cmd._user);
	string	resp;

	if (cmd._params.empty())
	{
		resp = getResponseFromCode(user, ERR_NEEDMOREPARAMS, (string[]){ cmd._type });
		responseQueue.push_back(std::make_pair(user->_fd, resp));
		return;
	}
	// Make a new command NAMES
	Command	cmdNAMES(cmd);
	cmdNAMES._type = "NAMES";

	std::vector<string>	chanNames, chanKeys;
	::splitStr(chanNames, cmd._params[0], ",");
	if (cmd._params.size() > 1)
		::splitStr(chanKeys, cmd._params[1], ",");

	for (std::size_t i(0); i < chanNames.size(); ++i)
	{
		string const	&name(chanNames[i]);
		string const	&key = (i < chanKeys.size())
							 ? chanKeys[i]
							 : "";
		if (name[0] != CHAN_PREFIX || !Channel::NameLegal(name))
		{
			resp = getResponseFromCode(user, ERR_BADCHANMASK, (string[]){ name });
			responseQueue.push_back(std::make_pair(user->_fd, resp));
			continue;
		}
		Channel	*chan = (_channels.find(name) == _channels.end()) 
					  ? newChannel(name, user)
					  : _channels[name];
		int	ret(user->JoinChannel(chan, key));
		if (ret)
		{
			resp = getResponseFromCode(user, ret, (string[]){ name });
			responseQueue.push_back(std::make_pair(user->_fd, resp));
		}
		else
		{
			// Inform everyone in the channel that user has just joined
			resp = appendUserNotif(
				user,
				(string[]){ "JOIN", ":" + name, "" },
				chan->_users,
				responseQueue
			);
			// Execute command NAMES because we want the same response here
			cmdNAMES._params[0] = name;
			execNAMES(cmdNAMES, responseQueue);
		}
	}
}
