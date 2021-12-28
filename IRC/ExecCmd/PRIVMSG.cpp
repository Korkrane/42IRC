#include "../IRC.hpp"

void	IRC::sendPRIVMSGtoChan
	(User *user, string const &name, string const &msg, std::vector<t_clientCmd> &responseQueue) const
{
	string	resp;
	Channel	*chan(getChannelByName(name));
	if (!chan || !chan->IsJoined(user))
		resp = getResponseFromCode(user, ERR_CANNOTSENDTOCHAN, (string[]){ name });
}

void	IRC::sendPRIVMSGtoUser
	(User *user, string const &name, string const &msg, std::vector<t_clientCmd> &responseQueue) const
{

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
		sendPRIVMSGtoChan(user, name, msg, responseQueue);
	else
		sendPRIVMSGtoUser(user, name, msg, responseQueue);
}
