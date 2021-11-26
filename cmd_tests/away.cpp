/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   away.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 13:20:57 by bahaas            #+#    #+#             */
/*   Updated: 2021/11/26 14:01:20 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/irc.hpp"

void test_1()
{
    std::cout << "--- TEST1 AWAY CMD ---" << std::endl;

    Server  server;
    Client *my_test_client = new Client();
    t_cmd   client_command;

    my_test_client->set_nickname("bahaas");
    my_test_client->set_username("bahaas");
    my_test_client->set_hostname("www.ft_irc.com");
    my_test_client->set_is_away(true);

    client_command.prefix = "";
    client_command.cmd    = "AWAY";
    client_command.params.push_back("");

    std::cout << "client cmd: /AWAY without params and being curently away" << std::endl;
    awayCmd(&client_command, my_test_client, &server);
    delete my_test_client;
}

void test_2()
{
    std::cout << "--- TEST2 AWAY CMD ---" << std::endl;
    Server  server;
    Client *my_test_client = new Client();
    t_cmd   client_command;

    my_test_client->set_nickname("bahaas");
    my_test_client->set_username("bahaas");
    my_test_client->set_hostname("www.ft_irc.com");
    my_test_client->set_is_away(true);

    client_command.prefix = "";
    client_command.cmd    = "AWAY";
    client_command.params.push_back("changed the message while being away");

    std::cout << "client cmd: AWAY with params and being curently away" << std::endl;
    awayCmd(&client_command, my_test_client, &server);
    delete my_test_client;
}

void test_3()
{
    std::cout << "--- TEST3 AWAY CMD ---" << std::endl;
    Server  server;
    Client *my_test_client = new Client();
    t_cmd   client_command;

    my_test_client->set_nickname("bahaas");
    my_test_client->set_username("bahaas");
    my_test_client->set_hostname("www.ft_irc.com");
    my_test_client->set_is_away(false);

    client_command.prefix = "";
    client_command.cmd    = "AWAY";
    client_command.params.push_back("I'm back in 5");

    std::cout << "client cmd: AWAY with params and not being curently away" << std::endl;
    awayCmd(&client_command, my_test_client, &server);
    delete my_test_client;
}

void test_4()
{
    std::cout << "--- TEST4 AWAY CMD ---" << std::endl;
    Server  server;
    Client *my_test_client = new Client();
    t_cmd   client_command;

    my_test_client->set_nickname("bahaas");
    my_test_client->set_username("bahaas");
    my_test_client->set_hostname("www.ft_irc.com");
    my_test_client->set_is_away(false);

    client_command.prefix = "";
    client_command.cmd    = "AWAY";
    client_command.params.push_back("");

    std::cout << "client cmd: AWAY with no params and not being curently away" << std::endl;
    awayCmd(&client_command, my_test_client, &server);
    delete my_test_client;
}

int main(int ac, char **av)
{
    test_1();
    test_2();
    test_3();
    test_4();
}