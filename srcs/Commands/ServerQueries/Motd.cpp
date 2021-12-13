//#include "../../includes/irc.hpp"
//TODO: a deplacer au bon endroit
#include <fstream>
#include <IRC.hpp>
/**
 * @brief send the content of motd file located in cmd_files. send first RPL_MOTDSTARD RPL_MOTD
 * then end with RPL_ENDOFMOTD. If no file located then ERR_NOMOTD
 * @param client
 * @param server
 */

void Commands::motd_cmd(User *user, IRC *server)
{
    (void)user;
    (void)server;
    #if DEBUG
        std::cout << "DEBUG: enter motd_cmd" << std::endl;
    #endif
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
        reply_params.push_back(user->get_hostname());
        reply = build_reply(375, user, reply_params);
        //TODO: a revoir ? est-ce le response queue ne peut pas fait partie du build reply ?
        server->_response_queue.push_back(std::make_pair(user->get_socket(), reply));
        reply_params.clear();

        reply_params.push_back(buff);
        reply = build_reply(372, user, reply_params);
        server->_response_queue.push_back(std::make_pair(user->get_socket(), reply));
        reply_params.clear();


        reply = build_reply(376, user, reply_params);
        server->_response_queue.push_back(std::make_pair(user->get_socket(), reply));
        reply_params.clear();
    }
    else
    {
        reply = build_reply(422, user, reply_params);
        server->_response_queue.push_back(std::make_pair(user->get_socket(), reply));
        reply_params.clear();
    }
}