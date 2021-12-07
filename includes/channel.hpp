#pragma once

//#include <User.hpp>
#include <irc.hpp>

class User;

class Channel
{
    private:
        std::string             _name;
        char                    _prefix;
        std::string             _topic;
        bool                    _has_topic;
        std::string             _modes;
        bool                    _handle_modes;
        std::vector<User *>     _operators;
        std::vector<User *>     _users;
        User                    *_channel_owner;
        std::string             _key;
        bool                    _has_key;
        unsigned int            _members_nb;
        unsigned int            _operators_nb;

        /*
        ** Fonctions membres privees (classe canonique)
        */
        Channel(Channel const &src);
        Channel & operator=(Channel const &src);
        Channel();

    public:
        Channel(std::string name, User *user);
        virtual ~Channel();

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
        std::vector<User *>     get_member_list(void) const;
        std::vector<User *>     get_operators(void) const;

        /*** UTILS ***/
        bool                    user_is_operator(User *user);
        bool                    user_is_member(User *user);
        bool                    user_is_invited(User *user);
        bool                    user_is_owner(User *user);

        void                    removeFromOperators(User *user);

        void                    newMember(User *user, bool user_operator);
        void                    newOperator(User *user);
        void                    deleteMember(User *user);
        void                    printMemberInfo(User *user);
        bool                    isNicknameUnique(User *user);

        /* Info sur le channel */
        //devrait generer une erreur si aucun user n'est dans la liste ?
        bool                    channelHasUsers(void);
        bool                    channelHasOperator(void);
        //bool                    channelHasBanned(void);

        /* Display / Debug */
        void                    displayChannelInfo(void);
        void                    displayMembers(void);
        void                    displayTopic(void);
        void                    displayOperators(void);
        void                    displayBanned(void);
        
        

        //Ajouter une fonction qui permet d'ajouter un mode
        //Ajouter une fonction qui permet d'enlever un mode 

        void                    set_handle_modes(void);
        void                    set_channel_prefix(void);
        char                    get_channel_prefix(void) const;

        void                    set_handle_modes(bool handle);
        bool                    get_handle_modes(void);

        bool                    check_channel_modes(std::string target_modes);
        void                    set_channel_modes(std::string target_modes);

        bool                    has_key_mode_on(void);
        bool                    has_mode(char mode);
        bool                    is_correct_channel_key(std::string target_key);
        bool                    is_full_channel(void) const;
};

//Utils to display - overloading 
std::ostream& operator<<(std::ostream COUT, Channel *channel);
bool          is_correct_channel_name(std::string target_name);
