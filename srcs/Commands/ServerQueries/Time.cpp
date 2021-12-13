#include <IRC.hpp>

/**
 * @brief query the local time from the specified server
 */
void Commands::time_cmd(User *user, IRC *server)
{
    std::vector<std::string> params;

    time_t      now  = std::time(0);
    std::string date = ctime(&now);

    params.push_back(user->get_hostname());
    params.push_back(date);
    server->send_rpl("391", user, params, "");
}