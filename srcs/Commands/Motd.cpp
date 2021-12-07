#include "../../includes/irc.hpp"
#include <fstream>

/**
 * @brief send the content of motd file located in cmd_files. send first RPL_MOTDSTARD RPL_MOTD
 * then end with RPL_ENDOFMOTD. If no file located then ERR_NOMOTD
 * @param client
 * @param server
 */
void Commands::motd_cmd(User *user, IRCServ *server)
{
    std::vector<std::string> reply_params;
    std::string reply;

    std::ifstream infile("./cmd_files/motd");
    if (infile.is_open())
    {
        std::string buff;
        for (std::string line; getline(infile, line);)
        {
            line = "- " + line + "\r\n";
            buff.append(line);
        }
        reply_params.push_back(server->get_name());
        reply = build_reply(375, user, reply_params);
        send_reply(reply);
        reply_params.clear();
        reply_params.push_back(buff);
        reply = build_reply(372, user, reply_params);
        send_reply(reply);
        reply_params.clear();
        reply = build_reply(376, user, reply_params);
        send_reply(reply);
    }
    else
    {
        reply = build_reply(422, client, reply_params);
        send_reply(reply);
    }
}