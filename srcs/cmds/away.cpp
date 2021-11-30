/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   away.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahautlatinis <mahautlatinis@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 13:53:00 by bahaas            #+#    #+#             */
/*   Updated: 2021/11/30 14:41:21 by mahautlatin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

/**
 * @brief
 *
 * @param cmd
 * @param client
 */
void awayCmd(t_cmd *cmd, Client *client, Server *server) // 305 & 306 reply
{
    std::vector<std::string> reply_params;
    std::string              reply;

    if (client->get_is_away() && cmd->params[0].empty()) // s'il est deja afk mais pas de param on le marque non afk
    {
        client->set_is_away(false);
        client->set_away_mssg("");
        reply = build_reply(305, client, reply_params);
    }
    else if (client->get_is_away() && !cmd->params[0].empty()) // s'il est deja afk est change son mssg d'away
    {
        client->set_is_away(false);
        client->set_away_mssg(cmd->params[0]);
        reply = build_reply(306, client, reply_params);
#if DEBUG
        std::cout << "DEBUG: "
                  << "set away with away_mssg:" << client->get_away_mssg() << std::endl;
#endif
    }
    else if (!client->get_is_away() && !cmd->params[0].empty()) // pas encore afk et avec un mssg
    {
        client->set_is_away(true);
        client->set_away_mssg(cmd->params[0]);
        reply = build_reply(306, client, reply_params);
#if DEBUG
        std::cout << "DEBUG: "
                  << "set away with away_mssg:" << client->get_away_mssg() << std::endl;
#endif
    }
    else if (!client->get_is_away() && cmd->params[0].empty()) // pas encore afk sans mssg
    {
        client->set_is_away(true);
        client->set_away_mssg("I'm away (default message)");
        reply = build_reply(306, client, reply_params);
#if DEBUG
        std::cout << "DEBUG: "
                  << "set away with away_mssg:" << client->get_away_mssg() << std::endl;
#endif
    }
    send_reply(reply);
}
