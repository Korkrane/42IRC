#include "../IRC.hpp"

// Create a new channel then return its pointer
Channel	*IRC::newChannel(string const &name, User *creator)
{
	Channel	*chan(new Channel(name, creator));
	_channels[name] = chan;
	creator->_channelsJoined.insert(chan);
	return chan;
}

// Return the pointer to the channel with name in argument, or NULL if not found
Channel	*IRC::getChannelByName(string const &name) const
{
	if (_channels.find(name) != _channels.end())
		return _channels.at(name);
	return NULL;
}

// Obtain a set of users who share any channels with the user. The resulting set
// excludes the user himself
std::set<User *>	IRC::getCommonUsers(User *user) const
{
	std::set<User *>	results;
	std::set<Channel *>::iterator it;
	for (it = user->_channelsJoined.begin(); it != user->_channelsJoined.end(); ++it)
		results.insert((*it)->_users.begin(), (*it)->_users.end());
	results.erase(user);
	return results;
}
