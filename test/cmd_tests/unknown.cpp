/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unknown.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 17:56:19 by bahaas            #+#    #+#             */
/*   Updated: 2021/11/26 18:06:44 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/irc.hpp"

void test_1()
{
    std::cout << "--- TEST1 PARSE CMD ---" << std::endl;

    Server server;
    Client my_test_client;
    t_cmd  client_command;

    my_test_client.set_nickname("bahaas");
    my_test_client.set_username("bahaas");
    my_test_client.set_hostname("www.ft_irc.com");

    server.set_version("v0.1");
    server.set_name("www.ft_irc.com");

    client_command.prefix = "";
    client_command.cmd    = "AWAY";
    client_command.params.push_back("Back in 5 minutes");

    std::cout << "with known command" << std::endl;
    client_cmd_parser(&client_command, &my_test_client, &server);
}

void test_2()
{
    std::cout << "--- TEST2 PARSE CMD ---" << std::endl;

    Server server;
    Client my_test_client;
    t_cmd  client_command;

    my_test_client.set_nickname("bahaas");
    my_test_client.set_username("bahaas");
    my_test_client.set_hostname("www.ft_irc.com");

    server.set_version("v0.1");
    server.set_name("www.ft_irc.com");

    client_command.prefix = "";
    client_command.cmd    = "TIME";
    client_command.params.push_back("");

    std::cout << "with known command" << std::endl;
    client_cmd_parser(&client_command, &my_test_client, &server);
}

void test_3()
{
    std::cout << "--- TEST3 PARSE CMD ---" << std::endl;

    Server server;
    Client my_test_client;
    t_cmd  client_command;

    my_test_client.set_nickname("bahaas");
    my_test_client.set_username("bahaas");
    my_test_client.set_hostname("www.ft_irc.com");

    server.set_version("v0.1");
    server.set_name("www.ft_irc.com");

    client_command.prefix = "";
    client_command.cmd    = "RANDOM";
    client_command.params.push_back("");

    std::cout << "with known command" << std::endl;
    client_cmd_parser(&client_command, &my_test_client, &server);
}

int main(int ac, char **av)
{
    test_1();
    test_2();
    test_3();
}