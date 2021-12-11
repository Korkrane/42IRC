#ifndef IRCTEST_HPP
#define IRCTEST_HPP

#include "Headers.hpp"
#include <set>

typedef std::pair<int, std::string>	t_clientCmd;

// prototype to the class containing the data and structure of the IRC server
class	IRC
{
private:
	std::string const	_svPassword;
	std::string const	_discEvenFD;

public:

	std::set<int> fds;	// FOR TESTING

	IRC(std::string const &password) :
		_svPassword(password),
		_discEvenFD("delete even\r\n")	// command to disconnect even number fds
	{}

	// Method to be called by the server. Process a command from a client, then queue
	// response messages into responseQueue. If there are clients to be removed, their
	// fd should also be added to disconnectList.
	// For testing purposes, this IRC program broadcast message to every client connected
	// to the server
	void ProcessCommand(t_clientCmd const &command, std::vector<t_clientCmd> &responseQueue, std::vector<int> &disconnectList)
	{
		int	clientFD = command.first;
		std::string const	&cmd = command.second;

		for (std::set<int>::iterator it = fds.begin(); it != fds.end(); ++it)
			if (*it != clientFD)
				responseQueue.push_back(std::make_pair(*it, cmd));
		
		// Add even fds to the disconnect list
		if (cmd == _discEvenFD)
		{
			for (std::set<int>::iterator it = fds.begin(); it != fds.end(); ++it)
				if (*it % 2 == 0)
					disconnectList.push_back(*it);
			for (std::vector<int>::iterator it = disconnectList.begin(); it != disconnectList.end(); ++it)
				ClientDisconnect(*it);
		}
	}

	// Called by the server to indicate that a client has disconnected
	void ClientDisconnect(int fd)
	{
		std::set<int>::iterator idx = std::find(fds.begin(), fds.end(), fd);
		if (idx != fds.end())
			fds.erase(idx);
	}
};

#endif
