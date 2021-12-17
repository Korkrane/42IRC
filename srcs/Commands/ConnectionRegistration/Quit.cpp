#include <IRC.hpp>

void Commands::quit_cmd(User *user, IRC *server)
{
#if DEBUG == 1
    std::cout << RED << "ENTER QUIT CMD" << std::endl;
#endif
    std::vector<std::string> params;

    server->send_rpl("998", user, params, "");
    user->_to_delete = true;
#if DEBUG == 1
    std::cout << RED << "EXIT QUIT CMD" << std::endl;
#endif
}