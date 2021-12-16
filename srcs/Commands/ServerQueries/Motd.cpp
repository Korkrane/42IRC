#include <IRC.hpp>
/**
 * @brief send the content of motd file located in cmd_files. send first RPL_MOTDSTARD RPL_MOTD
 * then end with RPL_ENDOFMOTD. If no file located then ERR_NOMOTD
 */
void Commands::motd_cmd(User *user, IRC *server)
{
    #if DEBUG
        std::cout << RED << "ENTER MOTD CMD" << NC << std::endl;
    #endif
    std::vector<std::string> params;

    std::ifstream infile("./cmd_files/motd");
    if (infile.is_open())
    {
        params.push_back(user->get_hostname());
        server->send_rpl("375", user, params, "");
        params.clear();

        std::string buff;
        for (std::string line; getline(infile, line);)
        {
            line = "- " + line + "\r\n";
            //buff.append(line);
            params.push_back(buff);
            params.push_back(line);
            server->send_rpl("372", user, params, "");
            params.clear();
        }

        server->send_rpl("376", user, params, "");
        params.clear();
    }
    else
        server->send_rpl("422", user, params, "");
    #if DEBUG
        std::cout << RED << "EXIT MOTD CMD" << NC << std::endl;
    #endif
}