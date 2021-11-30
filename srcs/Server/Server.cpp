#include "../../includes/server.hpp"

/*
** Constructeurs
*/
Server::Server(void): _socket(0), _port(PORT_SERVER), _totChannels(0), _totClients(0), _name("null"), _password("null"), _version("null"), _userModes("null"), _channelModes("null"), _init_time(), _str_date("null"), _serv_info(NULL), _hints(NULL), _server_ip("null"), _server_creation("null")
{
	this->_cmdsFunction = _initCmds();
#if DEBUG
	std::cout << "Server constructor called" << std::endl;
#endif
}

/**
 * @brief Construct a new Server:: Server object
 *
 * @param port
 * @param password
 * TODO: implementer proprement
 */
Server::Server(std::string port, std::string password): _socket(0), _port(PORT_SERVER), _totChannels(0), _totClients(0), _name("null"), _password("null"), _version("null"), _userModes("null"), _channelModes("null"), _init_time(), _str_date("null"), _serv_info(NULL), _hints(NULL), _server_ip("null"), _server_creation("null")
{
	this->_cmdsFunction = _initCmds();
	//gerer les attributs membres relatifs au temps
	//initialiser hints
#if DEBUG
	std::cout << "Server constructor called" << std::endl;
#endif
}

/**
 * @brief Destroy the Server:: Server object
 *
 */
Server::~Server()
{
	//A implementer
	return;
}

/*
** Setters
*/
void				Server::set_name(std::string name)
{
	this->_name = name;
#if DEBUG
	std::cout << "Name has been set successfully to " << name << std::endl;
#endif
	return ;
}

/**
** TODO: checker si les chaine sont correctes (voir rfc)
** pour l'ensemble des attributs membres
*/
void				Server::set_version(std::string version)
{
	this->_version = version;
#if DEBUG
	std::cout << "Version has been set successfully to " << version << std::endl;
#endif
	return ;
}

/*
** Getters
*/
std::string			Server::get_name(void) const
{
	std::string name = this->_name;
#if DEBUG
	std::cout << "Server version is " << version << std::endl;
#endif
	return (name);
}

std::string			Server::get_version(void) const
{
	std::string version = this->_version;
#if DEBUG
	std::cout << "Server version is " << version << std::endl;
#endif
	return (version);
}

std::map<std::string, void (*)(t_cmd *, Client *, Server *)> _initCmds()
{
    std::map<std::string, void (*)(t_cmd *, Client *, Server *)> cmds;
    /*
    cmds["PASS"]    = passCmd;
    cmds["NICK"]    = nickCmd;
    cmds["USER"]    = userCmd;
    cmds["JOIN"]    = joinCmd;
    cmds["PART"]    = partCmd;
	cmds["MODE"]    = modeCmd;
    cmds["TOPIC"]   = topicCmd;
    cmds["NAMES"]   = namesCmd;
    cmds["LIST"]    = listCmd;
    cmds["INVITE"]  = inviteCmd;
    cmds["KICK"]    = kickCmd;
	cmds["PRIVMSG"] = privmsgCmd;
    cmds["WHO"]     = whoCmd;
    cmds["WHOIS"]   = whoisCmd;
    cmds["WHOWAS"]  = whowasCmd;
    cmds["OPER"]    = operCmd;
    cmds["QUIT"]    = quitCmd;
    */
    // cmds["INFO"]  = infoCmd;
    cmds["VERSION"] = versionCmd;
    cmds["USERS"] = usersCmd;
    cmds["AWAY"] = awayCmd;
    cmds["TIME"] = timeCmd;
    cmds["ADMIN"] = adminCmd;
    return cmds;
}
