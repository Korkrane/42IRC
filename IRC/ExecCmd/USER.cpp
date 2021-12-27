#include "../IRC.hpp"

void	IRC::execUSER(Command const &cmd, std::vector<t_clientCmd> &responseQueue)
{
	User	*user(cmd._user);
	string	resp;

	if (!user->IsUsernameDefault())
	{
		resp = getResponseFromCode(user, ERR_ALREADYREGISTRED, NULL);
		responseQueue.push_back(std::make_pair(user->_fd, resp));
	}
	else if (cmd._params.size() < 4)
	{
		resp = getResponseFromCode(user, ERR_NEEDMOREPARAMS, (string[]){ cmd._type });
		responseQueue.push_back(std::make_pair(user->_fd, resp));
	}
	else
	{
		user->SetUsername(cmd._params[0]);
		user->_rname = cmd._params[3];
	}
}
