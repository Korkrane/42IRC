#include <Server.hpp>

Server::Server(int port, std::string const &password) : _port(port),
														_password(password),
														_fd(-1),
														_irc(NULL)
{
}

Server::~Server()
{
	std::map<int, Client *>::iterator clientIter;
	for (clientIter = _clients.begin(); clientIter != _clients.end(); ++clientIter)
		delete clientIter->second;
	disconnectList.clear();
	responseQueue.clear();
	close(_fd);
}

void Server::SetUp(IRC *irc)
{
	_irc = irc;

	// Create server socket
	protoent *prot = getprotobyname("tcp");
#ifdef __APPLE__
	if ((_fd = socket(AF_INET, SOCK_STREAM, prot->p_proto)) == -1)
	{

#else
	if ((_fd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, prot->p_proto)) == -1)
	{
#endif
		SERVER_ERR("socket");
	}
#ifdef __APPLE__
	fcntl(_fd, F_SETFL, O_NONBLOCK);
#endif

	// Set options for socket
	int opt = 1;
	(void)opt;
#ifdef __linux__
	if (setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(int)) == -1)
		SERVER_ERR("setsockopt");
#endif
	// Bind socket to port
	sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = htons(_port);
	if (bind(_fd, (sockaddr *)&sin, sizeof(sin)) == -1)
		SERVER_ERR("bind");

	// Listen for connections
	if (listen(_fd, MAX_LISTEN) == -1)
		SERVER_ERR("listen");

	std::cout << GREEN
			  << "IRC Server now active on "
			  << inet_ntoa(sin.sin_addr)
			  << ":" << _port
			  << NC << '\n';
}

void Server::acceptClient()
{
	sockaddr_in sin;
	socklen_t sin_len = 0;

	int clientFD = accept(_fd, (sockaddr *)&sin, &sin_len);
	if (clientFD == -1)
	{
		std::cerr << "Failed to accept a new connection\n";
		return;
	}
	std::cout << "New client on socket #" << clientFD << '\n';
	_clients.insert(std::make_pair(clientFD, new Client(clientFD)));
	//_irc->fds.push_back(clientFD);	// FOR TESTING
}

void Server::removeClient(int fd)
{
	if (_clients.find(fd) != _clients.end())
	{
		std::cout << "Client on socket #" << fd << " disconnected\n";
		delete _clients[fd];
		_clients.erase(fd);
		_irc->fds.erase(std::find(_irc->fds.begin(), _irc->fds.end(), fd)); // FOR TESTING
		_irc->delete_user(fd);
	}
}

void Server::Run()
{
	//std::vector<t_clientCmd> responseQueue;
	//std::vector<int> disconnectList;

	while (true)
	{
		responseQueue.clear();
		disconnectList.clear();

		int totalFD = setFDForReading();
		recvProcessCommand(totalFD, responseQueue, disconnectList);

		// Send server's response to clients
		for (std::vector<t_clientCmd>::const_iterator it = responseQueue.begin();
			 it != responseQueue.end(); ++it)
		{
			int clientFD = it->first;
			if (_clients.find(clientFD) != _clients.end())
				_clients[clientFD]->sendResponse(it->second);
		}

		// Disconnect FDs in list
		for (std::vector<int>::const_iterator it = disconnectList.begin();
			 it != disconnectList.end(); ++it)
			removeClient(*it);

		if (_irc->die == true)
			exitProperly();
	}
}

int Server::setFDForReading()
{
	_maxFD = _fd;
	FD_ZERO(&_fdReader);
	FD_SET(_fd, &_fdReader);

	std::map<int, Client *>::iterator clientIter;
	for (clientIter = _clients.begin(); clientIter != _clients.end(); ++clientIter)
	{
		int clientFD = clientIter->first;
		FD_SET(clientFD, &_fdReader);
		if (clientFD > _maxFD)
			_maxFD = clientFD;
	}

	int r = select(_maxFD + 1, &_fdReader, NULL, NULL, NULL);
	if (r == -1)
		SERVER_ERR("select");
	return r;
}

void Server::recvProcessCommand(int totalFD, std::vector<t_clientCmd> &responseQueue, std::vector<int> &disconnectList)
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
				std::string cmd;
				if (!_clients[s]->receiveCommand(cmd))
					removeClient(s);
				else if (!cmd.empty())
				{
#if DEBUG == 1
					std::cout << BLUE << "DEBUG: Server has to process command" << NC << std::endl;
#endif
					_irc->process_command(std::make_pair(s, cmd), responseQueue, disconnectList);
				}
			}
			--totalFD;
		}
}