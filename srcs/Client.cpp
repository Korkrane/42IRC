#include "Client.hpp"

Client::Client(int fd) : _fd(fd)
{
	fcntl(fd, F_SETFL, O_NONBLOCK);
}

Client::~Client()
{
	close(_fd);
}

bool	Client::receiveCommand(std::string &cmd)
{
	ssize_t	r = recv(_fd, _buffer, BUFFER_SIZE, 0);

	if (r <= 0)
		return false;
	_buffer[r] = '0';
	_cmdBuilder += _buffer;
	if (_cmdBuilder.find("\r\n", _cmdBuilder.size() - 2) != std::string::npos)
	{
		cmd = _cmdBuilder;
		_cmdBuilder.clear();
	}
	return true;
}

void	Client::sendResponse(std::string const &resp)
{
	
}
