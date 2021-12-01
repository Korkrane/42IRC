#include "../../includes/irc.hpp"

/**
 * @brief query the local time from the specified server
 *
 * @param cmd
 * @param client
 */
void timeCmd(t_cmd *cmd, Client *client, Server *server)
{
    std::vector<std::string> reply_params;
    std::string              reply;

    time_t      now  = time(0);
    std::string date = ctime(&now);

    reply_params.push_back(cmd->params[0]);
    reply_params.push_back(date);
    reply = build_reply(391, client, reply_params);
    send_reply(reply);
}