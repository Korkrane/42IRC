#include "Server.hpp"

Server::Server(int port, std::string const &password) :
	_port(port),
	_password(password),
	_fd(-1),
	_irc(nullptr)
{}

Server::~Server()
{
	std::map<int, Client *>::iterator	fd_cl;
	for (fd_cl = _clients.begin(); fd_cl != _clients.end(); ++fd_cl)
		delete fd_cl->second;
	close(_fd);
}

void	Server::SetUp(IRC *irc)
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

void	Server::acceptClient()
{
	struct sockaddr_in	sin;
	socklen_t			sin_len;

	int	clientFD = accept(_fd, (sockaddr *)&sin, &sin_len);
	if (clientFD == -1)
	{
		std::cerr << "Failed to accept a new connection\n";
		return;
	}
	std::cout << "New client on socket #" << clientFD << '\n';
	
	_clients.emplace(clientFD, new Client(clientFD));
}

void	Server::removeClient(int fd)
{
	if (_clients.find(fd) != _clients.end())
	{
		std::cout << "Client on socket #" << fd << " disconnected\n";
		delete _clients[fd];
		_clients.erase(fd);
	}
}

void	Server::Run()
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
				removeClient(*it);
	}
}

int	Server::setFDForReading()
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

void	Server::recvProcessCommand
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
				std::string	cmd;
				if (!_clients[s]->receiveCommand(cmd))
					removeClient(s);
				else if (!cmd.empty())
					_irc->ProcessCommand(
						std::make_pair(s, cmd), responseQueue, disconnectList
					);
			}
			--totalFD;
		}
}
