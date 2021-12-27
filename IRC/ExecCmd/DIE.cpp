#include "../IRC.hpp"

void	IRC::execDIE(Command const &cmd, std::vector<t_clientCmd> &responseQueue)
{
	User	*user(cmd._user);

	if (!user->_oper)
	{
		string	resp(getResponseFromCode(user, ERR_NOPRIVILEGES, NULL));
		responseQueue.push_back(std::make_pair(user->_fd, resp));
		return;
	}
	std::cout << BLUE << user->_nick << " killed the server\n" << NC;
	exit(0);
}
