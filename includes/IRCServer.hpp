#pragma once

#define MAX_CLIENT 10
#define PORT_SERVER 6667

#include "irc.hpp"

typedef std::pair<int, std::string>	t_clientCmd;
class Channel;
class Commands;
class User;

/**
 * @brief 
 * TODO: supprimer les elements redondants avec Server
 */
class IRC
{
private:
    int                     _socket;
    int                     _port;
    int                     _totChannels;
    int                     _totUsers;
    std::vector<Channel *>  _channels;
    std::string             _name;
    std::string             _password;
    std::string             _version;
    std::string             _userModes;
    std::string             _channelModes;
    time_t                  _init_time;     // FIXME time_t over std::string _date
    std::string             _date;          // FIXME one has to be deleted


    struct addrinfo*        _serv_info;
    struct addrinfo*        _hints;            //needed to initialize server
   // std::string         _domain;        
    std::string             _server_ip;     
    std::string             _server_creation;

    //damien added elements
    std::string const       _svPassword;
	std::string const       _discEvenFD;

public:
    IRC();
    IRC(IRC const &src);
    IRC & operator=(IRC const &src);
    IRC(std::string const &password);
    virtual ~IRC();

    std::vector<User *>      _users;
    //damien added elements
    std::vector<int>         fds;

    Commands *              _commands;

    void                    ProcessCommand(t_clientCmd const &command, std::vector<t_clientCmd> &responseQueue, std::vector<int> &disconnectList);
    void                    exec_command(User *);

    void                    set_name(std::string name);
    void                    set_version(std::string version);
    void                    set_creation(std::string date, time_t time);
    void                    set_port(int port);
    void                    set_password(std::string password);

    std::string             get_name(void) const ;
    std::string             get_version(void) const;
    int                     get_port(void) const;
    std::string             get_password(void) const;
    int                     get_socket(void) const;
    struct addrinfo*        get_serv_info(void) const;
    std::string             get_ip(void) const;
    std::string             get_server_creation(void) const;
    std::vector<Channel *>  get_channels(void) const;
    std::vector<User *>		get_users(void) const;
    User                    *get_user(int fd);

    void                    add_channel(Channel *);

    void                    init(void);
    void                    run(void);
    void                    find_to_kill(void);
    void                    refuseClient(void);
    void                    addClient(void);
    void                    removeClient(int fd);

    void                    receiveMessage(User *client);
    void                    sendGreetings(User *client);
    void                    welcomeClient(User *client);

    void					displayServerChannels(void) const;
	void					displayServerUsers(void) const;

    bool				    has_channel(std::string channel_name) const;
    Channel                 *find_channel(std::string channel_name) const;
};