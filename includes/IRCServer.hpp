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

public:
    IRC();
    IRC(IRC const &src);
    IRC &operator=(IRC const &src);
    IRC(std::string const &password);
    virtual ~IRC();

    //TODO passer en privé
    std::vector<User *> _users;
    std::vector<int> fds;
    Commands *_commands;
    std::vector<t_clientCmd> _response_queue;

    void ProcessCommand(t_clientCmd const &command, std::vector<t_clientCmd> &responseQueue, std::vector<int> &disconnectList);
    void exec_command(User *);

    void set_name(std::string name);
    void set_version(std::string version);
    void set_creation(std::string date, time_t time);
    void set_port(int port);
    void set_password(std::string password);

    /*** GETTERS ***/
    std::string get_name(void) const;
    std::string get_version(void) const;
    std::string get_password(void) const;
    int get_socket(void) const;
    std::string get_server_creation(void) const;
    std::vector<Channel *> get_channels(void) const;
    std::vector<User *> get_users(void) const;
    User *get_user(int fd);
    User *get_user_ptr(std::string name);
    unsigned int get_channel_nb(void) const;

    /*** METHODS ****/
    Channel *add_channel(std::string name, std::string opt_key);
    Channel *add_channel(std::string name, std::string opt_key, User *user);
    void drop_channel(Channel *to_drop);
    bool find_channel(Channel *to_find);
    bool find_user(std::string nickname);

    std::vector<Channel *>::iterator get_channel_it(Channel *to_find);

    bool has_channel(std::string channel_name) const;
    Channel *find_channel(std::string channel_name) const;
    void process_command(t_clientCmd const &command, std::vector<t_clientCmd> &responseQueue, std::vector<int> &disconnectList);

    bool user_can_join(Channel *channel);
    void send_rpl(std::string error_code, User *user, Channel *channel, std::string arg);
    void send_rpl_to_all_members(Channel *channel, std::string rpl);
    static std::string init_rpl(User *user);
    static std::string build_reply(int code, std::vector<User *>users, std::vector<std::string> params, std::string command);

    void delete_user(int fd);

    /*** DEBUG ***/
    void displayServerChannels(void) const;
    void displayServerUsers(void) const;
};