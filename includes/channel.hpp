#ifndef CHANNEL_HPP
# define CHANNEL_HPP

#pragma once

#include "client.hpp"
class Client;

class Channel
{
    private:
        std::string             _name;
        std::string             _topic;
        std::string             _modes;
        std::vector<Client *>   _operators;
        std::vector<Client *>   _clients;
        std::vector<Client *>   _banned_clients;
        std::vector<Client *>   _invited_clients;
        std::vector<Client *>   _voice_priv_clients;
        Client                  *_channel_owner;
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
        Channel(std::string name, Client *client);
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
        std::vector<Client *>   get_member_list(void) const;
        std::vector<Client *>   get_operators(void) const;

        /*** UTILS ***/
        //modifier user pour client ?
        bool                    user_is_banned(Client *client);
        bool                    user_is_operator(Client *client);
        bool                    user_is_member(Client *client);
        bool                    user_is_invited(Client *client);
        bool                    user_is_owner(Client *client);
        //bool                  user_is_voice_priv(Client *client);

        void                    removeFromOperators(Client *client);

        void                    newMember(Client *client);
        void                    deleteMember(Client *client);
        void                    printMemberInfo(Client *client);
        bool                    isNicknameUnique(Client *client);
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

#endif