#include "../IRC.hpp"

void	IRC::execVERSION(Command const &cmd, std::vector<t_clientCmd> &responseQueue)
{
	User	*user(cmd._user);
	string	resp(getResponseFromCode(user, RPL_TIME, NULL));
	responseQueue.push_back(std::make_pair(user->_fd, resp));
}
