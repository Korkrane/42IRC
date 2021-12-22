#pragma once

#include <IRC.hpp>

class User;
class IRC;

class Channel
{
private:
    std::string _name;
    char _prefix;
    std::string _topic;
    bool _has_topic;
    std::string _modes;
    bool _handle_modes;
    //Attention c'est devenu un pointeur ce qui n etait pas le cas
    std::vector<User *> _operators;
    std::vector<User *> _users;
    User *_channel_owner;
    std::string _key;
    bool _has_key;
    unsigned int _members_nb;
    unsigned int _operators_nb;
    char _mode_sign;

    Channel(Channel const &src);
    Channel &operator=(Channel const &src);
    Channel();

public:
    Channel(std::string name, User *user);
    virtual ~Channel();

    void set_name(std::string name);
    void set_topic(std::string topic);
    void set_topic(User *user, IRC *server, std::vector<std::string> topic);
    void set_has_topic(void);
    void clear_topic(User *user, IRC *server, std::vector<std::string> topic);
    void set_modes(std::string modes);
    void unset_topic(void);
    void set_has_key(void);
    void set_key(std::string key);
    void unset_has_key();
    void drop_key();

    std::string get_name(void) const;
    std::string get_topic(void) const;
    bool get_has_topic(void) const;
    std::string get_modes(void) const;
    unsigned int get_members_nb(void) const;
    unsigned int get_operators_nb(void) const;
    std::vector<User *> get_members(void) const;
    std::vector<User *> get_operators(void) const;
    std::vector<int> get_members_fd(void);
    bool get_has_key(void);
    std::string get_key(void);

    bool user_is_operator(User *user);
    bool user_is_member(User *user);
    bool user_is_invited(User *user);
    bool user_is_owner(User *user);

    void removeFromOperators(User *user);
    void new_member(User *user, bool user_operator);
    void new_operator(User *user);
    void deleteMember(User *user);
    bool isNicknameUnique(User *user);

    bool channelHasUsers(void);
    bool channelHasOperator(void);

    void displayChannelInfo(void);
    void displayMembers(void);
    void displayTopic(void);
    void displayOperators(void);
    void displayBanned(void);
    void displayMode(void);

    void set_handle_modes(void);
    void set_channel_prefix(void);
    char get_channel_prefix(void) const;

    void set_handle_modes(bool handle);
    bool get_handle_modes(void);

    bool check_channel_modes(std::string target_modes);
    void set_channel_modes(std::string target_modes);

    bool has_key_mode_on(void);
    bool has_mode(char mode);
    bool is_correct_channel_key(std::string target_key);
    bool is_full_channel(void) const;

    std::string get_unknown_mode(std::string target_modes);

    void delete_operator(User *user);
    void delete_owner();
    void set_owner(User *user);
    User *get_owner(void);
    //void    addChannelOwner(User *user);
    bool is_channel_owner(User *user);
};

std::ostream &operator<<(std::ostream COUT, Channel *channel);
//TODO: A remettre en membre ?
bool is_correct_channel_name(std::string target_name);
