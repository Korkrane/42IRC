#include "../IRC.hpp"

// Check if nick is already in use
bool	IRC::checkNickInUse(string const &nick) const
{
	std::map<int, User *>::const_iterator	it;
	for (it = _users.begin(); it != _users.end(); ++it)
		if (it->second->_nick == nick)
			return true;
	return false;
}

// Send notice message to a user
void	IRC::sendNotice(User *user, std::vector<t_clientCmd> &responseQueue, string msg) const
{
	stringstream	ss;
	ss	<< _prefix
		<< " NOTICE " << user->_nick << " :"
		<< msg << CMD_DELIM;
	responseQueue.push_back(std::make_pair(user->_fd, ss.str()));
}

// Delete user from a channel when he leaves
void	IRC::userLeaveChannel(User *user, Channel *chan)
{
	user->_channelsJoined.erase(chan);
	if (chan->RemoveUser(user) == 0)
	{
		_channels.erase(chan->_name);
		delete chan;
	}
}

// Delete user from every channel he is in
void	IRC::removeFromAllChannel(User *user)
{
	while (!user->_channelsJoined.empty())
		userLeaveChannel(user, *(user->_channelsJoined.begin()));
}

// Send new user welcome messages with useful information about server
void	IRC::sendWelcomeMessage(User *user, std::vector<t_clientCmd> &responseQueue) const
{
	string	resp(
		  getResponseFromCode(user, RPL_WELCOME, (string[]){ user->_prefix })
		+ getResponseFromCode(user, RPL_YOURHOST, NULL)
		+ getResponseFromCode(user, RPL_CREATED, NULL)
		+ getResponseFromCode(user, RPL_MYINFO, NULL)
	);
	responseQueue.push_back(std::make_pair(user->_fd, resp));
	appendMOTDToQueue(user, responseQueue);
}
