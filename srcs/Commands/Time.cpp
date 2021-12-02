#include "../../includes/irc.hpp"
#include <ctime>

/**
 * @brief query the local time from the specified server
 *
 * @param client
 * @param server
 */
void Commands::time_cmd(Client *client, Server *server)
{
    std::vector<std::string> reply_params;
    std::string              reply;

    time_t      now  = std::time(0);
    std::string date = ctime(&now);

    reply_params.push_back(client->get_params()[0]);
    reply_params.push_back(date);
    reply = build_reply(391, client, reply_params);
    send_reply(reply);
}