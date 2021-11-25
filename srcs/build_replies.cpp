/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_replies.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 13:02:49 by bahaas            #+#    #+#             */
/*   Updated: 2021/11/25 16:25:52 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/irc.hpp"

/**
 * @brief format the code into a valid string for the server reply (ex: int 1 --> str 001)
 *
 * @param code
 * @return std::string
 */
std::string format_code_str(int code)
{
    if (code < 10)
        return "00" + std::to_string(code);
    else if (code < 100)
        return "0" + std::to_string(code);
    return std::to_string(code);
}

/**
 * @brief build the reply string that the server has to send to the client when
 * a command (valid/unvalid) is received by th server
 * @param code
 * @return std::string
 */
std::string build_reply(int code, Client *client, std::vector<std::string> params)
{
    std::string code_str;
    std::string prefix;
    std::string date = "Mon Nov 22 2021";

    code_str         = format_code_str(code);
    if (client->get_nickname().empty())
        prefix = ":" + client->get_hostname() + " " + code_str + " * ";
    else
        prefix = ":" + client->get_hostname() + " " + code_str + " " + client->get_nickname() + " ";
    switch (code)
    {
        case 1:
            return prefix + RPL_WELCOME(client->get_nickname(), client->get_username(), client->get_hostname());
        case 2: // TODO servername not client->hostname for 2 & 4
            return prefix + RPL_YOURHOST(client->get_hostname(), "1.0");
        case 3: // TODO remove hardcoded date
            return prefix + RPL_CREATED(date);
        case 4: // TODO remove hardcoded value
            return prefix + RPL_MYINFO(client->get_hostname(), "1.0", "|list of user mode avai|", "|list of user mode avai|");
        case 391:
            return prefix + RPL_TIME(params[0], params[1]);
        default:
            return std::string("");
    }
}

// TEST MAIN FOR REPLY FORMAT //
/*
int main(int ac, char **av)
{
    Client                  *my_test_client = new Client();
    std::vector<std::string> reply_params;

    my_test_client->set_nickname("bahaas");
    my_test_client->set_username("bahaas");
    my_test_client->set_hostname("www.ft_irc.com");

    std::cout << build_reply(1, my_test_client, reply_params) << std::endl;
    std::cout << build_reply(2, my_test_client, reply_params) << std::endl;
    std::cout << build_reply(3, my_test_client, reply_params) << std::endl;
    std::cout << build_reply(4, my_test_client, reply_params) << std::endl;

    delete my_test_client;
}
*/