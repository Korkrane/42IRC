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

	Commands(void) : _cmds(_initCmds())
	{
		#if DEBUG
			std::cout << "Commands constructor called" << std::endl;
		#endif
	};

	Commands(Commands const &src);
	Commands	&operator=(Commands const &src);
	Commands(std::string const &serverPass, std::string serverName, std::string serverIP, std::string serverCreationDate);
	virtual ~Commands()
	{
		#if DEBUG
			std::cout << "DEBUG: " << "Command destructor called" << std::endl;
		#endif
	};


	/*** Fonctions membres ***/
	std::map<std::string, void (*)(Client *, Server *)>	get_cmds(void) const
	{
		std::map<std::string, void (*)(Client *, Server *)> cmds = this->_cmds;
		return (cmds);
	}

	std::map<std::string, void (*)(Client *, Server *)> _initCmds()
	{
    	std::map<std::string, void (*)(Client *, Server *)> cmds;

		cmds["AWAY"] = away_cmd;
		cmds["TIME"] = time_cmd;
    	return cmds;
	}

	static void	time_cmd(Client *client, Server *server);
	static void away_cmd(Client *client, Server *server);
    static void unknown_cmd(Client *client, Server *server);
	//static void	join(Client *client, Server *server);

protected:
	Server *_server;
    std::map<std::string, void (*)(Client *, Server *)> _cmds;

	/*
	** Voir la partie Oper ?
	*/
	std::string	_operName;
	std::string _operPass;
};

#endif