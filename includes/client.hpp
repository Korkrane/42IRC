#include "irc.hpp"
#include <vector>

#pragma once

class Channels;

class Commands;

/**
 * @brief
 */
class Client
{
    private:

        /*
        ** Fonctions membres de la classe canonique
        */
       Client(Client const &src);
       Client & operator=(Client const &src);

        std::string                 _nickname;
        std::string                 _username;
        std::string                 _hostname;
        std::string                 _realname;
        std::string                 _modes;
        bool                        _has_operator_status;
        bool                        _is_away;
        std::string                 _away_mssg;
        std::string                 _password;
        //std::vector<Channels *>  _channels;
        //Pas sure - utilisation pour select
        int                         _fd;
        int                         _message_status;
        std::string                 _message;

        /*
        ** Information relative au server
        ** comprendre dans quel cadre c'est utilisé
        */
        std::string                 _server_name;
        std::string                 _server_ip;
        std::string                 _server_creation;

        /* Liste des channels auxquelles l'user est membre */
        std::vector<Channel *>      _channels;
        //int                     _socket;
        //vector contenant toutes les commandes faites par l'user
        std::vector<std::string>    _commands;
        //bool  _registration_status
        std::string                 _port;
        bool                        _user_is_oper;
        bool                        _user_is_away;
        bool                        _user_has_registered_pass;
        bool                        _user_has_registered_nick;
        bool                        _user_is_registered;//?
        //std::vector<std::string>  _cap;
        //std::vector<std::string>  _nick;
        //std::vector<std::string>  _user;

    public:
        //Voir si mettre le constructeur par defaut en prive
        /*
        ** Fonctions membres classe canonique
        */

        //voir si constructeur par defaut a mettre en prive
        Client(void);
        Client(std::string server_name, std::string server_ip, std::string server_creation, std::string port);
        virtual ~Client();

        /*** GETTERS ***/
        std::string                 get_nickname(void) const;
        std::string                 get_username(void) const;
        std::string                 get_realname(void) const;
        std::string                 get_hostname(void) const;
        std::string                 get_modes(void) const;
        bool                        get_operator_status(void) const;
        bool                        get_is_away(void) const;
        std::string                 get_away_mssg(void) const;

        /*
        ** Added getters
        */
        std::string                 get_password(void) const;
        std::string                 get_server_port(void) const;
        std::string                 get_message(void) const;
        int                         get_message_status(void) const;
        int                         get_socket(void) const;
        int                         get_channels(void) const;
        bool                        get_away_message(void) const;

        /*
        ** Utils
        */
        bool                        user_is_registered(void) const;
        bool                        user_registered_password(void) const;
        bool                        user_registered_nickname(void) const;
        bool                        user_is_away(void) const;
        bool                        user_is_operator(void) const;
        std::vector<std::string>    user_commands(void) const;

        /*
        ** Utils relatifs au server
        */
        bool                        get_server_name(void) const;
        bool                        get_server_ip(void) const;
        bool                        get_server_creation(void) const;

        /*** SETTERS ***/
        void                        set_nickname(std::string nickname);
        void                        set_username(std::string username);
        void                        set_realname(std::string realname);
        void                        set_hostname(std::string hostname);
        void                        set_modes(std::string modes);
        void                        set_operator_status(bool value);
        void                        set_is_away(bool value);
        void                        set_away_mssg(std::string message);

        /*
        ** Added
        */
        void                        set_password_as_registered(bool is_set);
        void                        set_registered_nickname(bool is_set);
        void                        set_registered_user(bool is_set);
        void                        set_operators(bool is_set);
        int                         set_message_status(int status);
        void                        set_registration(bool is_set);
        void                        set_init_socket(int socket);

        void                        set_server_name(std::string server_name);
        void                        set_server_ip(std::string server_ip);
        void                        set_server_creation(std::string server_creation);

        /*
        ** Other utils
        */
       void                         clear_client_message(void);
       void                         clear_client_command(void);
       void                         send_message_to_server(void);
       //void                         check_message(void);
       //void                         join_channel(Channel *channel);
       //void                         quit_channel(Channel *channel);
       //void                           quit_all_channels(void);

        /*
        ** Display and debug
        */
       void                         displayClientInfo(void);
};