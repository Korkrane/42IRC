/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 13:36:48 by bahaas            #+#    #+#             */
/*   Updated: 2021/11/26 17:18:55 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/irc.hpp"

void test_1()
{
    std::cout << "--- TEST1 TIME CMD ---" << std::endl;

    Server server;
    User my_test_client;
    t_cmd  client_command;

    my_test_client.set_nickname("bahaas");
    my_test_client.set_username("bahaas");
    my_test_client.set_hostname("www.ft_irc.com");

    client_command.prefix = "";
    client_command.cmd    = "TIME";
    client_command.params.push_back("my_server");

    timeCmd(&client_command, &my_test_client, &server);
}

int main(int ac, char **av)
{
    test_1();
}