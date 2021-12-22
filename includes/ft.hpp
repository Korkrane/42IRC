#ifndef FT_HPP
#define FT_HPP

#include "IRC.hpp"

namespace ft
{
    inline std::vector<std::string> old_ft_split(std::string line, std::string charset)
    {
        std::vector<std::string> splitted;
        std::string buffer;
        size_t i = 0;
        size_t pos = 0;
        size_t len = line.length();

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
    };

    inline void split_string_to_vector(std::vector<std::string> *vec, std::string *str, char c)
    {
        size_t pos = str->find(c);
        size_t init_pos = 0;

        while (pos != std::string::npos)
        {
            vec->push_back(str->substr(init_pos, pos - init_pos));
            init_pos = pos + 1;
            pos = str->find(c, init_pos);
        }
        vec->push_back(str->substr(init_pos, std::min(pos, str->size()) - init_pos + 1));
    };

    inline bool string_end_with(std::string const &fullString, std::string const &ending)
    {
        if (fullString.length() >= ending.length())
            return (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
        else
            return false;
    };

    template <typename T>
    inline std::string to_string(T val)
    {
        std::stringstream stream;
        stream << val;
        return stream.str();
    }

    inline void display_vector_string(std::vector<std::string> vector)
    {
        if (vector.size() > 0)
        {
            for (std::vector<std::string>::iterator it = vector.begin(); it != vector.end(); it++)
                std::cout << (*it) << std::endl;
            return;
        }
        std::cout << "Vector is empty." << std::endl;
    };
} // namespace ft

#endif