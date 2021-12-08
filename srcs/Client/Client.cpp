#include "Client.hpp"

Client::Client(int fd) : _fd(fd)
{
	// Make reading and writing to fd non-blocking
	fcntl(fd, F_SETFL, O_NONBLOCK);
	//Commentaires Mahaut
	//Quand un client est construit, un User va l'etre egalement
}

Client::~Client()
{
	// Close fd before deconstructing object
	close(_fd);
}

bool Client::receiveCommand(std::string &cmd)
{
	ssize_t r = recv(_fd, _buffer, BUFFER_SIZE, 0);
	if (r <= 0)
		return false;

	// Null terminate command received
	_buffer[r] = '\0';

	// Add to current command builder
	_cmdBuilder += _buffer;

	// Try finding delimiter at the end of the command. If found, put everything
	// to cmd then reset command builder
	if (_cmdBuilder.find(CMD_DELIM, _cmdBuilder.size() - 2) != std::string::npos)
	{
		cmd = _cmdBuilder;
		_cmdBuilder.clear();
	}
	return true;
}

void Client::sendResponse(std::string const &resp)
{
	send(_fd, resp.c_str(), resp.size(), 0);
}