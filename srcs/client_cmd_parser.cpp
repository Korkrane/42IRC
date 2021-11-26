/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_cmd_parser.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 13:52:06 by bahaas            #+#    #+#             */
/*   Updated: 2021/11/26 17:52:00 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/irc.hpp"

void client_cmd_parser(t_cmd *cmd, Client *client, Server *server)
{
    std::map<std::string, void (*)(t_cmd *, Client *, Server *)>::iterator it;
    int                                                                    known_command = 0;

    for (it = server->_cmdsFunction.begin(); it != server->_cmdsFunction.end(); ++it)
    {
        std::string key = it->first;
        if (key == cmd->cmd)
        {
            std::cout << GREEN << key << NC << std::endl;
            std::cout << "execute the command -->" << std::endl;
            (*it->second)(cmd, client, server);
            known_command += 1;
        }
    }
    if (known_command == 0)
    {
#if DEBUG
        std::cout << RED << cmd->cmd << " : Unkown command" << NC << std::endl;
        std::cout << "return the error command -->" << std::endl;
#endif
        unknownCmd(cmd, client, server);
    }
}

int main(int ac, char **av)
{
    Server server;
    Client my_test_client;
    t_cmd  client_command;

    my_test_client.set_nickname("bahaas");
    my_test_client.set_username("bahaas");
    my_test_client.set_hostname("www.ft_irc.com");

    server.set_version("v0.1");
    server.set_name("www.ft_irc.com");

    client_command.prefix = "";
    client_command.cmd    = "RANDOM COMMAND";
    client_command.params.push_back("");

    std::cout << "tested client cmd: " << client_command.cmd << std::endl;
    client_cmd_parser(&client_command, &my_test_client, &server);
}