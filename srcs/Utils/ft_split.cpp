#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <IRC.hpp>

//TODO: a mettre sur user
void    User::ft_split_channels(std::string line, char charset)
{
    (void)line;
    (void)charset;

    std::string              buffer;
    size_t                   i = 0;
    size_t                   pos = 0;
    size_t                   len = line.length();

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
                this->_splitted_channels.push_back(line);
                #if DEBUG
                    //std::cout << PURPLE << "Displaying result split: " << std::endl;
                    //display_vector_string(this->_splitted_channels);
                #endif
            }
            //TODO: a revoir (cas ou on trouve au moins une fois le char recherche)
            /*
            else
            {
                splitted.push_back(line.substr(i));
                //splitted.back().resize(i - pos);
            }
            */
        }
        //i++;
    }
    #if DEBUG
        //std::cout << PURPLE << "Displaying result split: " << std::endl;
        //display_vector_string(*splitted);
    #endif
    return ;
}

void    User::ft_split_args(std::string line, char charset)
{
    (void)line;
    (void)charset;

    std::string              buffer;
    size_t                   i = 0;
    size_t                   pos = 0;
    size_t                   len = line.length();

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
                this->_splitted_args.push_back(line);
                #if DEBUG
                    std::cout << PURPLE << "Displaying result split: " << std::endl;
                    display_vector_string(this->_splitted_channels);
                #endif
            }
            //TODO: a revoir (cas ou on trouve au moins une fois le char recherche)
            /*
            else
            {
                splitted.push_back(line.substr(i));
                //splitted.back().resize(i - pos);
            }
            */
        }
        //i++;
    }
    #if DEBUG
        //std::cout << PURPLE << "Displaying result split: " << std::endl;
        //display_vector_string(*splitted);
    #endif
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
