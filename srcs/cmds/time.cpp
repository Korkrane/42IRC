/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 14:03:47 by bahaas            #+#    #+#             */
/*   Updated: 2021/11/26 14:01:53 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

/**
 * @brief query the local time from the specified server
 *
 * @param cmd
 * @param client
 */
void timeCmd(t_cmd *cmd, Client *client, Server *server)
{
    std::vector<std::string> reply_params;
    std::string              reply;

    time_t      now  = time(0);
    std::string date = ctime(&now);

    reply_params.push_back(cmd->params[0]);
    reply_params.push_back(date);
    reply = build_reply(391, client, reply_params);
    send_reply(reply);
}