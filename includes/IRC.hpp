#pragma once

#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <fstream>
#include <iterator>
#include <sstream>
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
#include <vector>
#include "Channel.hpp"
#include "Client.hpp"
#include "Colors.hpp"
#include "Replies.hpp"
#include "Server.hpp"
#include "Commands.hpp"
#include "IRCServer.hpp"
#include "User.hpp"
#include "ft.hpp"

#define NICK_VALID_CHARS "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-^_[]{}\\|"
#define CHANNEL_VALID_CHARS "#&!+"
#define USER_VALID_MODES "aiwroOs"
#define CHANNEL_VALID_MODES "+=tko" //On ne gere que ces modes mais il en existe davantage
#define CHANNEL_FORBIDDEN_CHARS " ,:"
#define CHANNEL_MODES "to"

#define MAX_CHAR 4096
#define CHAN_MAXCAPACITY 10
#define USER_MAXCHAN 10
#define SERVER_MAXCHAN 10

#define OPER_PASS "admin"
#define OPER_NAME "admin"
class User;

void error_handler(std::string error_code, User *user, Channel *channel, std::vector<std::string> parameter);
std::vector<std::string> ft_split(std::string line, std::string charset);
void delete_channels(User *user);