#ifndef IRCSERVER_HPP
#define IRCSERVER_HPP

#include <errno.h>
#include <signal.h>
#include <unistd.h>

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>

#include <arpa/inet.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/select.h>

#include "Client.hpp"

#define MAX_LISTEN	42

// prototype to the class containing the data and structure of the IRC server
class	IRC
{

};

class	IRCServer
{
private:
	int const			_port;
	std::string	const	_password;
	int					_fd;
	IRC					*_irc;

	std::vector<Client>	_clients;
	int					_maxFD;

public:
	IRCServer(int port, std::string const &password);
	~IRCServer();

	// Set up server properly for listening and accepting clients
	void	SetUp(IRC *irc);
	// Kick off server's infinite loop (until Ctrl+C or Ctrl+\\)
	void	Run();
};

IRCServer::IRCServer(int port, std::string const &password) :
	_port(port),
	_password(password),
	_fd(-1),
	_irc(nullptr)
{}

IRCServer::~IRCServer()
{
	_clients.clear();
	close(_fd);
}

void	IRCServer::SetUp(IRC *irc)
{
	_irc = irc;

	// Create server socket
	struct protoent		*prot = getprotobyname("tcp");
	if ((_fd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, prot->p_proto)) == -1)
	{
		std::cerr << "socket: " << strerror(errno) << std::endl;
		exit(1);
	}

	// Bind socket to port
	struct sockaddr_in	sin;
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = htons(_port);
	if (bind(_fd, (struct sockaddr*)&sin, sizeof(sin)) == -1)
	{
		std::cerr << "bind: " << strerror(errno) << std::endl;
		exit(1);
	}

	// Listen for connections
	if (listen(_fd, MAX_LISTEN) == -1)
	{
		std::cerr << "listen: " << strerror(errno) << std::endl;
		exit(1);
	}
}

void	IRCServer::Run()
{
	while (true)
	{
		// TODO
	}
}

#endif
