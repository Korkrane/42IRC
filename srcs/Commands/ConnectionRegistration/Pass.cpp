#include <IRC.hpp>

void Commands::pass(User *user, IRC *server)
{
    #if DEBUG == 1
        std::cout << RED << "ENTER PASS CMD" << NC << std::endl;
    #endif
    if(user->user_is_registered() == true)
    {
        std::vector<std::string> rpl_params;
        server->send_rpl("462", user, rpl_params, "");
    }
    //TODO wrong pass at connection, what do we do ?
    #if DEBUG == 1
        std::cout << RED << "EXIT PASS CMD" << NC << std::endl;
    #endif
}