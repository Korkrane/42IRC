/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 16:37:06 by bahaas            #+#    #+#             */
/*   Updated: 2021/11/25 17:55:35 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include "irc.hpp"

// every function pointer will be stored as this type
// typedef void (*cmdFunction)(t_cmd *cmd, Client *client);

struct t_cmd;
void timeCmd(t_cmd *cmd, Client *client);

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

        std::map<std::string, void (*)(t_cmd *, Client *)> _cmdsFunction;

        Server()
        {
            _cmdsFunction = _initCmds();
        }

        ~Server(){};

        /**
         * @brief map cmd params to it's ptr function
         *
         * @return std::map<std::string, void (*)(t_cmd *, Client *)>
         */
        std::map<std::string, void (*)(t_cmd *, Client *)> _initCmds()
        {
            std::map<std::string, void (*)(t_cmd *, Client *)> cmds;
            cmds["TIME"] = timeCmd; // insert a new value
            return cmds;
        }
};

#endif // !SERVER_HPP