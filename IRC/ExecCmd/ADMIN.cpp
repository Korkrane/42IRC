#include "../IRC.hpp"
#include <fstream>

#define ADMININFO_FILE		"config/admin"
#define DEFAULT_ADMIN_NAME	"Damien Dam"
#define DEFAULT_ADMIN_LOC	"Paris FR"
#define DEFAULT_ADMIN_EMAIL	"qdam@student.42.fr"

struct	AdminInfo
{
	string	Name;
	string	Location;
	string	Email;

	AdminInfo() :
		Name(DEFAULT_ADMIN_NAME),
		Location(DEFAULT_ADMIN_LOC),
		Email(DEFAULT_ADMIN_EMAIL)
	{}
};

static AdminInfo	admin;
static bool	adminInit = false;

static void	initAdminInfo()
{
	adminInit = true;
	std::ifstream	adminFile(ADMININFO_FILE);
	if (!adminFile.is_open())
	{
		char	*cwd(getcwd(NULL, 0));
		std::cout	<< RED << "Cannot read admin info from "
					<< cwd << '/' << ADMININFO_FILE
					<< ". Using default information\n" << NC;
		free(cwd);
		return;
	}

	string		name;	std::getline(adminFile, name);
	string		loc; 	std::getline(adminFile, loc);
	string		email;	std::getline(adminFile, email);
	if (!name.empty())	admin.Name = name;
	if (!loc.empty())	admin.Location = loc;
	if (!email.empty())	admin.Email = email;
	adminFile.close();
}

void	IRC::execADMIN(Command const &cmd, std::vector<t_clientCmd> &responseQueue)
{
	if (!adminInit)
		initAdminInfo();
	
	User	*user(cmd._user);
	string	resp(
		  getResponseFromCode(user, RPL_ADMINME, NULL)
		+ getResponseFromCode(user, RPL_ADMINLOC1, (string[]){ admin.Name })
		+ getResponseFromCode(user, RPL_ADMINLOC2, (string[]){ admin.Location })
		+ getResponseFromCode(user, RPL_ADMINEMAIL, (string[]){ admin.Email })
	);
	responseQueue.push_back(std::make_pair(user->_fd, resp));
}
