#pragma once

#define PORT_SERVER 6667
#include "IRC.hpp"

typedef std::pair<int, std::string> t_clientCmd;
class Commands;

class IRC
{
private:
    int _socket;
    int _totChannels;
    int _totUsers;
    std::vector<Channel *> _channels;
    std::string _name;
    std::string _password;
    std::string _version;
    std::string _date;
    std::string _server_creation;
    std::string const _svPassword;
    std::string _port;

public:
    IRC();
    IRC(IRC const &src);
    IRC &operator=(IRC const &src);
    IRC(std::string const &password);
    virtual ~IRC();

    bool die;
    std::vector<User *> _users;
    std::vector<int> fds;
    Commands *_commands;
    std::vector<t_clientCmd> _response_queue;
    std::vector<int> _disconnect_list;

    void ProcessCommand(t_clientCmd const &command, std::vector<t_clientCmd> &responseQueue, std::vector<int> &disconnectList);
    void exec_command(User *);

    void set_name(std::string name);
    void set_version(std::string version);
    void set_creation(std::string date);
    void set_port(int port);
    void set_password(std::string password);

    /*** GETTERS ***/
    std::string get_name(void);
    std::string get_version(void);
    std::string get_password(void);
    int get_socket(void);
    std::string get_server_creation(void);
    std::vector<Channel *> get_channels(void);
    std::vector<User *> get_users(void);
    User *get_user(int fd);
    User *get_user_ptr(std::string name);
    Channel *get_channel_ptr(std::string name);
    unsigned int get_channel_nb(void);
    std::string get_port(void);
    void set_port(std::string port_number);

    /*** METHODS ****/
    Channel *add_channel(std::string name, User *user);
    Channel *add_channel(std::string name, std::string opt_key, User *user);
    void drop_channel(Channel *to_drop);
    bool find_channel(Channel *to_find);
    bool find_user(std::string nickname);

    std::vector<Channel *>::iterator get_channel_it(Channel *to_find);

    bool has_channel(std::string channel_name);
    Channel *find_channel(std::string channel_name);
    void process_command(t_clientCmd const &command, std::vector<t_clientCmd> &responseQueue, std::vector<int> &disconnectList);

    bool user_can_join(Channel *channel);
    
    void send_rpl_display_all_users(User *user, User *target, std::string command);
    void send_rpl_display_user(User *user, std::string command);

    int send_rpl(std::string code, User *user, std::vector<std::string> params, std::string command);
    int send_rpl_to_all_members(std::string code, std::vector<User* > user, std::vector<std::string> params, std::string command);

    static std::string init_rpl(User *user);
    std::string build_reply(std::string code, User * user, std::vector<std::string> params, std::string command);

    void delete_user(int fd);

    /*** DEBUG ***/
    void displayServerChannels(void);
    void displayServerUsers(void);
};