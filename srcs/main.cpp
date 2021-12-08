#include "Server.hpp"


// Global pointers (only accessible from this source file)
Server	*gServer = NULL;
IRC		*gIRC = NULL;

static void	cleanupBeforeExit()
{
	if (gServer)
		delete gServer;
	if (gIRC)
		delete gIRC;
}

static void	handleSignal(int signum)
{
	if (signum == SIGINT || signum == SIGQUIT)
		std::cout	<< GREEN
					<< "\b\bServer is stopped. Good bye!\n"
					<< NC;
	exit(0);
}

static bool	checkArgs(int ac, char **av, int &port, std::string &password)
{
	int	iPort, iPassword;

	if (ac == 3)
		iPort = 1, iPassword = 2;
	else if (ac == 4)
	{
		std::cout << "Multi-server is not implemented, second argument is ignored.\n";
		iPort = 2, iPassword = 3;
	}
	else
	{
		std::cerr << "Invalid number of arguments\n";
		return false;
	}

	port = std::atoi(av[iPort]);
	if (port <= 0 || port > 0xffff)
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
	atexit(cleanupBeforeExit);

	// Register signals to end program
	signal(SIGINT, handleSignal);
	signal(SIGQUIT, handleSignal);
	signal(SIGALRM, handleSignal);

	// Check and obtain information from arguments
	int			port;
	std::string	password;
	if (!checkArgs(ac, av, port, password))
		exit(1);
	
	// Create an instance of the server and program
	gServer = new Server(port, password);
	gIRC = new IRC(password);

	gServer->SetUp(gIRC);
	gServer->Run();
}
