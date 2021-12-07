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
        std::vector<User *>     _operators;
        std::vector<User *>     _users;
       // std::vector<User *>   _banned_users;
       // std::vector<User *>   _invited_users;
       // std::vector<User *>   _voice_priv_users;
        User                    *_channel_owner;
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
        Channel(std::string name, User *user);
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
        //modifier user pour user ?
        bool                    user_is_banned(User *user);
        bool                    user_is_operator(User *user);
        bool                    user_is_member(User *user);
        bool                    user_is_invited(User *user);
        bool                    user_is_owner(User *user);
        //bool                  user_is_voice_priv(User *user);

        void                    removeFromOperators(User *user);

        void                    newMember(User *user);
        void                    deleteMember(User *user);
        void                    printMemberInfo(User *user);
        bool                    isNicknameUnique(User *user);
        //ajouter add banned
        //ajouter add invited
        //voir voice priv

        /* Info sur le channel */

        //devrait generer une erreur si aucun user n'est dans la liste ?
        bool                    channelHasUsers(void);
        bool                    channelHasOperator(void);
        bool                    channelHasBanned(void);

        /* Display / Debug */
        void                    displayChannelInfo(void);
        void                    displayMembers(void);
        void                    displayTopic(void);
        void                    displayOperators(void);
        void                    displayBanned(void);
};

//Utils to display - overloading 
std::ostream& operator<<(std::ostream COUT, Channel *channel);