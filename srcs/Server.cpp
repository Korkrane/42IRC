#include "Server.hpp"

Server::Server(int port, std::string const &password) :
	_port(port),
	_password(password),
	_fd(-1),
	_irc(NULL)
{}

Server::~Server()
{
	_running = false;
	pthread_join(_ghostBuster, NULL);
	pthread_mutex_destroy(&_mutex);
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
	if ((_fd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, prot->p_proto)) == -1)
		SERVER_ERR("socket");

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

	// Setup thread to timeout ghost client
	_running = true;
	if (pthread_mutex_init(&_mutex, NULL) != 0)
		SERVER_ERR("pthead_mutex_init");
	if (pthread_create(&_ghostBuster, NULL, timeoutGhostClients, this) != 0)
		SERVER_ERR("pthread_create");

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
	
	pthread_mutex_lock(&_mutex);
	_clients.insert(std::make_pair(clientFD, new Client(clientFD)));
	pthread_mutex_unlock(&_mutex);
	_irc->fds.push_back(clientFD);	// FOR TESTING. Delete this line for production
}

void	Server::removeClient(int fd)
{
	if (_clients.find(fd) != _clients.end())
	{
		delete _clients[fd];
		_clients.erase(fd);
		_irc->fds.erase(std::find(_irc->fds.begin(), _irc->fds.end(), fd));	// FOR TESTING. Delete this line for production
	}
}

void	Server::Run()
{
	std::vector<t_clientCmd>			responseQueue;
	std::vector<int>					disconnectList;
	std::vector<t_clientCmd>::iterator	rIt;
	std::vector<int>::iterator			dIt;

	while (true)
	{
		responseQueue.clear();
		disconnectList.clear();
	
		int	totalFD = setFDForReading();
		recvProcessCommand(totalFD, responseQueue, disconnectList);

		// Send server's response to clients
		pthread_mutex_lock(&_mutex);
		for (rIt = responseQueue.begin(); rIt != responseQueue.end(); ++rIt)
		{
			int	clientFD = rIt->first;
			if (_clients.find(clientFD) != _clients.end())
				_clients[clientFD]->sendResponse(rIt->second);
		}

		// Disconnect FDs in list
		for (dIt = disconnectList.begin(); dIt != disconnectList.end(); ++dIt)
			removeClient(*dIt);
		pthread_mutex_unlock(&_mutex);
	}
}

int	Server::setFDForReading()
{
	_maxFD = _fd;
	FD_ZERO(&_fdReader);
	FD_SET(_fd, &_fdReader);

	std::map<int, Client *>::iterator	clientIter;
	pthread_mutex_lock(&_mutex);
	for (clientIter = _clients.begin(); clientIter != _clients.end(); ++clientIter)
	{
		int	clientFD = clientIter->first;
		FD_SET(clientFD, &_fdReader);
		if (clientFD > _maxFD)
			_maxFD = clientFD;
	}
	pthread_mutex_unlock(&_mutex);

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
				pthread_mutex_lock(&_mutex);
				if (!_clients[s]->receiveCommand(cmd))
				{
					removeClient(s);
					pthread_mutex_unlock(&_mutex);
				}
				else if (!cmd.empty())
				{
					pthread_mutex_unlock(&_mutex);
					_irc->ProcessCommand(
						std::make_pair(s, cmd), responseQueue, disconnectList
					);
				}
			}
			--totalFD;
		}
}

void	*Server::timeoutGhostClients(void *server)
{
	Server								&s(*(Server *)server);
	std::map<int, Client *>::iterator	clientIter;
	std::time_t							timer(std::time(NULL));
	Client								*c;
	std::vector<int>					disconnectList;

	while (s._running)
	{
		sleep(1);	// Scan client's list every second
		++timer;
		disconnectList.clear();
		pthread_mutex_lock(&s._mutex);
		for (clientIter = s._clients.begin(); clientIter != s._clients.end(); ++clientIter)
		{
			c = clientIter->second;
			if (c->_isGhost && timer - c->_connTime >= CLIENT_TIMEOUT)
				disconnectList.push_back(c->_fd);
		}
		for (std::vector<int>::iterator it = disconnectList.begin(); it != disconnectList.end(); ++it)
			s.removeClient(*it);
		pthread_mutex_unlock(&s._mutex);
	}
	return (NULL);
}
