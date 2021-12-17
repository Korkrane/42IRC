#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <IRC.hpp>

//TODO: a mettre sur user (fichier)
void    User::ft_split_channels(std::string l, char charset)
{
    if (l.empty())
    {
        return ;
    }
    std::string tmp;
    std::istringstream line(l);
    //On va lire la string a splitter
    while (std::getline(line, tmp, charset))
    {
        this->_splitted_channels.push_back(tmp);
        tmp.clear();
        /*
        i = line.find(charset, i);
        //Si on trouve quelque chose (\0) inclu
        if (i == std::string::npos)
        {
            //std::cout << "line is " << line << std::endl;
            this->_splitted_channels.push_back(line);
            return ;
        }
        else
        {
            tmp = line.substr(i + 1);
            std::cout << GREEN << "tmp splitted is " << tmp << std::endl;
            this->_splitted_channels.push_back(tmp);
            tmp.clear();
        }
        //TODO: a revoir (cas ou on trouve au moins une fois le char recherche)
        */
    }
    return ;
}

void    User::ft_split_args(std::string l, char charset)
{
   if (l.empty())
        return ;

    std::string tmp;
    std::istringstream line(l);
    //On va lire la string a splitter
    while (std::getline(line, tmp, charset))
    {
        this->_splitted_args.push_back(tmp);
        tmp.clear();
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
                splitted.push_back(line.substr(pos));
                return (splitted);
            }
            else
            {
                splitted.push_back(line.substr(pos));
                splitted.back().resize(i - pos);
            }
        }
        i += charset.length();
    }
    return (splitted);
}

std::vector<std::string>    old_ft_split(std::string line, std::string charset)
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
                splitted.push_back(line.substr(pos));
                return (splitted);
            }
            else
            {
                splitted.push_back(line.substr(pos));
                splitted.back().resize(i - pos);
            }
        }
        i += charset.length();
    }
    return (splitted);
}