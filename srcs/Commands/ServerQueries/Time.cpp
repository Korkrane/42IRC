#include <IRC.hpp>
#include <ctime>

/**
 * @brief query the local time from the specified server
 *
 * @param client
 * @param server
 * TODO: a tester
 */
void Commands::time_cmd(User *user, IRC *server)
{
    (void)server;

    std::vector<std::string> reply_params;
    std::string              reply;

    time_t      now  = std::time(0);
    std::string date = ctime(&now);

    reply_params.push_back(user->get_hostname());
    reply_params.push_back(date);
    reply = build_reply(391, user, reply_params);
    server->_response_queue.push_back(std::make_pair(user->get_socket(), reply));
    reply_params.clear();
}