#include "../IRC.hpp"

void	IRC::execKILL(Command const &cmd, std::vector<t_clientCmd> &responseQueue)
{
	User	*user(cmd._user);
	string	resp;

	if (!user->_oper)
		resp = getResponseFromCode(user, ERR_NOPRIVILEGES, NULL);
	else if (cmd._params.empty())
		resp = getResponseFromCode(user, ERR_NEEDMOREPARAMS, (string[]){ cmd._type });
	else if (cmd._params[0] == IRC_HOST)
		resp = getResponseFromCode(user, ERR_CANTKILLSERVER, NULL);
	if (!resp.empty())
	{
		responseQueue.push_back(std::make_pair(user->_fd, resp));
		return;
	}

	string const	&nick(cmd._params[0]);
	string const	&comment = (cmd._params.size() == 1)
							 ? ("Killed by " + user->_nick)
							 : cmd._params[1];
	User	*victim(getUserByNick(nick));
	if (victim)
	{
		_killing = victim->_fd;
		// Kill the victim like he's quitting himself
		Command	cmdQUIT(victim, "QUIT :" + comment);
		execQUIT(cmdQUIT, responseQueue);
		return;
	}
	resp = getResponseFromCode(user, ERR_NOSUCHNICK, (string[]){ nick });
	responseQueue.push_back(std::make_pair(user->_fd, resp));
}
