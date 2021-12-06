#include <irc.hpp>

/**
 * @brief
 *
 * @param cmd
 * @param client
 * @param server
 * TODO: a reprendre suite a la modif de client
 */
void versionCmd(User *client, Server *server) // 351 & 402 reply
{
    (void)client;
    (void)server;
    std::vector<std::string> reply_params;
    std::string              reply;

    /*
    if (cmd->params[0].empty() || (cmd->params[0] == server->get_name())) // si pas de server precise donné l'actuel
    {
        // TODO check for degublevel & comments (hardcoded atm)
        //reply_params.push_back(server->get_version());
        reply_params.push_back("debuglevel00");
        //reply_params.push_back(server->get_name());
        reply_params.push_back("random comments as test");
        reply = build_reply(351, client, reply_params);
    }
    else if (!cmd->params[0].empty() && cmd->params[0] != server->get_name())
    {
        reply_params.push_back(cmd->params[0]);
        reply = build_reply(402, client, reply_params);
    }
    */
    send_reply(reply);
}