#include "../IRC.hpp"

void	IRC::execPASS(Command const &cmd, std::vector<t_clientCmd> &responseQueue)
{
	User	*user(cmd._user);

	if (user->_passwordOK)
		return;
	if (cmd._params.empty())
	{
		string	resp(getResponseFromCode(user, ERR_NEEDMOREPARAMS, (string[]){ cmd._type }));
		responseQueue.push_back(std::make_pair(user->_fd, resp));
	}
	else if (cmd._params[0] == _svPassword)
		user->_passwordOK = true;
}
