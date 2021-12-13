#include <IRC.hpp>

void Commands::pass(User *user, IRC *server)
{
    (void)user;
    (void)server;
#if DEBUG
    std::cout << RED << "ENTER PASS CMD" << NC << std::endl;
    std::cout << RED << "EXIT PASS CMD" << NC << std::endl;
#endif
    return;
}