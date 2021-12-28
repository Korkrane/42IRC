#include "../IRC.hpp"

void	IRC::execNAMES(Command const &cmd, std::vector<t_clientCmd> &responseQueue)
{
	string const	&chanName = (cmd._params.empty())
							  ? "*" : cmd._params[0];
	User	*user(cmd._user);
	Channel	*chan(getChannelByName(chanName));
	string	resp;

	if (chan && chan->IsVisible(user))
	{
		// If channel exists and not secret, or if user is in the secret channel,
		// query is valid and processed
		string	chanType = (chan->_secret) ? "@ " : "= ";
		string	names;
		names.reserve(1024);
		std::set<User *>::iterator it;
		for (it = chan->_users.begin(); it != chan->_users.end(); ++it)
		{
			if (chan->IsOperator(*it))
				names += "@";
			names += (*it)->_nick;
			if (std::distance(it, chan->_users.end()) > 1)
				names += " ";
		}
		resp = getResponseFromCode(
			user,
			RPL_NAMREPLY,
			(string[]){ chanType + chanName, names }
		);
		responseQueue.push_back(std::make_pair(user->_fd, resp));
	}
	resp = getResponseFromCode(user, RPL_ENDOFNAMES, (string[]){ chanName });
	responseQueue.push_back(std::make_pair(user->_fd, resp));
}
