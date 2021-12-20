#include "Server.hpp"

Server::Server(int port, std::string const &password) :
	_port(port),
	_password(password),
	_fd(-1),
	_irc(NULL)
{}

Server::~Server()
{
	std::map<int, Client *>::iterator	clientIter;
	for (clientIter = _clients.begin(); clientIter != _clients.end(); ++clientIter)
		delete clientIter->second;
	close(_fd);
}

void	Server::SetUp(IRC *irc)
{
	_irc = irc;

	// Create server socket
	protoent	*prot = getprotobyname("tcp");
#ifdef __APPLE__
	if ((_fd = socket(AF_INET, SOCK_STREAM, prot->p_proto)) == -1)
#else
	if ((_fd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, prot->p_proto)) == -1)
#endif
		SERVER_ERR("socket");

#ifdef __APPLE__
	fcntl(fd, F_SETFL, O_NONBLOCK);
#endif

	// Set options for socket
	int	opt = 1;
	if (setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(int)) == -1)
		SERVER_ERR("setsockopt");

	// Bind socket to port
	sockaddr_in	sin;
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = htons(_port);
	if (bind(_fd, (sockaddr *)&sin, sizeof(sin)) == -1)
		SERVER_ERR("bind");

	// Listen for connections
	if (listen(_fd, MAX_LISTEN) == -1)
		SERVER_ERR("listen");

	std::cout	<< GREEN
				<< "IRC Server now active on "
				<< inet_ntoa(sin.sin_addr)
				<< ":" << _port
				<< NC << '\n';
}

void	Server::acceptClient()
{
	sockaddr_in	sin;
	socklen_t	sin_len = 0;

	int	clientFD = accept(_fd, (sockaddr *)&sin, &sin_len);
	if (clientFD == -1)
	{
		std::cerr << "Failed to accept a new connection\n";
		return;
	}
	std::cout << "New client on socket #" << clientFD << '\n';
	
	_clients.insert(std::make_pair(clientFD, new Client(clientFD)));
	// _irc->fds.insert(clientFD);	// FOR TESTING. Delete this line in production
}

void	Server::removeClient(int fd)
{
	if (_clients.find(fd) != _clients.end())
	{
		delete _clients[fd];
		_clients.erase(fd);
	}
}

void	Server::Run()
{
	int	totalFD;

	while (true)
	{
		disconnectGhostClients();
		totalFD = setFDForReading();
		recvProcessCommand(totalFD);
		usleep(50);	// Sleep for 50 microsecond to save CPU cycle
	}
}

void	Server::disconnectGhostClients()
{
	std::time_t			now(std::time(NULL));
	std::vector<int>	disconnectList;

	std::map<int, Client *>::iterator	clientIter;
	std::vector<int>::iterator			it;
	for (clientIter = _clients.begin(); clientIter != _clients.end(); ++clientIter)
	{
		int	clientFD = clientIter->first;
		Client &client(*clientIter->second);
		if (client._isGhost && std::difftime(now, client._connTime) >= CLIENT_TIMEOUT)
			disconnectList.push_back(clientFD);
	}

	for (it = disconnectList.begin(); it != disconnectList.end(); ++it)
		removeClient(*it);
}

int	Server::setFDForReading()
{
	_maxFD = _fd;
	FD_ZERO(&_fdReader);
	FD_SET(_fd, &_fdReader);

	std::map<int, Client *>::iterator	clientIter;
	for (clientIter = _clients.begin(); clientIter != _clients.end(); ++clientIter)
	{
		int	clientFD = clientIter->first;
		FD_SET(clientFD, &_fdReader);
		if (clientFD > _maxFD)
			_maxFD = clientFD;
	}

	int	r = select(_maxFD + 1, &_fdReader, NULL, NULL, NULL);
	if (r == -1)
		SERVER_ERR("select");
	return r;
}

void	Server::recvProcessCommand(int totalFD)
{
	std::vector<t_clientCmd>			responseQueue;
	std::vector<int>					disconnectList;
	std::vector<t_clientCmd>::iterator	rIt;
	std::vector<int>::iterator			dIt;
	std::string	cmd;

	// Checking each socket for reading, starting from FD 3 because there should be nothing
	// to read from 0 (stdin), 1 (stdout) and 2 (stderr)
	for (int s = 3; s <= _maxFD && totalFD; ++s)
		if (FD_ISSET(s, &_fdReader))
		{
			if (s == _fd)
				acceptClient();
			else
			{
				responseQueue.clear();
				disconnectList.clear();
				cmd.clear();

				// Receive a full command, with delimiter, then send it to program to process,
				// then grab program's response(s)
				if (!_clients[s]->receiveCommand(cmd))
				{
					removeClient(s);
					_irc->delete_user(s);	// Tell the program that client is disconnected
				}
				else if (!cmd.empty())
				{
					_irc->process_command(
						std::make_pair(s, cmd), responseQueue, disconnectList
					);
					// Send server's response to clients
					for (rIt = responseQueue.begin(); rIt != responseQueue.end(); ++rIt)
					{
						int	clientFD = rIt->first;
						if (_clients.find(clientFD) != _clients.end())
							_clients[clientFD]->sendResponse(rIt->second);
					}
					// Disconnect FDs in list
					for (dIt = disconnectList.begin(); dIt != disconnectList.end(); ++dIt)
						removeClient(*dIt);
				}
			}
			--totalFD;
		}
}