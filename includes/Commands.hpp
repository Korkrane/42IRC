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
	void		who(Client *client, Server *server);
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
	void		kill(Client *client, Server *server, bool nick_collision);
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
	void		join(Client *client, Server *server);

	/**
	 * @brief 
	 * 
	 * @param command 
	 * @param client 
	 * @param server 
	 * TODO: par sure si cette commande est necessaire
	 */
	void		cap(Client *client, Server *server);

	/**
	 * @brief 
	 * 
	 * @param command 
	 * @param client 
	 * @param server 
	 */
	void		nick(Client *client, Server *server);
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
	* The PART command causes the user sending the message to be removed
	* from the list of active members for all given channels listed in the
	* parameter string.  If a "Part Message" is given, this will be sent
	* instead of the default message, the nickname.  This request is always
	* granted by the server.
	* Parameters: <channel> *( "," <channel> ) [ <Part Message> ]
	 */
	void		part(Client *client, Server *server);
	//verifier qu on a bien un leave channel dans client

	/**
	 * @brief 
	 * 
	 * @param client 
	 * @param server 
	 * The KICK command can be used to request the forced removal of a user
   	 * from a channel.  It causes the <user> to PART from the <channel> by
     * force.  For the message to be syntactically correct, there MUST be
	 * either one channel parameter and multiple user parameter, or as many
     * channel parameters as there are user parameters.  If a "comment" is
     * given, this will be sent instead of the default message, the nickname
     * of the user issuing the KICK.
	 * Parameters: <channel> *( "," <channel> ) <user> *( "," <user> )
               [<comment>]
	 */
	void		kick(Client *client, Server *server);

	/**
	 * @brief 
	 * 
	 * @param client 
	 * @param server 
	 * Parameters: <channel> [ <topic> ]
	 * The TOPIC command is used to change or view the topic of a channel.
     * The topic for channel <channel> is returned if there is no <topic>
     * given.  If the <topic> parameter is present, the topic for that
     * channel will be changed, if this action is allowed for the user
     * requesting it.  If the <topic> parameter is an empty string, the
     * topic for that channel will be removed.
	 */
	void		topic(Client *client, Server *server);

	/**
	 * @brief 
	 * 
	 * @param client 
	 * @param server 
	 * 	 * The list command is used to list channels and their topics.  If the
     * <channel> parameter is used, only the status of that channel is
     * displayed.

   	 * If the <target> parameter is specified, the request is forwarded to
     * that server which will generate the reply.
	 * Parameters: [ <channel> *( "," <channel> ) [ <target> ] ]
	 */
	void		list(Client *client, Server *server);

	/**
	 * @brief 
	 * 
	 * @param client 
	 * @param server 
	 * By using the NAMES command, a user can list all nicknames that are
     * visible to him. For more details on what is visible and what is not,
     * see "Internet Relay Chat: Channel Management" [IRC-CHAN].  The
     * <channel> parameter specifies which channel(s) to return information
     * about.  There is no error reply for bad channel names.

     * If no <channel> parameter is given, a list of all channels and their
     * occupants is returned.  At the end of this list, a list of users who
     * are visible but either not on any channel or not on a visible channel
     * are listed as being on `channel' "*".
	 * Parameters: [ <channel> *( "," <channel> ) [ <target> ] ]
	 */
	void		names(Client *client, Server *server);
};

/* 
** Attention cas particulier :
** Note that this message accepts a special argument ("0"), which is
   a special request to leave all channels the user is currently a member
   of.  The server will process this message as if the user had sent
   a PART command (See Section 3.2.2) for each channel he is a member
   of.
*/