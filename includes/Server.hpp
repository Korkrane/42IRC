#pragma once

#include "IRC.hpp"
#include "Client.hpp"
#include "IRCServer.hpp"

#define MAX_LISTEN 42
#define SERVER_ERR(err)                                                        \
	do                                                                         \
	{                                                                          \
		std::cerr << RED << err << ": " << NC << strerror(errno) << std::endl; \
		exit(1);                                                               \
	} while (0)

class Client;

class Server
{
private:
	int const _port;				  // Server's port
	std::string const _password;	  // Server's password
	int _fd;						  // Server's socket fd
	IRC *_irc;						  // IRC program
	std::map<int, Client *> _clients; // List of clients, fd as key, Client object as value
	int _maxFD;						  // Current highest client FD
	fd_set _fdReader;				  // Structure to select client FD for reading

	void acceptClient();
	void removeClient(int fd);

	// Make all open socket ready to be read then select them. Return the number of FDs
	// ready to be read
	int setFDForReading();

	// Read from fd to get client commands then forward it to the IRC program
	void recvProcessCommand(int totalFD, std::vector<t_clientCmd> &responseQueue, std::vector<int> &disconnectList);

public:
	Server(int port, std::string const &password);
	~Server();

	std::vector<int> disconnectList;
	std::vector<t_clientCmd> responseQueue;
	void SetUp(IRC *irc);

	// Kick off server's infinite loop (until SIGINT, SIGQUIT or SIGKILL received)
	void Run();

	//friend void	exitProperly();
};

void exitProperly();
void delete_server_allocated_memory();