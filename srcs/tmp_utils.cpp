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
    int i = 0;
    for (std::vector<std::string>::iterator itr = cmd->params.begin(); itr != cmd->params.end(); itr++)
    {
        std::cout << "param(" << i << ")=" << *itr << std::endl;
        i++;
    }
}