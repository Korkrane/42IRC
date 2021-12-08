#ifndef SERVER_HPP
#define SERVER_HPP

#include "Headers.hpp"
#include "Client.hpp"
#include "IRCTest.hpp"

#define MAX_LISTEN	42		// Max concurrent connections in queue
#define SERVER_ERR(err)	do { std::cerr << RED << err << ": " << NC << strerror(errno) << std::endl; exit(1); } while (0)	// Print error msg, exit
#define CLIENT_TIMEOUT	10	// Seconds before timing out inactive client

class	Server
{
private:
	int const			_port;		// Server's port
	std::string	const	_password;	// Server's password
	int					_fd;		// Server's socket fd
	IRC					*_irc;		// IRC program

	std::map<int, Client *>	_clients;	// List of clients, fd as key, Client object as value
	int						_maxFD;		// Current highest client FD
	fd_set					_fdReader;	// Structure to select client FD for reading

	pthread_t			_ghostBuster;
	pthread_mutex_t		_mutex;
	bool				_running;

	// Accept new client connection
	void	acceptClient();

	// Remove existing client
	void	removeClient(int fd);

	// Make all open socket ready to be read then select them. Return the number of FDs
	// ready to be read
	int		setFDForReading();

	// Read from fd to get client commands then forward it to the IRC program
	void	recvProcessCommand(int totalFD, std::vector<t_clientCmd> &responseQueue, std::vector<int> &disconnectList);

	// Static function serving as the task for ghostbuster thread
	static void	*timeoutGhostClients(void *server);

public:
	Server(int port, std::string const &password);
	~Server();

	// Set up server properly for listening and accepting clients
	void	SetUp(IRC *irc);
	
	// Kick off server's infinite loop (until SIGINT, SIGQUIT or SIGKILL received)
	void	Run();
};

#endif
