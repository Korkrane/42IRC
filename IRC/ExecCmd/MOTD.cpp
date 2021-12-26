#include "../IRC.hpp"
#include <fstream>

#define MOTD_FILE	"config/motd"

static std::vector<string>	MOTDLines;
static bool	motdInit = false;

// Initialize message of the day from file
static void	initMOTD()
{
	motdInit = true;
	std::ifstream	motdFile(MOTD_FILE);
	if (!motdFile.is_open())
	{
		char	*cwd(getcwd(NULL, 0));
		std::cout	<< RED << "Cannot read message of the day from "
					<< cwd << '/' << MOTD_FILE << '\n' << NC;
		free(cwd);
		return;
	}

	string		line;
	while (std::getline(motdFile, line))
		MOTDLines.push_back(line);
	motdFile.close();
}

// Append message of the day messages to response queue
void	IRC::appendMOTDToQueue(User *user, std::vector<t_clientCmd> &responseQueue) const
{
	string	motd;

	if (!motdInit)
		initMOTD();
	if (MOTDLines.empty())
		motd = getResponseFromCode(user, ERR_NOMOTD, NULL);
	else
	{
		motd = getResponseFromCode(user, RPL_MOTDSTART, NULL);
		for (std::vector<string>::iterator it(MOTDLines.begin());
			it != MOTDLines.end(); ++it)
		{
			motd += getResponseFromCode(
				user, RPL_MOTD,
				(string[]){ *it }	
			);
		}
		motd += getResponseFromCode(user, RPL_ENDOFMOTD, NULL);
	}
	responseQueue.push_back(std::make_pair(user->_fd, motd));
}

void	IRC::execMOTD(Command const &cmd, std::vector<t_clientCmd> &responseQueue)
{
	appendMOTDToQueue(cmd._user, responseQueue);
}
