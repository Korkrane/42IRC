#include "../../includes/irc.hpp"

// TODO find a good process to send consecutive multiple replies
void adminCmd(t_cmd *cmd, Client *client, Server *server) // 256 to 259 & 402 reply
{
    std::vector<std::string> reply_params;
    std::string              reply;

    if (cmd->params[0].empty() || (cmd->params[0] == server->get_name())) // si pas de server precise donné l'actuel
    {
        /*
        reply = build_reply(256, client, reply_params);
        reply = build_reply(257, client, reply_params);
        reply = build_reply(258, client, reply_params);
        reply = build_reply(259, client, reply_params);
        */
    }
    else if (!cmd->params[0].empty() && cmd->params[0] != server->get_name())
    {
        reply_params.push_back(cmd->params[0]);
        reply = build_reply(402, client, reply_params);
        send_reply(reply);
    }
}