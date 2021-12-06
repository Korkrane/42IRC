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

#include "channel.hpp"
#include "Client.hpp"
#include "Colors.hpp"
#include "replies.hpp"
#include "Server.hpp"
#include "Commands.hpp"
#include "IRCServer.hpp"
#include "ParsingUtils.hpp"
#include "ClientUtils.hpp"
#include "User.hpp"
#include "ErrorHandling.hpp"

class User;

std::string build_reply(int code, User *server, std::vector<std::string> params);
void send_reply(std::string reply);