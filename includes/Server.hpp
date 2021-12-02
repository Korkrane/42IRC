#ifndef SERVER_HPP
#define SERVER_HPP

#include "Headers.hpp"
#include "Client.hpp"

#define MAX_LISTEN	42		// Max concurrent connections in queue
#define SERVER_ERR(err)	do { std::cerr << RED << err << ": " << NC << strerror(errno) << std::endl; exit(1); } while (0)	// Print error msg, exit

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

class	Server
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

	// Remove existing client
	void	removeClient(int fd);

	// Make all open socket ready to be read then select them. Return the number of FDs
	// ready to be read
	int		setFDForReading();

	// Read from fd to get client commands then forward it to the IRC program
	void	recvProcessCommand(int totalFD, std::vector<t_clientCmd> &responseQueue, std::vector<int> &disconnectList);

public:
	Server(int port, std::string const &password);
	~Server();

	// Set up server properly for listening and accepting clients
	void	SetUp(IRC *irc);
	
	// Kick off server's infinite loop (until Ctrl+C or Ctrl+\\)
	void	Run();
};

#endif
