#include "../../includes/client.hpp"

/*
** Constructeur
** TODO: voir ce qu'il y a de mieux pour initialiser les valeurs
** Attention particuliere a porter sur le nickname et le password (?)
*/
Client::Client(void): _nickname("null"), _username("null"), _hostname("null"), _realname("null"), _modes("null"), _has_operator_status(false), _is_away(false), _away_mssg("null"), _password("null"), _fd(0), _message_status(0), _message("null"), _server_name("null"), _server_ip("null"), _server_creation("null"), _channels(NULL), _commands(NULL), _port("null"), _user_is_oper(0), _user_is_away(0), _user_has_registered_pass(0), _user_has_registered_nick(0), _user_is_registered(0)
{
#if DEBUG
	std::cout << "Client default constructor called" << std::endl;
#endif
	return ;
}

/*
** Faire des tests pour voir ce qui est important pour l'initialisation
*/
Client::Client(std::string server_name, std::string server_ip, std::string server_creation, std::string port): _nickname("null"), _username("null"), _hostname("null"), _realname("null"), _modes("null"), _has_operator_status(false), _is_away(false), _away_mssg("null"), _password("null"), _fd(0), _message_status(0), _message("null"), _server_name(server_name), _server_ip(server_ip), _server_creation(server_creation), _channels(NULL), _commands(NULL), _port(port), _user_is_oper(0), _user_is_away(0), _user_has_registered_pass(0), _user_has_registered_nick(0), _user_is_registered(0)
{
#if DEBUG
	std::cout << "Client default constructor called" << std::endl;
#endif
	return ;
}

/*
** Destructeur
*/
Client::~Client(void)
{
#if DEBUG
	std::cout << "Client destructor called" << std::endl;
#endif
    return;
}

/*
** Setters
*/

void		Client::set_nickname(std::string nickname)
{
	this->_nickname = nickname;
#if DEBUG
	std::cout << "Client's nickname has been set to " << nickname << std::endl;
#endif
	return ;
}

void 		Client::set_username(std::string username)
{
	this->_username = username;
#if DEBUG
	std::cout << "Client's username has been set to " << username << std::endl;
#endif
}

void		Client::set_realname(std::string realname)
{
	this->_realname = realname;
#if DEBUG
	std::cout << "Client's realname has been set to " << realname << std::endl;
#endif
}

void		Client::set_hostname(std::string hostname)
{
	this->_hostname = hostname;
#if DEBUG
	std::cout << "Client's hostname has been set to " << hostname << std::endl;
#endif
}

void		Client::set_modes(std::string modes)
{
	this->_modes = modes;
#if DEBUG
	std::cout << "Client's modes has been set to " << modes << std::endl;
#endif
}

void		Client::set_operator_status(bool value)
{
	this->_has_operator_status = value;
#if DEBUG
	std::cout << "Client's operator status has been set to " << value << std::endl;
#endif
}

void 		Client::set_is_away(bool value)
{
	this->_is_away = value;
#if DEBUG
	std::cout << "Client's is away status has been set to " << value << std::endl;
#endif
}

void		Client::set_away_mssg(std::string message)
{
	this->_away_mssg = message;
#if DEBUG
	std::cout << "Client's is away message has been set to " << message << std::endl;
#endif
}

/*
** Getters
*/
std::string	Client::get_nickname(void) const
{
	std::string nick = this->_nickname;
#if DEBUG
	std::cout << "Client's nickname is " << nick << std::endl;
#endif
	return (nick);
}

std::string	Client::get_username(void) const
{
	std::string user = this->_username;
#if DEBUG
	std::cout << "Client's username is " << user << std::endl;
#endif
	return (user);
}

std::string	Client::get_realname(void) const
{
	std::string	real = this->_realname;
#if DEBUG
	std::cout << "Client's realname is " << real << std::endl;
#endif
	return (real);
}

std::string	Client::get_hostname(void) const
{
	std::string host = this->_hostname;
#if DEBUG
	std::cout << "Client's hostname is " << host << std::endl;
#endif
	return (host);
}

std::string	Client::get_modes(void) const
{
	std::string modes;
	modes = this->_modes;
#if DEBUG
	std::cout << "Client's modes is " << modes << std::endl;
#endif
	return (modes);
}

bool		Client::get_operator_status(void) const
{
	bool op = this->_has_operator_status;
#if DEBUG
	std::cout << "Client's operator status is " << op << std::endl;
#endif
	return (op);
}

bool 		Client::get_is_away(void) const
{
	bool op = this->_is_away;
#if DEBUG
	std::cout << "Client's away status is " << op << std::endl;
#endif
	return (op);
}

std::string	Client::get_away_mssg(void) const
{
	std::string away = this->_away_mssg;
#if DEBUG
	std::cout << "Client's away message is " << away << std::endl;
#endif
	return (away);
}
