#pragma once

//#include <User.hpp>
#include <irc.hpp>

class User;

class Channel
{
    private:
        std::string             _name;
        std::string             _topic;
        std::string             _modes;
        std::vector<User *>   _operators;
        std::vector<User *>   _clients;
        std::vector<User *>   _banned_clients;
        std::vector<User *>   _invited_clients;
        std::vector<User *>   _voice_priv_clients;
        User                  *_channel_owner;
        //std::string           _key;
        //bool                  _has_key;
        unsigned int            _members_nb;
        bool                    _topic_set;

        /*
        ** Fonctions membres privees (classe canonique)
        */
        Channel(Channel const &src);
        Channel & operator=(Channel const &src);

    public:
        Channel(std::string name, User *client);
        virtual ~Channel();

        //Constructeur par defaut a mettre en prive ?
        Channel();

        /*** SETTERS ***/
        void                    set_name(std::string name);
        void                    set_topic(std::string topic);
        void                    set_modes(std::string modes);
        void                    unset_topic(void);

        /*** GETTERS ***/
        std::string             get_name(void) const;
        std::string             get_topic(void) const;
        std::string             get_modes(void) const;
        unsigned int            get_members_nb(void) const;
        std::vector<User *>   get_member_list(void) const;
        std::vector<User *>   get_operators(void) const;

        /*** UTILS ***/
        //modifier user pour client ?
        bool                    user_is_banned(User *client);
        bool                    user_is_operator(User *client);
        bool                    user_is_member(User *client);
        bool                    user_is_invited(User *client);
        bool                    user_is_owner(User *client);
        //bool                  user_is_voice_priv(User *client);

        void                    removeFromOperators(User *client);

        void                    newMember(User *client);
        void                    deleteMember(User *client);
        void                    printMemberInfo(User *client);
        bool                    isNicknameUnique(User *client);
        //ajouter add banned
        //ajouter add invited
        //voir voice priv

        /* Info sur le channel */

        //devrait generer une erreur si aucun client n'est dans la liste ?
        bool                    channelHasClients(void);
        bool                    channelHasOperator(void);
        bool                    channelHasBanned(void);

        /* Display / Debug */
        void                    displayChannelInfo(void);
        void                    displayMembers(void);
        void                    displayTopic(void);
        void                    displayOperators(void);
        void                    displayBanned(void);
};