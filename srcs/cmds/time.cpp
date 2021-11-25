/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 14:03:47 by bahaas            #+#    #+#             */
/*   Updated: 2021/11/25 17:56:16 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

void send_reply(std::string reply)
{
    std::cout << reply << std::endl;
}

/**
 * @brief query the local time from the specified server
 *
 * @param cmd
 */
void timeCmd(t_cmd *cmd, Client *client)
{
    std::vector<std::string> reply_params;
    std::string              reply;

    time_t      now  = time(0);
    std::string date = ctime(&now);

    reply_params.push_back(cmd->params[0]);
    reply_params.push_back(date);
    reply = build_reply(391, client, reply_params);
    send_reply(reply);
}

int main(int ac, char **av)
{
    Server  server;
    Client *my_test_client = new Client();
    my_test_client->set_nickname("bahaas");
    my_test_client->set_username("bahaas");
    my_test_client->set_hostname("www.ft_irc.com");

    t_cmd client_command;

    client_command.prefix = "";
    client_command.cmd    = "TIME";
    client_command.params.push_back("my_server");
    timeCmd(&client_command, my_test_client);
    std::map<std::string, void (*)(t_cmd *, Client *)>::iterator it;

    it              = server._cmdsFunction.begin();
    std::string key = it->first;
    std::cout << key << " " << std::endl;
}