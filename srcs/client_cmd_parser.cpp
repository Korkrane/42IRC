/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_cmd_parser.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 13:52:06 by bahaas            #+#    #+#             */
/*   Updated: 2021/11/26 18:07:34 by bahaas           ###   ########.fr       */
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
        unknownCmd(cmd, client, server);
    }
}