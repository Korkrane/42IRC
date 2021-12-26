#include "../IRC.hpp"

void	IRC::execPING(Command const &cmd, std::vector<t_clientCmd> &responseQueue)
{
	// 	>>>> PING LAG3775662729\r\n
	//    << :irc.42.fr PONG irc.42.fr :LAG3775662729\r\n
	stringstream	ss;
	string	param	= cmd._params.empty()
						? ""
						: cmd._params[0];
	ss << _prefix << " PONG " << IRC_HOST << " :" << param << CMD_DELIM;
	responseQueue.push_back(std::make_pair(cmd._user->_fd, ss.str()));
}
