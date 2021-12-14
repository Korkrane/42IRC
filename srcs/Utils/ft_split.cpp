#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <IRC.hpp>

//TODO: a mettre sur user
void    User::ft_split_channels(std::string line, char charset)
{
    std::string              buffer;
    size_t                   i = 0;
    size_t                   pos = 0;
    size_t                   len = line.length();

    if (line.empty())
    {
        #if DEBUG
            std::cout << BLUE << "ERROR: line is empty" << NC << std::endl;
        #endif
        return ;
    }
        
    //On va lire la string a splitter
    while (pos < len)
    {
        pos = i;
        i = line.find(charset, pos);
        //Si on trouve quelque chose (\0) inclu
        if (pos != i)
        {
            //SI on est arrive au \0
            if (i == std::string::npos)
            {
                std::cout << "line is " << line << std::endl;
                this->_splitted_channels.push_back(line);
                return ;
            }
            //TODO: a revoir (cas ou on trouve au moins une fois le char recherche)
        }
    }
    return ;
}

void    User::ft_split_args(std::string line, char charset)
{
    std::string              buffer;
    size_t                   i = 0;
    size_t                   pos = 0;
    size_t                   len = line.length();

    if (line.empty())
        return ;
    //On va lire la string a splitter
    while (pos < len)
    {
        pos = i;
        i = line.find(charset, pos);
        //Si on trouve quelque chose (\0) inclu
        if (pos != i)
        {
            //SI on est arrive au \0
            if (i == std::string::npos)
            {
                std::cout << "line is " << line << std::endl;
                this->_splitted_args.push_back(line);
                return ;
            }
            //TODO: a revoir (cas ou on trouve au moins une fois le char recherche)
        }
    }
    return ;
}

std::vector<std::string>    ft_split(std::string line, std::string charset)
{
    (void)line;
    (void)charset;

    std::vector<std::string> splitted;
    std::string              buffer;
    size_t                   i = 0;
    size_t                   pos = 0;
    size_t                   len = line.length();

    if (!line.empty())
        return (splitted);

    //Si le charset est null
    if (charset.empty())
    {
#if DEBUG
    std::cout << BLUE << "DEBUG: " << "ft_split called but charset is null" << NC << std::endl;
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
