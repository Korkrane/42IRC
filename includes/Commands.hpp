#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#pragma once

#include "Headers.hpp"
#include "server.hpp"
#include "client.hpp"

class Client;
class Server;
/*
** Classe Command(s)
** Les fonctions qui en font une classe canonique sont partagees
** entre public et protected.
*/
class Commands
{
public:
	/*
	** Constructeur avec arguments
	*/
	Commands(std::string const &serverPass, std::string serverName, std::string serverIP, std::string serverCreationDate);

	/*
	** Destructeur
	*/
	virtual ~Commands(void);

/*
** Fonctions membres principales
*/

//default prototype:
void	timeCmd(Client *client, Server *server);


void	join();
protected:
	/*
	** Constructeur par defaut
	*/
	Commands(void);

	/*
	** Constructeur par copie
	*/
	Commands(Commands const &src);

	/*
	** Operateur d'assignation
	*/
	Commands	&operator=(Commands const &src);

	/*
	** Attributs membres
	*/
	Server *_server;

	/*
	** Liste des commandes (sous forme de map ?)
	*/

	/*
	** Voir la partie Oper ?
	*/
	std::string	_operName;
	std::string _operPass;
};

#endif