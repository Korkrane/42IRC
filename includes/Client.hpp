#pragma once

#include "IRC.hpp"

#define BUFFER_SIZE	512		// standard buffer size
#define CMD_DELIM	"\r\n"

class	Server;

class	Client
{
private:
	char		_buffer[BUFFER_SIZE + 1];
	int const	_fd;
	std::string	_cmdBuilder;
	bool		_isGhost;
	std::time_t	_connTime;

	Client();		// default constructor is not allowed
	Client(int fd);

	// Get the command sent to client's socket and build it until delimiter is reached,
	// then it will be put into cmd (passed into argument). Return true when a command
	// (partial or fully constructed) is received, false when the client disconnects and
	// is no longer able to send command
	bool	receiveCommand(std::string &cmd);

	// Send the server's response to the client via its socket
	void	sendResponse(std::string const &resp);

public:
	~Client();

	friend class Server;	// only lets server handle clients
};
