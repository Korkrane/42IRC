#include "Server.hpp"
//#include "IRCServer.hpp"

// Global pointers (only accessible from this source file)
Server	*gServer = NULL;
IRC		*gIRC = NULL;

static void	exitProperly()
{
	if (gServer)
		delete gServer;
	if (gIRC)
	{
		std::vector<User *> users = gIRC->get_users();
		users.clear();
		/*
		std::vector<User *> users = gIRC->get_users();
		std::vector<Channel *> channels = gIRC->get_channels();

		for(std::vector<User *>::iterator it = users.begin(); it != users.end(); it++)
			delete (*it);
		for(std::vector<Channel *>::iterator it2 = channels.begin(); it2 != channels.end(); it2++)
			delete (*it2);
		*/
		delete gIRC;
	}
}

static void	handleSignal(int signum)
{
	if (signum == SIGINT || signum == SIGQUIT || signum == SIGKILL)
		std::cout	<< GREEN
					<< "\b\bServer is stopped. Good bye!\n"
					<< NC;
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
	atexit(exitProperly);

	// Register signals to end program
	signal(SIGINT, handleSignal);
	signal(SIGQUIT, handleSignal);
	signal(SIGKILL, handleSignal);

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