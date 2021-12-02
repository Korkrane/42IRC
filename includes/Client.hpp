#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "Headers.hpp"

#define BUFFER_SIZE	512		// standard buffer size

class	Server;

class	Client
{
private:
	char		_buffer[BUFFER_SIZE + 1];
	int const	_fd;

	std::string	_cmdBuilder;

	Client();		// default constructor is not allowed
	Client(int fd);

	bool	receiveCommand(std::string &cmd);
	void	sendResponse(std::string const &resp);

public:
	~Client();

	friend class Server;	// only lets server handle clients
};

#endif
