#include "../IRC.hpp"

void	IRC::execTOPIC(Command const &cmd, std::vector<t_clientCmd> &responseQueue)
{
	User	*user(cmd._user);
	string	resp;

	// cmd.Print();

	if (cmd._params.empty())
	{
		resp = getResponseFromCode(user, ERR_NEEDMOREPARAMS, (string[]){ cmd._type });
		responseQueue.push_back(std::make_pair(user->_fd, resp));
		return;
	}

	string const	&chanName(cmd._params[0]);
	Channel	*chan =	(_channels.find(chanName) != _channels.end())
				  ? _channels[chanName]
				  : NULL;
	if (!chan || !chan->IsVisible(user))
	{
		// Channel not found or not visible to user
		if (cmd._params.size() == 1)
			resp = getResponseFromCode(user, ERR_NOSUCHCHANNEL, (string[]){ chanName });
		else
			resp = getResponseFromCode(user, ERR_NOTONCHANNEL, (string[]){ chanName });
	}
	else if (cmd._params.size() == 1)
	{
		// Query channel's topic
		if (chan->_topic.empty())
			resp = getResponseFromCode(user, RPL_NOTOPIC, (string[]){ chanName });
		else
			resp = getResponseFromCode(user, RPL_TOPIC, (string[]){ chanName, chan->_topic });
	}
	else if (!chan->IsOperator(user))
		// User trying to change topic is not operator of channel
		resp = getResponseFromCode(user, ERR_CHANOPRIVSNEEDED, (string[]){ chanName });
	else
	{
		// Operator changed topic of channel, inform everyone
		chan->_topic = cmd._params[1];
		appendUserNotif(
			user,
			(string[]){ "TOPIC", chanName, ":" + chan->_topic, "" },
			chan->_users, responseQueue
		);
	}
	if (!resp.empty())
		responseQueue.push_back(std::make_pair(user->_fd, resp));
}
