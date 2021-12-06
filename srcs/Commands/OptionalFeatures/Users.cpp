#include <irc.hpp>

/**
 * @brief disabled due to security implications, only send an error reply
 * https://datatracker.ietf.org/doc/html/rfc2812#section-4.6
 * @param cmd
 * @param client
 * @param server
 * TODO: a reprendre suite a la modif de client
 */
void usersCmd(User *client, Server *server) // 446 reply
{
    (void)client;
    (void)server;
    /*
    std::vector<std::string> reply_params;
    std::string reply;

    reply = build_reply(446, client, reply_params);
    send_reply(reply);
    */
}