/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   users.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 17:43:31 by bahaas            #+#    #+#             */
/*   Updated: 2021/11/29 18:24:15 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

/**
 * @brief disabled due to security implications, only send an error reply
 * https://datatracker.ietf.org/doc/html/rfc2812#section-4.6
 * @param cmd
 * @param client
 * @param server
 */
void usersCmd(t_cmd *cmd, Client *client, Server *server) // 446 reply
{
    std::vector<std::string> reply_params;
    std::string reply;

    reply = build_reply(446, client, reply_params);
    send_reply(reply);
}