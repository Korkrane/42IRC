#include "server/IRCServer.hpp"


IRCServer	*gServer = nullptr;		// Global pointer to server (only visible in this source file)


static void	exitProperly()
{
	if (gServer)
		delete gServer;
}

static void	handleSignal(int signum)
{
	if (signum == SIGINT || signum == SIGQUIT)
		std::cout << "\b\bServer is stopped. Good bye!\n";
	exit(0);
}

static bool	checkArgs(int ac, char **av, int &port, std::string &password)
{
	int	iPort, iPassword;

	switch (ac)
	{
	case 4:
		std::cout << "Multi-server is not implemented, second argument is ignored.\n";
		iPort = 2;
		iPassword = 3;
		break;
	case 3:
		iPort = 1;
		iPassword = 2;
		break;
	default:
		std::cerr << "Invalid number of arguments\n";
		return false;
	}

	port = atoi(av[iPort]);
	if (port <= 0 || port > UINT16_MAX)
	{
		std::cerr << "Invalid port number\n";
		return false;
	}
	password = std::string(av[iPassword]);
	return true;
}

int	main(int ac, char **av)
{
	// Register clean up function at exit
	atexit(exitProperly);

	// Register signals to end program
	signal(SIGINT, handleSignal);
	signal(SIGQUIT, handleSignal);

	// Check and obtain information from arguments
	int			port;
	std::string	password;
	if (!checkArgs(ac, av, port, password))
		exit(1);
	
	// Create an instance of the server
	gServer = new IRCServer(port, password);
	// Create an instance of the program (TODO by Mahaut & Baudain)
	IRC	irc;
	gServer->SetUp(&irc);
}
