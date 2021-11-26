/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_query_parser.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 18:12:31 by bahaas            #+#    #+#             */
/*   Updated: 2021/11/26 20:31:34 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/irc.hpp"

int main(int ac, char **av)
{
    Server  server;
    Client *my_test_client = new Client();
    t_cmd   client_command;

    // save prefix in cmd
    std::string           str = std::string(av[1]);
    std::string::iterator it  = str.begin();

    std::cout << str << std::endl;
    int i = 0;
    if (*it == ':')
    {
        for (it = str.begin(); (it != str.end()); ++it)
        {
            if (*it == ' ')
            {
                client_command.prefix = str.substr(0, i);
                i++;
                break;
            }
            i++;
        }
    }
    std::cout << "prefix=" << client_command.prefix << std::endl;

    // save command
    int j = 0;
    for (std::string::iterator it2 = str.begin() + i; it2 != str.end(); ++it2)
    {
        if (*it2 == ' ')
        {
            client_command.cmd = str.substr(i, j);
            j++;
            break;
        }
        j++;
    }
    std::cout << "cmd=" << client_command.cmd << std::endl;

    // save command params
    //  std::string::iterator it3 = str.begin() + i + j;
    std::cout << *it3 << std::endl;

    for (it3; it3 != str.end(); ++it3)
    {
    }

    /*
    std::vector<std::string>::iterator itr = client_command.params.begin();
    for (itr; itr != client_command.params.end(); itr++)
    {
        std::cout << *itr << std::endl;
    }
    * /
}