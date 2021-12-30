#include "../IRC.hpp"

void	IRC::execWHO(Command const &cmd, std::vector<t_clientCmd> &responseQueue)
{
	string	resp;
	User	*user(cmd._user);

	if (cmd._params.empty())
	{
		resp = getResponseFromCode(user, ERR_NEEDMOREPARAMS, (string[]){ cmd._type });
		responseQueue.push_back(std::make_pair(user->_fd, resp));
		return ;
	}
	
	string const	&mask(cmd._params[0]);
	bool	o(cmd._params.size() > 1 && cmd._params[1].find('o') != string::npos);
	if (Channel::IsPrefix(mask[0]))
		ChannelWHO(user, mask, o, responseQueue);
	else
		UserWHO(user, mask, o, responseQueue);
	resp = getResponseFromCode(user, ERR_NEEDMOREPARAMS, (string[]){ mask });
	responseQueue.push_back(std::make_pair(user->_fd, resp));
}

void	IRC::ChannelWHO(User *user, string const &mask, bool o, std::vector<t_clientCmd> &responseQueue) const
{
	Channel	*chan(getChannelByName(mask));
	if (!chan)
		return;
	
	string	resp;
	User	*u;
	for (std::set<User *>::const_iterator it(chan->_users.begin());
		it != chan->_users.end(); ++it)
	{
		u = (*it);
		if ((user != u && u->_invisible) || (o && !u->_oper))
			// Do not include non-self invisible users or non-op in 'o' request
			continue;
		string	flag = (u->IsAway()) ? "G" : "H";
		if (u->_oper)
			flag += "*";
		if (chan->IsOperator(u))
			flag += "@";
		resp += getResponseFromCode(
			user, RPL_WHOREPLY,
			(string[]){ mask, u->_uname, u->_nick, flag, u->_rname }
		);
	}
	responseQueue.push_back(std::make_pair(user->_fd, resp));
}

//bool	maskMatchesStr(string const &mask, string const &str);

void	IRC::UserWHO(User *user, string const &mask, bool o, std::vector<t_clientCmd> &responseQueue) const
{
	// :irc.42.fr 352 nick21 #lol userooooo 127.0.0.1 irc.42.fr nick23 H :0 realname\r\n
	// Search in : hostname, server name, nickname, real name. De-invisible by realname and nickname
	
	// Check if mask contains illegal characters and star
	string	maskWithoutStar;
	for (string::const_iterator it(mask.begin()); it != mask.end(); ++it)
		if (*it != '*')
			maskWithoutStar += (*it);
	if (!User::CheckNickValidChars(maskWithoutStar))
		return;	// Do nothing if mask contains illegal character
	
	string	resp;
	User	*u;
	for (std::map<int, User *>::const_iterator it(_users.begin());
		it != _users.end(); ++it)
	{
		bool	showUser(false);
		u = it->second;
		if (o && !u->_oper)
			// Do not include non-op in 'o' request
			continue;
		if (u->_nick == mask || u->_rname == mask)
			// Show user if nick or real name is exact match (even invisible)
			showUser = true;
		else if (u == user || !u->_invisible)
			// Show user if one of the patterns matches (for themselves
			// or another non-invisible user)
			showUser = (::maskMatchesStr(mask, USR_HOST)
				|| ::maskMatchesStr(mask, IRC_HOST)
				|| ::maskMatchesStr(mask, u->_nick)
				|| ::maskMatchesStr(mask, u->_rname));
		if (showUser)
		{
			string	flag = (u->IsAway()) ? "G" : "H";
			if (u->_oper)
				flag += "*";
			resp += getResponseFromCode(
				user, RPL_WHOREPLY,
				(string[]){ "*", u->_uname, u->_nick, flag, u->_rname }
			);
		}
	}
	if (!resp.empty())
		responseQueue.push_back(std::make_pair(user->_fd, resp));
}
