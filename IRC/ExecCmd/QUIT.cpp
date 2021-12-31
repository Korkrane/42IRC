#include "../IRC.hpp"

void	IRC::execQUIT(Command const &cmd, std::vector<t_clientCmd> &responseQueue)
{
	User	*user(cmd._user);
	string	msg = cmd._params.empty()
					? "Client exited"
					: ("Quit: " + cmd._params[0]);
	// Inform everyone user is leaving
	appendUserNotif(
		user,
		(string[]){ "QUIT", ":" + msg, "" },
		getCommonUsers(user), responseQueue
	);
	string	resp(getErrorResponse(user, msg));
	responseQueue.push_back(std::make_pair(user->_fd, resp));
	ClientDisconnect(user->_fd);
}
