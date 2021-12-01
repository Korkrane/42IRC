#include "../includes/irc.hpp"

/**
 * @brief Stock a substring from src into dest until the first occurence of c is met in src
 * Returning the length parsed to find it.
 *
 * @param dest
 * @param src
 * @param c
 * @param len
 * @return int
 */
int storeStringUntilChar(std::string *dest, std::string *src, char c, int len)
{
    for (std::string::iterator it = src->begin(); it != src->end(); ++it)
    {
        if (*it == c)
        {
            *dest = src->substr(0, len);
            len++;
            break;
        }
        len++;
    }
    return (len);
}

void storePrefix(t_cmd *cmd, std::string *query)
{
    std::string::iterator it = query->begin();

    int i = 0;
    if (*it == ':')
        i = storeStringUntilChar(&cmd->prefix, query, ' ', i);
    query->replace(0, i, "");
}

void storeCommand(t_cmd *cmd, std::string *query)
{
    int i = 0;
    i = storeStringUntilChar(&cmd->cmd, query, ' ', i);
    query->replace(0, i, "");
}

/**
 * @brief Correct the way parameters are stored. with the case ":this is a single param in fact"
 * append all these in a single one and erase the old ones.
 * @param params
 */
void patch_params(std::vector<std::string> *params)
{
    int elem_to_erase = 0;
    for (std::vector<std::string>::iterator it = params->begin(); it != params->end(); it++)
    {
        if ((*it)[0] == ':')
        {
            for (std::vector<std::string>::iterator it2 = it + 1; it2 != params->end(); it2++)
            {
                (*it).append(" " + *it2);
                elem_to_erase++;
            }
            break;
        }
    }

    std::vector<std::string>::iterator ite = params->end();
    for (int erase = elem_to_erase; erase != 0; --erase)
        params->erase(ite);
}

void storeParams(t_cmd *cmd, std::string *query)
{
    split_string_to_vector(&cmd->params, query, ' ');
    patch_params(&cmd->params);
}

/*
int main(int ac, char **av)
{
    //    Server server;
    //    Client *my_test_client = new Client();
    t_cmd client_command;

    std::string str = std::string(av[1]);
    storePrefix(&client_command, &str);
    storeCommand(&client_command, &str);
    storeParams(&client_command, &str);

    if (str.size() + 2 > 512)
        throw TooLongCommandFromClient();
    if (client_command.params.size() > 15)
        throw TooMuchParamsFromClient();
    printClientCommand(&client_command);
}
*/