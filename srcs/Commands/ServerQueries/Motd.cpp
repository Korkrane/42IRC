#include "IRC.hpp"

void Commands::motd_cmd(User *user, IRC *server)
{
#if DEBUG == 1
    std::cout << "DEBUG: enter motd_cmd" << std::endl;
#endif
    std::vector<std::string> params = user->get_params();
    std::vector<std::string> reply_params;

    if (!params.empty() && params[0] != server->get_name())
    {
        reply_params.push_back(params[0]);
        server->send_rpl("402", user, reply_params, "");
    }
    else
    {
        std::ifstream infile("./cmd_files/motd");
        if (infile.is_open())
        {
            reply_params.push_back(user->get_hostname());
            server->send_rpl("375", user, reply_params, "");
            reply_params.clear();
            for (std::string line; getline(infile, line);)
            {
                line = "- " + line + "\r\n";
                reply_params.push_back(line);
                server->send_rpl("372", user, reply_params, "");
                reply_params.clear();
            }
            server->send_rpl("376", user, reply_params, "");
        }
        else
            server->send_rpl("422", user, params, "");
    }
#if DEBUG == 1
    std::cout << RED << "EXIT MOTD CMD" << NC << std::endl;
#endif
}