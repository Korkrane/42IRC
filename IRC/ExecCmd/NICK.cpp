#include "../IRC.hpp"

void	IRC::execNICK(Command const &cmd, std::vector<t_clientCmd> &responseQueue)
{
	User	*user(cmd._user);
	string	resp;
	bool	newUser(false);

	if (cmd._params.empty())
	{
		resp = getResponseFromCode(user, ERR_NONICKNAMEGIVEN, NULL);
		responseQueue.push_back(std::make_pair(user->_fd, resp));
		return;
	}

	string const	&nick(cmd._params[0]);
	if (!User::CheckNickValidChars(nick))
		resp = getResponseFromCode(user, ERR_ERRONEUSNICKNAME, (string[]){ nick });
	else if (nick == user->_nick)
		return;
	else if (getUserByNick(nick))
		resp = getResponseFromCode(user, ERR_NICKNAMEINUSE, (string[]){ nick });
	else
	{
		newUser = !(user->_registered);
		// Inform everyone in common channels that user has just changed nickname
		if (!newUser)
			resp = appendUserNotif(
				user,
				(string[]){ "NICK", ":" + nick, "" },
				getCommonUsers(user),
				responseQueue
			);
		user->SetNick(nick);
	}
	if (!newUser)
		responseQueue.push_back(std::make_pair(user->_fd, resp));
}
