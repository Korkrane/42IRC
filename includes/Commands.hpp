#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#pragma once

#include "Headers.hpp"

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

	/*
	** Liste des commandes (sous forme de map ?)
	*/

	std::string _unparsed_client_command;		/* raw client command before parsing */
	std::string _prefix;
	std::string _command_name;
	std::vector<std::string> _params;

	/*
	** Voir la partie Oper ?
	*/
	std::string	_operName;
	std::string _operPass;
};

#endif