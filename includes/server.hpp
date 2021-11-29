/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 16:37:06 by bahaas            #+#    #+#             */
/*   Updated: 2021/11/29 22:51:04 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include "irc.hpp"

struct t_cmd;
class Server;

// every function pointer will be stored as this type
// typedef void (*cmdFunction)(t_cmd *cmd, Client *client, Server *serv);

/*
void passCmd(t_cmd *cmd, Client *client, Server *serv);
void nickCmd(t_cmd *cmd, Client *client, Server *serv);
void userCmd(t_cmd *cmd, Client *client, Server *serv);
void joinCmd(t_cmd *cmd, Client *client, Server *serv);
void partCmd(t_cmd *cmd, Client *client, Server *serv);
void modeCmd(t_cmd *cmd, Client *client, Server *serv);
void topicCmd(t_cmd *cmd, Client *client, Server *serv);
void namesCmd(t_cmd *cmd, Client *client, Server *serv);
void listCmd(t_cmd *cmd, Client *client, Server *serv);
void inviteCmd(t_cmd *cmd, Client *client, Server *serv);
void kickCmd(t_cmd *cmd, Client *client, Server *serv);
void privmsgCmd(t_cmd *cmd, Client *client, Server *serv);
void noticeCmd(t_cmd *cmd, Client *client, Server *serv);
void whoCmd(t_cmd *cmd, Client *client, Server *serv);
void whoisCmd(t_cmd *cmd, Client *client, Server *serv);
void whowasCmd(t_cmd *cmd, Client *client, Server *serv);
void operCmd(t_cmd *cmd, Client *client, Server *serv);
void quitCmd(t_cmd *cmd, Client *client, Server *serv);
*/
// void infoCmd(t_cmd *cmd, Client *client, Server *serv);
void timeCmd(t_cmd *cmd, Client *client, Server *serv);
void versionCmd(t_cmd *cmd, Client *client, Server *serv);
void awayCmd(t_cmd *cmd, Client *client, Server *serv);
void usersCmd(t_cmd *cmd, Client *client, Server *serv);
void adminCmd(t_cmd *cmd, Client *client, Server *serv);

void unknownCmd(t_cmd *cmd, Client *client, Server *server);

class Server
{
private:
public:
    int _socket;
    int _port;
    int _totChannels;
    int _totClients;
    std::string _name;
    std::string _password;
    std::string _version;
    std::string _userModes;
    std::string _channelModes;

    time_t _init_time;     // FIXME time_t over std::string _str_time
    std::string _str_date; // FIXME one has to be deleted

    std::map<std::string, void (*)(t_cmd *, Client *, Server *)> _cmdsFunction;

    Server()
    {
        _cmdsFunction = _initCmds();
    }

    ~Server(){};

    /*** SETTERS ***/
    void set_name(std::string name)
    {
        this->_name = name;
    }

    void set_version(std::string version)
    {
        this->_version = version;
    }

    /*** GETTERS ***/
    std::string get_name()
    {
        return this->_name;
    }

    std::string get_version()
    {
        return this->_version;
    }

    /**
         * @brief map cmd params to it's ptr function
         *
         * @return std::map<std::string, void (*)(t_cmd *, Client *, Server *)>
         */
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
};

#endif // !SERVER_HPP