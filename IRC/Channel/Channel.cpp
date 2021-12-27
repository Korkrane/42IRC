#include "Channel.hpp"

// Check if name is legal to be used as channel's name
bool	Channel::NameLegal(string const &name)
{
	static string const	illegalChars(CHAN_ILLEGAL_CHARS);
	static std::set<char> const	illegalCharSet(illegalChars.begin(), illegalChars.end());

	std::set<char>		nameCharSet(name.begin(), name.end());
	std::vector<char>	inter(illegalChars.size());

	std::vector<char>::iterator	it(
		std::set_intersection(
			illegalCharSet.begin(), illegalCharSet.end(),
			nameCharSet.begin(), nameCharSet.end(),
			inter.begin()
		)
	);
	return std::distance(inter.begin(), it) == 0;
}

Channel::Channel(string const &name, User *creator) :
	_name(name),
	_limitNumUsers(-1),
	_secret(false)
{
	_operators.insert(creator);
	_users.insert(creator);
}

Channel::~Channel()
{}

// Attempt to add user to the channel using key. Return 0 if user
// is added successfully, or a numeric representation of error if fails
int	Channel::TryAddUser(User *user, string const &key)
{
	if (IsJoined(user))
		return 0;

	if (!_key.empty() && key != _key)
		return ERR_BADCHANNELKEY;
	_users.insert(user);
	return 0;
}

// Remove a user from channel. Return number of user left in the channel
int	Channel::RemoveUser(User *user)
{
	_users.erase(user);
	_operators.erase(user);
	return _users.size();
}

// Check if user has joined channel
bool	Channel::IsJoined(User *user)	{ return (_users.find(user) != _users.end()); }

// Check if user can look up info of channel
bool	Channel::IsVisible(User *user)	{ return (!_secret || IsJoined(user)); }

// Check if user is operator of channel
bool	Channel::IsOperator(User *user)	{ return (_operators.find(user) != _operators.end()); }
