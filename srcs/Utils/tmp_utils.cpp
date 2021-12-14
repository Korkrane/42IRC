#include <IRC.hpp>

//TODO: A supprimer ?
void send_reply(std::string reply)
{
    std::cout << BLUE << reply << NC << std::endl;
}

void    display_vector_string(std::vector<std::string> vector)
{
    if (vector.size() == 0)
    {
        std::cout << GREEN << "Oops, vector is empty !" << std::endl;
        return ;
    }
    std::vector<std::string>::iterator it = vector.begin();
    std::vector<std::string>::iterator ite = vector.end();

    while (it != ite)
    {
        std::cout << PURPLE << (*it) << std::endl;
        it++;
    }
    return ;
}