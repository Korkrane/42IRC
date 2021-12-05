/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   users.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 17:47:00 by bahaas            #+#    #+#             */
/*   Updated: 2021/11/29 17:48:23 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/irc.hpp"

void test_1()
{
    std::cout << "--- TEST1 USERS CMD ---" << std::endl;

    Server server;
    Client my_test_client;
    t_cmd client_command;

    my_test_client.set_nickname("bahaas");
    my_test_client.set_username("bahaas");
    my_test_client.set_hostname("www.ft_irc.com");

    server.set_version("v0.1");
    server.set_name("www.ft_irc.com");

    client_command.prefix = "";
    client_command.cmd = "USERS";
    client_command.params.push_back("");

    std::cout << "client cmd: /USERS with no params" << std::endl;
    usersCmd(&client_command, &my_test_client, &server);
}

void test_2()
{
    std::cout << "--- TEST2 USERS CMD ---" << std::endl;

    Server server;
    Client my_test_client;
    t_cmd client_command;

    my_test_client.set_nickname("bahaas");
    my_test_client.set_username("bahaas");
    my_test_client.set_hostname("www.ft_irc.com");

    server.set_version("v0.1");
    server.set_name("www.ft_irc.com");

    client_command.prefix = "";
    client_command.cmd = "USERS";
    client_command.params.push_back(server.get_name());

    std::cout << "client cmd: /USERS with known server params" << std::endl;
    usersCmd(&client_command, &my_test_client, &server);
}

int main(int ac, char **av)
{
    test_1();
    test_2();
}