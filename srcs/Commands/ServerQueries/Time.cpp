#include <IRC.hpp>

/**
 * @brief query the local time from the specified server
 */
void Commands::time_cmd(User *user, IRC *server)
{
#if DEBUG
    std::cout << RED << "ENTER MOTD CMD" << NC << std::endl;
#endif
    std::vector<std::string> params = user->get_params();
    std::vector<std::string> reply_params;

    std::cout << server->get_name() << std::endl;
    if (!params.empty() && params[0] != server->get_name())
    {
        reply_params.push_back(params[0]);
        server->send_rpl("402", user, reply_params, "");
    }
    else
    {
        time_t now = std::time(0);
        std::string date = ctime(&now);

        reply_params.push_back(user->get_hostname());
        reply_params.push_back(date);
        server->send_rpl("391", user, reply_params, "");
    }
#if DEBUG
    std::cout << RED << "EXIT MOTD CMD" << NC << std::endl;
#endif
}