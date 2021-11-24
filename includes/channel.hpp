/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 12:06:37 by bahaas            #+#    #+#             */
/*   Updated: 2021/11/24 13:58:27 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

class Client;

class Channel
{
    private:
        std::string         _name;
        std::string         _topic;
        std::string         _modes;
        std::list<Client *> _operators;
        std::list<Client *> _clients;
        std::list<Client *> _banned_clients;
        std::list<Client *> _invited_clients;
        std::list<Client *> _voice_priv_clients;
        Client             *_channel_owner;

    public:
        Channel();
        ~Channel();

        /*** SETTERS ***/
        void set_name(std::string name)
        {
            this->_name = name;
        }
        void set_topic(std::string topic)
        {
            this->_topic = topic;
        }
        void set_modes(std::string modes)
        {
            this->_modes = modes;
        }

        /*** GETTERS ***/
        std::string get_name()
        {
            return this->_name;
        }
        std::string get_topic()
        {
            return this->_topic;
        }
        std::string get_modes()
        {
            return this->_modes;
        }
};