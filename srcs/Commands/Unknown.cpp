/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Unknown.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 17:45:38 by bahaas            #+#    #+#             */
/*   Updated: 2021/12/02 18:04:11 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

void Commands::unknown_cmd(Client *client, Server *server)
{
    std::vector<std::string> reply_params;
    std::string              reply;

    reply_params.push_back(client->get_command_name());
    reply = build_reply(421, client, reply_params);
    send_reply(reply);
}