#include "../IRC.hpp"

void	IRC::chanPRIVMSG
	(User *user, string const &name, string const &msg, std::vector<t_clientCmd> &responseQueue) const
{
	Channel	*chan(getChannelByName(name));

	if (!chan || !chan->HasJoined(user))
	{
		string	resp(getResponseFromCode(user, ERR_CANNOTSENDTOCHAN, (string[]){ name }));
		responseQueue.push_back(std::make_pair(user->_fd, resp));
	}
	else
		appendUserNotif(
			user,
			(string[]){ "PRIVMSG", name, ":" + msg, "" },
			chan->_users, responseQueue,
			true
		);
}

void	IRC::userPRIVMSG
	(User *user, string const &name, string const &msg, std::vector<t_clientCmd> &responseQueue) const
{
	User	*target(getUserByNick(name));
	int		fd;
	string	resp;

	if (!target)
	{
		resp = getResponseFromCode(user, ERR_NOSUCHNICK, (string[]){ name });
		fd = user->_fd;
	}
	else
	{
		if (target->IsAway())
		{
			resp = getResponseFromCode(user, RPL_AWAY, (string[]){ name, target->_awayMsg });
			responseQueue.push_back(std::make_pair(user->_fd, resp));
		}
		resp = user->_prefix + " PRIVMSG " + name + " :" + msg + CMD_DELIM;
		fd = target->_fd;
	}
	responseQueue.push_back(std::make_pair(fd, resp));
}

void	IRC::execPRIVMSG(Command const &cmd, std::vector<t_clientCmd> &responseQueue)
{
	User	*user(cmd._user);
	string	resp;

	if (cmd._params.empty())
		resp = getResponseFromCode(user, ERR_NORECIPIENT, (string[]){ cmd._type });
	else if (cmd._params.size() == 1)
		resp = getResponseFromCode(user, ERR_NOTEXTTOSEND, NULL);
	if (!resp.empty())
	{
		responseQueue.push_back(std::make_pair(user->_fd, resp));
		return;
	}

	string const	&name(cmd._params[0]);
	string const	&msg(cmd._params[1]);
	if (Channel::IsPrefix(name[0]))
		chanPRIVMSG(user, name, msg, responseQueue);
	else
		userPRIVMSG(user, name, msg, responseQueue);
}
