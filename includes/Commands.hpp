#pragma once

#include "Headers.hpp"

class Client;

//class Server;

class Channel;

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

	/*
	** Commande parsee (sous forme de vecteur ?)
	*/

	/*
	** Autres attributs (strings)
	*/
	std::string	_serverPass;
	std::string	_serverName;
	std::string	_serverIP;
	std::string	_serverCreationDate;

	/*
	** Voir la partie Oper ?
	*/
	std::string	_operName;
	std::string _operPass;
};
