#pragma once
#include "irc.hpp"

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

private:
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

	/**
	** Important : il nous faudrait une fonction reply qui va etre
	** appelee a la fin de chaque commande (pour envoyer code/info au serveur ?)
	*/

public:
	/**
	** Fonctions necessaires pour la commande who (notamment)
	** Pas sure a 100% des protos
	** Le param de who pour correspondre au une channel ou a autre chose
	** TODO: mahaut WHO
	*/
	void		who(Commands *command, Client *client, Server *server);
	static void	displayAllClients(Channel *channel);
	//Appelera la sous fonction displayClientsFromChannel ?
	static void	displayChannel(Channel *channel, Client *client);
	//Affichage specifique si le client est operateur ?
	static void	displayClientsFromChannel(Channel *channel, Client *client);
	//Va permettre de verifier si la channel passee en parametre existe bien
	static void	paramsIsCorrectChannel(Commands *command, Server *server);
	static void	paramsIsCorrectOther(Commands *command, Server *server);

	/**
	** Commande KILL
	** TODO: Mahaut
	** Voir comment le serveur doit reagir si il y a une nick collision
	*/
	void		kill(Commands *command, Client *client, Server *server, bool nick_collision);
	//verifier les fonctions annexes relatives aux clients sont bien implementees
	//nickname exists
	//leave all channels
	//set message status

	/**
	 * @brief 
	 * 
	 * @param command 
	 * @param client 
	 * @param server 
	 * Parameters: ( <channel> *( "," <channel> ) [ <key> *( "," <key> ) ] )
	 ** Is used by user to request to start listening to a specific channel.
	 ** Server "should not use lists when reading JOIN messages to clients".
	 ** Once a user has join a channel, he is aware when a command is affecting the server :
	 ** JOIN, MODE, KICK, PART, QUIT and PRIVMSG/NOTICE.
	 ** See details on RFC 2812.
	 */
	void		join(Commands *command, Client *client, Server *server);

	/**
	 * @brief 
	 * 
	 * @param command 
	 * @param client 
	 * @param server 
	 * TODO: par sure si cette commande est necessaire
	 */
	void		cap(Commands *command, Client *client, Server *server);

	/**
	 * @brief 
	 * 
	 * @param command 
	 * @param client 
	 * @param server 
	 */
	void		nick(Commands *command, Client *client, Server *server);
	/*
	** Autres fonctions necessaires a nick
	*/
	static bool	checkNickGrammar(std::string nick);

	/**
	 * @brief 
	 * 
	 * @param command 
	 * @param client 
	 * @param server 
	 */
	void		part(Commands *command, Client *client, Server *server);
	//verifier qu on a bien un leave channel dans client

};

/* 
** Attention cas particulier :
** Note that this message accepts a special argument ("0"), which is
   a special request to leave all channels the user is currently a member
   of.  The server will process this message as if the user had sent
   a PART command (See Section 3.2.2) for each channel he is a member
   of.
*/