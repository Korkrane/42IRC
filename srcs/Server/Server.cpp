#include "../../includes/server.hpp"

/*
** Constructeurs
*/
Server::Server(void): _socket(0), _port(PORT_SERVER), _totChannels(0), _totClients(0), _name("null"), _password("null"), _version("null"), _userModes("null"), _channelModes("null"), _init_time(), _date("null"), _serv_info(NULL), _hints(NULL), _server_ip("null"), _server_creation("null")
{
#if DEBUG
	std::cout << "Server constructor called" << std::endl;
#endif
_commands = new Commands();
}

/**
 * @brief Construct a new Server:: Server object
 *
 * @param port
 * @param password
 * TODO: implementer proprement
 */
Server::Server(std::string port, std::string password): _socket(0), _port(PORT_SERVER), _totChannels(0), _totClients(0), _name("null"), _password("null"), _version("null"), _userModes("null"), _channelModes("null"), _init_time(), _date("null"), _serv_info(NULL), _hints(NULL), _server_ip("null"), _server_creation("null")
{
	/*
	//gerer les attributs membres relatifs au temps
	//initialiser hints
#if DEBUG
	std::cout << "Server constructor called" << std::endl;
#endif
*/
}

/**
 * @brief Destroy the Server:: Server object
 *
 */
Server::~Server()
{
	delete this->_commands;
	#if DEBUG
	std::cout << "DEBUG: " << "Server destructor called" << std::endl;
	#endif
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

void				Server::set_creation(std::string date, time_t time)
{
	this->_date = date;
    this->_init_time = time;
#if DEBUG
	std::cout << "Creation date has been set successfully to " << date << std::endl;
#endif
	return ;
}

void				Server::set_port(int port)
{
	this->_port = port;
#if DEBUG
	std::cout << "port has been set successfully to " << port << std::endl;
#endif
	return ;
}

void				Server::set_password(std::string password)
{
	this->_password = password;
#if DEBUG
	std::cout << "password has been set successfully to " << password << std::endl;
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
	std::cout << "Server version is " << _version << std::endl;
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

int			Server::get_port(void) const
{
	int port = this->_port;
#if DEBUG
	std::cout << "Server port is " << port << std::endl;
#endif
	return (port);
}

std::string			Server::get_password(void) const
{
	std::string password = this->_password;
#if DEBUG
	std::cout << "Server password is " << password << std::endl;
#endif
	return (password);
}

int			Server::get_socket(void) const
{
	int socket = this->_socket;
#if DEBUG
	std::cout << "Server socket is " << socket << std::endl;
#endif
	return (socket);
}

struct addrinfo*			Server::get_serv_info(void) const
{
    struct addrinfo* serv_info = this->_serv_info;
	return (serv_info);
}

std::string			Server::get_ip(void) const
{
	std::string ip = this->_server_ip;
#if DEBUG
	std::cout << "Server ip is " << ip << std::endl;
#endif
	return (ip);
}

std::string			Server::get_server_creation(void) const
{
	std::string server_creation = this->_server_creation;
#if DEBUG
	std::cout << "Server creation is " << server_creation << std::endl;
#endif
	return (server_creation);
}

std::vector<Channel *>	Server::get_channels(void) const
{
	std::vector<Channel *> channels = this->_channels;
	return (channels);
}

void Server::add_channel(Channel *new_channel)
{
	this->_channels.push_back(new_channel);
}