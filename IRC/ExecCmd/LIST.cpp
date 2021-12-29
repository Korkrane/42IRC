#include "../IRC.hpp"

void	IRC::execLIST(Command const &cmd, std::vector<t_clientCmd> &responseQueue)
{
	User    *user(cmd._user);
    string    resp;

    resp = getResponseFromCode(user, RPL_LISTSTART, NULL);
    responseQueue.push_back(std::make_pair(user->_fd, resp));
    resp = getResponseFromCode(user, RPL_LISTEND, NULL);
    responseQueue.push_back(std::make_pair(user->_fd, resp));
}
