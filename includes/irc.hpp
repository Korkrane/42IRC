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
#include "replies.hpp"
#include "Server.hpp"
#include "Commands.hpp"
#include "IRCServer.hpp"
#include "ParsingUtils.hpp"
#include "User.hpp"
#include "ErrorHandling.hpp"

#define NICK_VALID_CHARS "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-^_[]{}\\|"
#define CHANNEL_VALID_CHARS "#&!+"
#define USER_VALID_MODES "aiwroOs"
#define CHANNEL_VALID_MODES "OovaimnpsrtklbeI"
#define CHANNEL_FORBIDDEN_CHARS " ,:"

class User;

std::string build_reply(int code, User *server, std::vector<std::string> params);
void send_reply(std::string reply);