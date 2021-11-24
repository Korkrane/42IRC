/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 16:37:06 by bahaas            #+#    #+#             */
/*   Updated: 2021/11/24 18:19:36 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include "irc.hpp"

class Server
{
    private:
    public:
        int         _socket;
        int         _port;
        int         _totChannels;
        int         _totClients;
        std::string _password;
        std::string _version;
        std::string _userModes;
        std::string _channelModes;

        time_t      _init_time; // FIXME time_t over std::string _str_time
        std::string _str_date;  // FIXME one has to be deleted

        Server(){};
        ~Server(){};
};

#endif // !SERVER_HPP