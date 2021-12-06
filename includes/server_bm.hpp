#pragma once

/*
#define MAX_CLIENT 10
#define PORT_SERVER 6667

#include "irc.hpp"

class Channel;
class Commands;
class User;

class Server
{
private:
    int                 _socket;
    int                 _port;
    int                 _totChannels;
    int                 _totClients;
    std::vector<Channel *> _channels;
    //TODO std::vector<User *> _clients;
    std::string         _name;
    std::string         _password;
    std::string         _version;
    std::string         _userModes;
    std::string         _channelModes;
    time_t              _init_time;     // FIXME time_t over std::string _date
    std::string         _date;          // FIXME one has to be deleted


    struct addrinfo*    _serv_info;
    struct addrinfo*    _hints;            //needed to initialize server
    std::string         _domain;        //?
    std::string         _server_ip;
    std::string         _server_creation;

public:
    Server();
    Server(Server const &src);
    Server & operator=(Server const &src);
    Server(std::string port, std::string password);
    virtual ~Server();

    //public ou privé ?
    Commands *_commands;

    void                set_name(std::string name);
    void                set_version(std::string version);
    void                set_creation(std::string date, time_t time);
    void                set_port(int port);
    void                set_password(std::string password);

    std::string         get_name(void) const ;
    std::string         get_version(void) const;
    int                 get_port(void) const;
    std::string         get_password(void) const;
    int                 get_socket(void) const;
    struct addrinfo*    get_serv_info(void) const;
    std::string         get_ip(void) const;
    std::string         get_server_creation(void) const;
    std::vector<Channel *> get_channels(void) const;

    void add_channel(Channel *);

    void    init(void);
    void    run(void);
    void    find_to_kill(void);
    void    refuseClient(void);
    void    addClient(void);
    void    removeClient(int fd);
    //User* find_client_from_fd(int fd);

    void    receiveMessage(User *client);
    void    sendGreetings(User *client);
    void    welcomeClient(User *client);

    void                    display_channels(void);
};
