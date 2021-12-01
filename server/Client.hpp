#ifndef CLIENT_HPP
#define CLIENT_HPP

#define BUFFER_SIZE	512		// standard buffer size according to RFC

class	IRCServer;

class	Client
{
private:
	char		_buffer[BUFFER_SIZE + 1];
	int const	_fd;

	Client();		// default constructor is not allowed
	Client(int fd);

public:
	~Client() {}

	friend class IRCServer;	// only lets server handle clients
};

#endif
