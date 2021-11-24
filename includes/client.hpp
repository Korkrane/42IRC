/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 11:56:11 by bahaas            #+#    #+#             */
/*   Updated: 2021/11/24 14:24:28 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

class Client
{
    private:
        std::string _nickname;
        std::string _username;
        std::string _hostname;
        std::string _realname;
        std::string _modes;
        bool        _has_operator_status;

        bool        _is_away;
        std::string _away_mssg;

    public:
        Client(){};
        ~Client(){};

        /*** SETTERS ***/
        void set_nickname(std::string nickname)
        {
            this->_nickname = nickname;
        }
        void set_username(std::string username)
        {
            this->_username = username;
        }
        void set_realname(std::string realname)
        {
            this->_realname = realname;
        }
        void set_hostname(std::string hostname)
        {
            this->_hostname = hostname;
        }
        void set_modes(std::string modes)
        {
            this->_modes = modes;
        }
        void set_operator_status(bool value)
        {
            this->_has_operator_status = value;
        }
        void set_is_away(bool value)
        {
            this->_is_away = value;
        }
        void set_away_mssg(std::string message)
        {
            this->_away_mssg = message;
        }

        /*** GETTERS ***/
        std::string get_nickname()
        {
            return this->_nickname;
        }
        std::string get_username()
        {
            return this->_username;
        }
        std::string get_realname()
        {
            return this->_realname;
        }
        std::string get_hostname()
        {
            return this->_hostname;
        }
        std::string get_modes()
        {
            return this->_modes;
        }
        bool get_operator_status()
        {
            return this->_has_operator_status;
        }
        bool get_is_away()
        {
            return this->_is_away;
        }
        std::string get_away_mssg()
        {
            return this->_away_mssg;
        }
};