//#include <irc.hpp>
//#include "../../includes/irc.hpp"

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

/**
 * @brief 
 * 
 * @param str 
 * @param charset 
 * @return int 
 */
int                         ft_len(std::string str, std::string charset)
{
    (void)str;
    (void)charset;
    int len = 0;
    return (len);
}

/**
 * @brief : version C++ de split
 * 
 * @param line 
 * @param charset 
 * TODO: A tester
 */
std::vector<std::string>    ft_split(std::string line, std::string charset)
{
    (void)line;
    (void)charset;

    std::vector<std::string> splitted;
    std::string              buffer;
    size_t                   i = 0;
    size_t                   pos = 0;
    size_t                   len = line.length();

    //Si le charset est null
    if (charset.empty())
    {
#if DEBUG
    std::cout << BLUE << "DEBUG: " << "ft_split called but charset is null" << std::endl;
#endif
        splitted.push_back(line);
        return (splitted);
    }
    //On va lire la string a splitter
    while (i < len)
    {
        pos = i;
        i = line.find(charset, pos);
        //Si on trouve quelque chose (\0) inclu
        if (pos != i)
        {
            //SI on est arrive au \0
            if (i == std::string::npos)
            {
                #if DEBUG
                    std::cout << BLUE << "DEBUG: " << "0. Splitting adding " << line.substr(pos) << std::endl;
                #endif
                splitted.push_back(line.substr(pos));
                return (splitted);
            }
            else
            {
                #if DEBUG
                    std::cout << BLUE << "DEBUG: " << "1. Splitting adding " << line.substr(pos) << std::endl;
                #endif
                splitted.push_back(line.substr(pos)); 
                splitted.back().resize(i - pos);
            }
        }
        i += charset.length();
    }
    return (splitted);
}

/*
int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    std::string test = "coucou je teste des trucs !";
    std::vector<std::string> splitted = ft_split(test, " ");
    std::vector<std::string>::iterator it = splitted.begin();
    std::vector<std::string>::iterator ite = splitted.end();
    int i = 0;
    while (it != ite)
    {
        std::cout << i << " " << (*it) << std::endl;
        it++;
        i++;
    }
    return (0);
}
*/