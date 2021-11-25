/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   away.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 13:53:00 by bahaas            #+#    #+#             */
/*   Updated: 2021/11/25 14:01:08 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"

struct t_cmd
{

        std::string              prefix;
        std::string              cmd;
        std::vector<std::string> params;
};

void away(t_cmd *cmd)
{
}

int main(int ac, char **av)
{
    Server *server;
    t_cmd  *client_command;

    away(client_command);
}