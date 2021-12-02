#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>
#include <sstream>

#define BUFFER_SIZE	512		// standard buffer size according to RFC

class	IRCServer;

class	Client
{
private:
	char		_buffer[BUFFER_SIZE + 1];
	int const	_fd;

	std::stringstream	_cmdBuilder;

	Client();		// default constructor is not allowed
	Client(int fd);

	std::string	receiveCommand();
	void		sendResponse(std::string const &resp);

public:
	~Client();

	friend class IRCServer;	// only lets server handle clients
};

Client::Client(int fd) :
	_fd(fd)
{
	fcntl(fd, F_SETFL, O_NONBLOCK);
}

Client::~Client()
{
	close(_fd);
}

std::string	Client::receiveCommand()
{

}

void	Client::sendResponse(std::string const &resp)
{
	
}

#endif
