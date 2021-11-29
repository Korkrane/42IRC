/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_utils.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 12:11:56 by bahaas            #+#    #+#             */
/*   Updated: 2021/11/29 17:03:32 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/irc.hpp"

void send_reply(std::string reply)
{
    std::cout << BLUE << reply << NC;
}

void split_string_to_vector(std::vector<std::string> *vec, std::string *str, char c)
{
    size_t pos = str->find(c);
    size_t initialPos = 0;

    // Decompose each element
    while (pos != std::string::npos)
    {
        vec->push_back(str->substr(initialPos, pos - initialPos));
        initialPos = pos + 1;
        pos = str->find(c, initialPos);
    }
    // Add the last element
    vec->push_back(str->substr(initialPos, std::min(pos, str->size()) - initialPos + 1));
}

void printClientCommand(t_cmd *cmd)
{
    std::cout << "prefix=" << cmd->prefix << std::endl;
    std::cout << "cmd=" << cmd->cmd << std::endl;
    std::vector<std::string>::iterator itr = cmd->params.begin();
    int i = 0;
    for (itr; itr != cmd->params.end(); itr++)
    {
        std::cout << "param(" << i << ")=" << *itr << std::endl;
        i++;
    }
}