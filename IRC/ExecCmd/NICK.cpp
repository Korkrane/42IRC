#include "../IRC.hpp"

#define NICK_VALID_CHARS	"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-^_[]{}\\|"

static bool	checkNickValidChars(string const &nick)
{
	static string const	validChars(NICK_VALID_CHARS);
	static std::set<char> const	validChatSet(validChars.begin(), validChars.end());

	std::set<char>		nickCharSet(nick.begin(), nick.end());
	std::vector<char>	diff(nickCharSet.size());

	std::vector<char>::iterator	it(
		std::set_difference(
			nickCharSet.begin(), nickCharSet.end(),
			validChatSet.begin(), validChatSet.end(),
			diff.begin()
		)
	);
	return std::distance(diff.begin(), it) == 0;
}

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
	if (!checkNickValidChars(nick))
		resp = getResponseFromCode(user, ERR_ERRONEUSNICKNAME, (string[]){ nick });
	else if (checkNickInUse(nick))
		resp = getResponseFromCode(user, ERR_NICKNAMEINUSE, (string[]){ nick });
	else
	{
		newUser = !user->_registered;
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
