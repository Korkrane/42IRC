#ifndef IRCSERVER_HPP
#define IRCSERVER_HPP

#include <errno.h>
#include <signal.h>
#include <unistd.h>

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#include <map>

#include <arpa/inet.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/select.h>

#include "Client.hpp"

#define MAX_LISTEN	42		// Max concurrent connections in queue
#define SERVER_ERR(err)	do { std::cerr << err << ": " << strerror(errno) << std::endl; exit(1); } while (0)	// Print error msg, quit

typedef std::pair<int, std::string>	t_clientCmd;

// prototype to the class containing the data and structure of the IRC server
class	IRC
{
private:
	std::string const	_svPassword;

public:
	IRC(std::string const &password) : _svPassword(password) {}

	// Method to be called by the server. Process a command from a client, then queue
	// response messages into responseQueue. If there are clients to be removed, their
	// fd should also be added to disconnectList
	void ProcessCommand(t_clientCmd command, std::vector<t_clientCmd> &responseQueue, std::vector<int> &disconnectList) {}

};

class	IRCServer
{
private:
	int const			_port;
	std::string	const	_password;
	int					_fd;
	IRC					*_irc;

	std::map<int, Client *>	_clients;
	int						_maxFD;
	fd_set					_fdReader;

	// Accept new client connection
	void	acceptClient();

	// Make all open socket ready to be read then select them. Return the number of FDs
	// ready to be read
	int		setFDForReading();

	// Read from fd to get client commands then forward it to the IRC program
	void	recvProcessCommand(int totalFD, std::vector<t_clientCmd> &responseQueue, std::vector<int> &disconnectList);

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
	std::map<int, Client *>::iterator	fd_cl;
	for (fd_cl = _clients.begin(); fd_cl != _clients.end(); ++fd_cl)
		delete fd_cl->second;
	close(_fd);
}

void	IRCServer::SetUp(IRC *irc)
{
	_irc = irc;

	// Create server socket
	struct protoent		*prot = getprotobyname("tcp");
	if ((_fd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, prot->p_proto)) == -1)
		SERVER_ERR("socket");

	// Bind socket to port
	struct sockaddr_in	sin;
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = htons(_port);
	if (bind(_fd, (sockaddr *)&sin, sizeof(sin)) == -1)
		SERVER_ERR("bind");

	// Listen for connections
	if (listen(_fd, MAX_LISTEN) == -1)
		SERVER_ERR("listen");
}

void	IRCServer::acceptClient()
{
	struct sockaddr_in	sin;
	socklen_t			sin_len;

	int	clientFD = accept(_fd, (sockaddr *)&sin, &sin_len);
	if (clientFD == -1)
	{
		std::cerr << "Failed to accept a new connection\n";
		return;
	}
	std::cout	<< "New client on socket #" << clientFD
				<< " from address " << inet_ntoa(sin.sin_addr)
				<< ":" << ntohs(sin.sin_port) << '\n';
	
	_clients.emplace(clientFD, new Client(clientFD));
}

void	IRCServer::Run()
{
	std::vector<t_clientCmd>	responseQueue;
	std::vector<int>			disconnectList;

	while (true)
	{
		responseQueue.clear();
		disconnectList.clear();
	
		int	totalFD = setFDForReading();
		recvProcessCommand(totalFD, responseQueue, disconnectList);

		// Send server's response to clients
		for (std::vector<t_clientCmd>::const_iterator it = responseQueue.cbegin();
			it != responseQueue.cend(); ++it)
		{
			int	clientFD = it->first;
			if (_clients.find(clientFD) != _clients.end())
				_clients[clientFD]->sendResponse(it->second);
		}

		// Disconnect FDs in list
		for (std::vector<int>::const_iterator it = disconnectList.cbegin();
			it != disconnectList.cend(); ++it)
			if (_clients.find(*it) != _clients.end())
			{
				delete _clients[*it];
				_clients.erase(*it);
			}
	}
}

int	IRCServer::setFDForReading()
{
	_maxFD = _fd;
	FD_ZERO(&_fdReader);
	FD_SET(_fd, &_fdReader);

	std::map<int, Client *>::iterator	fd_cl;
	for (fd_cl = _clients.begin(); fd_cl != _clients.end(); ++fd_cl)
	{
		int	clientFD = fd_cl->first;
		FD_SET(clientFD, &_fdReader);
		if (clientFD > _maxFD)
			_maxFD = clientFD;
	}

	int	r = select(_maxFD + 1, &_fdReader, NULL, NULL, NULL);
	if (r == -1)
		SERVER_ERR("select");
	return r;
}

void	IRCServer::recvProcessCommand
	(int totalFD, std::vector<t_clientCmd> &responseQueue, std::vector<int> &disconnectList)
{
	// Checking each socket for reading, starting from FD 3 because there should be nothing
	// to read from 0 (stdin), 1 (stdout) and 2 (stderr)
	for (int s = 3; s <= _maxFD && totalFD; ++s)
		if (FD_ISSET(s, &_fdReader))
		{
			if (s == _fd)
				acceptClient();
			else
			{
				// Receive a full command, with delimiter, then send it to program to process,
				// then grab program's response(s)
				std::string	cmd(_clients[s]->receiveCommand());
				if (!cmd.empty())
					_irc->ProcessCommand(
						std::make_pair(s, cmd),
						responseQueue,
						disconnectList
					);
			}
			--totalFD;
		}
}

#endif
