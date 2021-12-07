#pragma once

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
#include <algorithm>

#include "channel.hpp"
#include "Client.hpp"
#include "Colors.hpp"
#include "exceptions.hpp"
#include "replies.hpp"
#include "Server.hpp"
#include "Commands.hpp"
#include "IRCTest.hpp"
#include "ParsingUtils.hpp"
#include "User.hpp"
#include "ErrorHandling.hpp"

#define NICK_VALID_CHARS "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-^_[]{}\\|"
#define CHANNEL_VALID_CHARS "#&!+"
#define USER_VALID_MODES "aiwroOs"
#define CHANNEL_VALID_MODES "OovaimnpsrtklbeI"

class Server;
class Client;
class Channel;

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