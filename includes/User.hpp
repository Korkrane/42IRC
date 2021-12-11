#pragma once

#include <IRC.hpp>

class IRC;
class Channel;

struct t_cmd
{
    std::string _unparsed;
    std::string _prefix;
    std::string _command_name;
    std::vector<std::string> _params;
};

class User
{
private:
    User(User const &src);
    User &operator=(User const &src);

    int _socket;
    std::string _nickname;
    std::string _username;
    std::string _hostname;
    std::string _realname;
    std::string _modes;
    bool _has_operator_status;
    bool _is_away;
    std::string _away_mssg;
    std::string _password;
    int _message_status;
    std::string _message;
    std::vector<Channel *> _channels;
    unsigned int _channels_nb;

    bool _user_is_oper;
    bool _user_is_away;
    bool _user_has_registered_pass;
    bool _user_has_registered_nick;
    bool _user_is_registered;

    /* Correspond a la commande pre parsee */

    std::string _unparsed_client_command;
    std::string _prefix;
    std::string _command_name;

public:
    std::vector<std::string> _params;
    std::vector<t_cmd> _commands;
    void split_if_multiple_command();

    void set_params(std::vector<std::string>);
    void set_prefix(std::string);
    void set_command(std::string);

    IRC *_IRCserver;

    bool _to_delete;
    User(void);
    User(int fd);
    virtual ~User();

    std::string get_nickname(void) const;
    std::string get_username(void) const;
    std::string get_realname(void) const;
    std::string get_hostname(void) const;
    std::string get_modes(void) const;
    bool get_operator_status(void) const;
    bool get_is_away(void) const;
    std::string get_away_mssg(void) const;
    std::string get_password(void) const;
    std::string get_message(void) const;
    int get_message_status(void) const;
    int get_channels_nb(void) const;
    IRC *get_server(void) const;
    std::string get_server_name(void) const;
    int get_socket(void) const;

    /* Getters preparsing */
    std::string get_unparsed_client_command(void) const;
    std::vector<std::string> get_params(void) const;
    std::string get_command_name(void) const;
    std::string get_prefix(void) const;
    unsigned int get_params_size(void) const;
    bool check_if_prefix(void) const;

    bool user_is_registered(void) const;
    bool user_registered_password(void) const;
    bool user_registered_nickname(void) const;
    bool user_is_away(void) const;
    bool user_is_operator(void) const;
    std::vector<std::string> user_commands(void) const;

    void set_nickname(std::string nickname);
    void set_username(std::string username);
    void set_realname(std::string realname);
    void set_hostname(std::string hostname);
    void set_modes(std::string modes);
    void set_operator_status(bool value);
    void set_is_away(bool value);
    void set_away_mssg(std::string message);
    void set_unparsed_client_command(std::string client_command);
    void set_password_as_registered(bool is_set);
    void set_registered_nickname(bool is_set);
    void set_registered_user(bool is_set);
    void set_operator(bool is_set);
    void set_message_status(int status);
    void set_init_socket(int socket);
    void set_socket(int socket);

    /* Pre parsing */
    int store_string_until_char(std::string *dest, std::string *src, char c, int len);
    void patch_params(std::vector<std::string> *params);
    void split_string_to_vector(std::vector<std::string> *vec, std::string *str, char c);
    bool hasEnding(std::string const &fullString, std::string const &ending);
    void store_prefix(void);
    void store_command(void);
    void store_params(void);

    void store_prefix(std::vector<t_cmd>::iterator it);
    void store_command(std::vector<t_cmd>::iterator it);
    void store_params(std::vector<t_cmd>::iterator it);

    /* Display */
    void displayClientInfo(void);
    void displayChannels(void);
    void display_command(void);
    void display_params(void);

    /* Channel */
    Channel *creates_channel(std::string channel_name);
    bool is_channel_user(Channel *channel);
    void be_added_to_channel(Channel *chan);
    void decrease_channel_nb();
    void increase_channel_nb();
    void add_channel_to_list(Channel *channel);
    void remove_channel_from_list(Channel *channel);
};

//Utils to display overloading <<
std::ostream &operator<<(std::ostream &COUT, User *user);