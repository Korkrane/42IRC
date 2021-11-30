/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahautlatinis <mahautlatinis@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:24:49 by bahaas            #+#    #+#             */
/*   Updated: 2021/11/30 18:49:14 by mahautlatin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_HPP
#define IRC_HPP

#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>

#include <list>
#include <map>
#include <vector>

#include <arpa/inet.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <poll.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/select.h>

#include "channel.hpp"
#include "client.hpp"
#include "colors.hpp"
#include "exceptions.hpp"
#include "replies.hpp"
#include "server.hpp"

/**
 * @brief content of the command send by a client
 *
 */
struct t_cmd
{
        std::string prefix;
        std::string cmd;
        std::vector<std::string> params;
};

void buildServer(Server *server, char **av);

std::string build_reply(int code, Client *client, std::vector<std::string> params);

void send_reply(std::string reply);

void client_cmd_parser(t_cmd *client_command, Client *my_test_client, Server *server);

void printClientCommand(t_cmd *cmd);
void split_string_to_vector(std::vector<std::string> *vec, std::string *str, char c);
#endif // !IRC_HPP