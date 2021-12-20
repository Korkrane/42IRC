#include "Server.hpp"

// Global pointers (only accessible from this source file)
Server *gServer = NULL;
IRC *gIRC = NULL;

void delete_channels(User *user)
{
	(void)user;

	if (user)
	{
		std::vector<Channel *> chans = user->get_channels();
		unsigned int size = chans.size();
		if (size != 0)
		{
			chans.clear();
		}
		/*
		std::vector<Channel *>::iterator it = chans.begin();
		std::vector<Channel *>::iterator ite = chans.end();

		while (it != ite)
		{
			if ((*it))
			{
				delete (*it);
			}
			it++;
		}
		chans.erase();
		*/
	}
	//TODO: faire un get_channel?
	//std::vector<Channel *> chans = ;
	return;
}

//TODO: fonction Mahaut - a verifier + deplacer ? Faire un fichier dedie a l exit et aux delete ? IRC Server et pas gServer
void delete_server_allocated_memory(void)
{
	//Faire le tour de toutes les channels pour les delete
	std::vector<Channel *> chans = gIRC->get_channels();

	std::vector<Channel *>::iterator it = chans.begin();
	std::vector<Channel *>::iterator ite = chans.end();

	while (it != ite)
	{
		delete (*it);
		it++;
	}
#if MALATINI == 1
	std::cout << PURPLE << "Deleted all channels" << NC << std::endl;
#endif
	//faire le tour de tous les users pour les delete

	/* */
	std::vector<User *> users = gIRC->get_users();
	unsigned int size = users.size();
	if (size == 0)
		return;
	std::vector<User *>::iterator itb = users.begin();
	std::vector<User *>::iterator itbe = users.end();
	while (itb != itbe)
	{
		if (*itb)
		{
			delete_channels((*itb));
			//(*itb)->_channels.erase();
			//delete (*itb);
		}
		itb++;
	}
#if MALATINI == 1
	std::cout << PURPLE << "Deleted all users" << NC << std::endl;
#endif
	return;
}

void exitProperly()
{
#if MALATINI == 1
	std::cout << RED << "Exit properly called." << NC << std::endl;
#endif
	if (gIRC)
	{
		delete_server_allocated_memory();
		delete gIRC;
	}

	if (gServer)
	{
		delete gServer;
	}
}

static void handleSignal(int signum)
{
	if (signum == SIGINT || signum == SIGQUIT || signum == SIGKILL)
		std::cout << GREEN
				  << "\b\bServer is stopped. Good bye!\n"
				  << NC;
	exit(0);
}

static bool checkArgs(int ac, char **av, int &port, std::string &password)
{
	int iPort, iPassword;

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

int main(int ac, char **av)
{
	// Register clean up function at exit
	atexit(exitProperly);

	// Register signals to end program
	signal(SIGINT, handleSignal);
	signal(SIGQUIT, handleSignal);
	signal(SIGKILL, handleSignal);

	// Check and obtain information from arguments
	int port;
	std::string password;
	if (!checkArgs(ac, av, port, password))
		exit(1);

	// Create an instance of the server and program
	gServer = new Server(port, password);
	gIRC = new IRC(password);

	gServer->SetUp(gIRC);
	gServer->Run();
}