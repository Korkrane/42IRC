#include <irc.hpp>

/**
 * @brief 
 * 
 * @param client 
 * @param server 
 * TODO: a reprendre suite a la modification de clientm
 */
void Commands::unknown_cmd(User *client, Server *server)
{
    (void)client;
    (void)server;
    /*
    std::vector<std::string> reply_params;
    std::string              reply;

    //A reprendre suite a la modif de client
    //reply_params.push_back(client->get_command_name());
    reply = build_reply(421, client, reply_params);
    send_reply(reply);
    */
}