#include <IRC.hpp>

void            Commands::pass(User *user, IRC *server)
{
    (void)user;
    (void)server;
    #if DEBUG
        std::cout << BLUE << "DEBUG: " << "PASS" << std::endl;
    #endif
    return ;

}