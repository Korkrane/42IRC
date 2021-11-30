#ifndef SERVER_HPP
#define SERVER_HPP

//valeur a confirmer
#define MAX_CLIENT 10
#define PORT_SERVER "6667"

#include "irc.hpp"

/**
** TODO: signal handler
*/

struct t_cmd;
class Server;
//class Commands;

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

/**
 * @brief
 *TODO: creer des exceptions appartenant a la classe serveur uniquement ?
 ** Pareil pour Client, Channel et Commands
 */
class Server
{
private:
    /*
    ** Attributs membres
    */
    int                 _socket;
    std::string         _port;
    int                 _totChannels;
    int                 _totClients;
    std::string         _name;
    std::string         _password;
    std::string         _version;
    std::string         _userModes;
    std::string         _channelModes;
    time_t              _init_time;     // FIXME time_t over std::string _str_time
    std::string         _str_date; // FIXME one has to be deleted
    //"Command book"
    std::map<std::string, void (*)(t_cmd *, Client *, Server *)> _cmdsFunction;
    //A creuser
    struct addrinfo*    _serv_info;
    struct addrinfo*    _hints; //needed to initialize server
    //std::string       _domain;//?
    std::string         _server_ip;
    std::string         _server_creation;

    /*
    ** Fonctions membres (classe canonique)
    */
    Server();
    Server(Server const &src);
    Server & operator=(Server const &src);

public:
    Server(std::string port, std::string password);
    virtual ~Server();

    /*** SETTERS ***/
    void                set_name(std::string name);
    void                set_version(std::string version);
    /* Added - a implementer */
    void                set_creation(std::string date);

    /*** GETTERS ***/
    std::string         get_name(void) const ;
    std::string         get_version(void) const;
    /* Added - a implementer*/
    int                 getSocket(void) const;
    std::string         getPort(void) const;
    std::string         getPassword(void) const;
    struct addrinfo*    getServInfo(void) const;
    std::string         get_ip(void) const;
    std::string         get_server_creation(void) const;

    /**
         * @brief map cmd params to it's ptr function
         *
         * @return std::map<std::string, void (*)(t_cmd *, Client *, Server *)>
         */
    std::map<std::string, void (*)(t_cmd *, Client *, Server *)> _initCmds();

    /**
    ** Connections management
    ** TODO: a implementer
    */
    void    init(void);
    void    run(void);
    void    find_to_kill(void);
    void    refuseClient(void);
    void    addClient(void);
    void    removeClient(int fd);
    //Client* find_client_from_fd(int fd);

    /**
    ** Message Management
    ** TODO: a implementer
    */
    void    receiveMessage(Client *client);
    void    sendGreetings(Client *client);
    void    welcomeClient(Client *client);

};

#endif // !SERVER_HPP
