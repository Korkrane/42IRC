#include "../IRC.hpp"

void	IRC::execLIST(Command const &cmd, std::vector<t_clientCmd> &responseQueue)
{
	User    *user(cmd._user);
    std::vector<std::string> params = cmd._params;
    string    resp;

    resp = getResponseFromCode(user, RPL_LISTSTART, NULL);
    responseQueue.push_back(std::make_pair(user->_fd, resp));
     if (params.size() == 0 || (params.size() == 1 && params[0] == ""))
    {
        for (std::map<string, Channel *>::iterator it = _channels.begin(); it != _channels.end(); it++)
        {
            string name = it->second->_name;
            //string nb = static_cast<string>(it->second->_users.size());
            string topic = it->second->_topic;
            resp = getResponseFromCode(user, RPL_LIST, (string[]){name, size, topic});
        }
    }
    resp = getResponseFromCode(user, RPL_LISTEND, NULL);
    responseQueue.push_back(std::make_pair(user->_fd, resp));
}