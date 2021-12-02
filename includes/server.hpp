#ifndef SERVER_HPP
#define SERVER_HPP

#define MAX_CLIENT 10
#define PORT_SERVER 6667

struct t_cmd;
#include "channel.hpp"
#include "client.hpp"
#include "Commands.hpp"

class Channel;
class Commands;
class Client;

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
    int                 _port;
    int                 _totChannels;
    int                 _totClients;
    std::string         _name;
    std::string         _password;
    std::string         _version;
    std::string         _userModes;
    std::string         _channelModes;
    time_t              _init_time;     // FIXME time_t over std::string _date
    std::string         _date;          // FIXME one has to be deleted

    //"Command book" //TODO move it to cmds class
    //std::map<std::string, void (*)(t_cmd *, Client *, Server *)> _cmds;

    //A creuser
    struct addrinfo*    _serv_info;
    struct addrinfo*    _hints; //needed to initialize server
    //std::string       _domain;//?
    std::string         _server_ip;
    std::string         _server_creation;

    std::vector<Channel *> _channels;

public:
    /*
    ** Fonctions membres (classe canonique)
    */
    Server();
    Server(Server const &src);
    Server & operator=(Server const &src);
    Server(std::string port, std::string password);
    virtual ~Server();

    //TODO mettre en public ou privé ? pour l'exec de commande : client->server->join() ou client->get_server()->join();
    Commands *_commands;

    /*** SETTERS ***/
    void                set_name(std::string name);
    void                set_version(std::string version);
    void                set_creation(std::string date, time_t time);
    void                set_port(int port);
    void                set_password(std::string password);

    /*** GETTERS ***/
    std::string         get_name(void) const ;
    std::string         get_version(void) const;
    int                 get_port(void) const;
    std::string         get_password(void) const;
    int                 get_socket(void) const;
    struct addrinfo*    get_serv_info(void) const;
    std::string         get_ip(void) const;
    std::string         get_server_creation(void) const;
    std::vector<Channel *> get_channels(void) const;
    //std::map<std::string, void (*)(t_cmd *, Client *, Server *)>    get_cmds(void) const;

    /*** MEMBERS FUNCTIONS ***/
    //std::map<std::string, void (*)(t_cmd *, Client *, Server *)> _initCmds();

    void add_channel(Channel *);

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

    /* Display / Debug */ //TODO
    void                    display_channels(void);
};

#endif // !SERVER_HPP