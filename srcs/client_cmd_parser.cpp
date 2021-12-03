#include "../includes/irc.hpp"
void client_cmd_parser(t_cmd *cmd, Client *client, Server *server)
{
    /*
    std::map<std::string, void (*)(t_cmd *, Client *, Server *)>::iterator it;
    int                                                                    known_command = 0;

    for (it = server->get_cmds().begin(); it != server->get_cmds().end(); ++it)
    {
        std::string key = it->first;
        if (key == cmd->cmd)
        {
#if DEBUG
            std::cout << "DEBUG: " << GREEN << key << NC << " execute the command -->" << std::endl;
#endif
            (*it->second)(cmd, client, server);
            known_command += 1;
        }
    }
    if (known_command == 0)
    {
#if DEBUG
        std::cout << "DEBUG: " << RED << cmd->cmd << NC << " return the error command -->" << std::endl;
#endif
        //TODO uncomment when class well implemented
        //unknownCmd(cmd, client, server);
    }
    */
}