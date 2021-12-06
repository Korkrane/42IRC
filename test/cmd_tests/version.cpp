/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   version.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 14:03:45 by bahaas            #+#    #+#             */
/*   Updated: 2021/11/26 14:29:32 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/irc.hpp"

void test_1()
{
    std::cout << "--- TEST1 VERSION CMD ---" << std::endl;

    Server server;
    Client my_test_client;
    t_cmd  client_command;

    my_test_client.set_nickname("bahaas");
    my_test_client.set_username("bahaas");
    my_test_client.set_hostname("www.ft_irc.com");

    server.set_version("v0.1");
    server.set_name("www.ft_irc.com");

    client_command.prefix = "";
    client_command.cmd    = "VERSION";
    client_command.params.push_back("");

    std::cout << "client cmd: /VERSION with no params" << std::endl;
    versionCmd(&client_command, &my_test_client, &server);
}

void test_2()
{
    std::cout << "--- TEST2 VERSION CMD ---" << std::endl;

    Server server;
    Client my_test_client;
    t_cmd  client_command;

    my_test_client.set_nickname("bahaas");
    my_test_client.set_username("bahaas");
    my_test_client.set_hostname("www.ft_irc.com");

    server.set_version("v0.1");
    server.set_name("www.ft_irc.com");

    client_command.prefix = "";
    client_command.cmd    = "VERSION";
    client_command.params.push_back(server.get_name());

    std::cout << "client cmd: /VERSION with good server params" << std::endl;
    versionCmd(&client_command, &my_test_client, &server);
}

void test_3()
{
    std::cout << "--- TEST3 VERSION CMD ---" << std::endl;

    Server server;
    Client my_test_client;
    t_cmd  client_command;

    my_test_client.set_nickname("bahaas");
    my_test_client.set_username("bahaas");
    my_test_client.set_hostname("www.ft_irc.com");

    server.set_version("v0.1");
    server.set_name("www.ft_irc.com");

    client_command.prefix = "";
    client_command.cmd    = "VERSION";
    client_command.params.push_back("unkown.com");

    std::cout << "client cmd: /VERSION with unkown server params" << std::endl;
    versionCmd(&client_command, &my_test_client, &server);
}

int main(int ac, char **av)
{
    test_1();
    test_2();
    test_3();
}