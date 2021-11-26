/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   version.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 13:46:34 by bahaas            #+#    #+#             */
/*   Updated: 2021/11/26 14:28:37 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

void versionCmd(t_cmd *cmd, Client *client, Server *server) // 351 & 402 reply
{
    std::vector<std::string> reply_params;
    std::string              reply;

    if (cmd->params[0].empty() || (cmd->params[0] == server->get_name())) // si pas de server precise donné l'actuel
    {
        // TODO check for degublevel & comments (hardcoded atm)
        reply_params.push_back(server->get_version());
        reply_params.push_back("debuglevel00");
        reply_params.push_back(server->get_name());
        reply_params.push_back("random comments as test");
        reply = build_reply(351, client, reply_params);
    }
    else if (!cmd->params[0].empty() && cmd->params[0] != server->get_name())
    {
        reply_params.push_back(cmd->params[0]);
        reply = build_reply(402, client, reply_params);
    }
    send_reply(reply);
}