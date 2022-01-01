#include "../IRC.hpp"

void	IRC::execNAMES(Command const &cmd, std::vector<t_clientCmd> &responseQueue)
{
	string const	&chanName = (cmd._params.empty())
							  ? "*" : cmd._params[0];
	User	*user(cmd._user);
	string	resp;

	Channel	*chan(getChannelByName(chanName));
	if (chan)
	{
		bool	joined(chan->HasJoined(user));
		string	names;
		names.reserve(1024);
		std::set<User *>::iterator it;
		for (it = chan->_users.begin(); it != chan->_users.end(); ++it)
		{
			if (!joined && (*it)->_invisible)	// not showing invisible users
				continue;
			if (chan->IsOperator(*it))
				names += "@";
			names += (*it)->_nick + " ";
		}
		if (!names.empty())
		{
			if (names[names.size() - 1] == ' ')
				// Remove last character if it's a space
				names.erase(names.size() - 1, 1);
			resp = getResponseFromCode(
				user,
				RPL_NAMREPLY,
				(string[]){ "= " + chanName, names }
			);
		}
	}
	resp += getResponseFromCode(user, RPL_ENDOFNAMES, (string[]){ chanName });
	pushToQueue(user->_fd, resp, responseQueue);
}
