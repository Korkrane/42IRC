/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   admin.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 15:26:20 by bahaas            #+#    #+#             */
/*   Updated: 2021/11/26 16:53:42 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/irc.hpp"

void test_1()
{
    std::cout << "--- TEST1 ADMIN CMD ---" << std::endl;

    Server server;
    User my_test_client;
    t_cmd  client_command;

    my_test_client.set_nickname("bahaas");
    my_test_client.set_username("bahaas");
    my_test_client.set_hostname("www.ft_irc.com");

    server.set_version("v0.1");
    server.set_name("www.ft_irc.com");

    client_command.prefix = "";
    client_command.cmd    = "VERSION";
    client_command.params.push_back("");

    std::cout << "client cmd: /ADMIN with no params" << std::endl;
    adminCmd(&client_command, &my_test_client, &server);
}

void test_2()
{
    std::cout << "--- TEST2 VERSION CMD ---" << std::endl;

    Server server;
    User my_test_client;
    t_cmd  client_command;

    my_test_client.set_nickname("bahaas");
    my_test_client.set_username("bahaas");
    my_test_client.set_hostname("www.ft_irc.com");

    server.set_version("v0.1");
    server.set_name("www.ft_irc.com");

    client_command.prefix = "";
    client_command.cmd    = "ADMIN";
    client_command.params.push_back(server.get_name());

    std::cout << "client cmd: /ADMIN with good server params" << std::endl;
    adminCmd(&client_command, &my_test_client, &server);
}

void test_3()
{
    std::cout << "--- TEST3 ADMIN CMD ---" << std::endl;

    Server server;
    User my_test_client;
    t_cmd  client_command;

    my_test_client.set_nickname("bahaas");
    my_test_client.set_username("bahaas");
    my_test_client.set_hostname("www.ft_irc.com");

    server.set_version("v0.1");
    server.set_name("www.ft_irc.com");

    client_command.prefix = "";
    client_command.cmd    = "ADMIN";
    client_command.params.push_back("unkown.com");

    std::cout << "client cmd: /ADMIN with unkown server params" << std::endl;
    adminCmd(&client_command, &my_test_client, &server);
}

int main(int ac, char **av)
{
    test_1();
    test_2();
    test_3();
}