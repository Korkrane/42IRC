#include <IRC.hpp>

void Commands::send_quit_message(User *user, IRC *server, std::string message)
{
    (void)message;
    std::vector<std::string> reply_params;
    std::string reply;
    reply = build_reply(998, user, reply_params);
    server->_response_queue.push_back(std::make_pair(user->get_socket(), reply));
    reply_params.clear();
    user->_to_delete = true;
}

void Commands::quit_cmd(User *user, IRC *server)
{
#if DEBUG
    std::cout << RED << "ENTER QUIT CMD" << std::endl;
#endif
    /*
#if DEBUG
    int i = 0;
    for (std::vector<std::string>::iterator itr = params.begin(); itr != params.end(); itr++)
    {
        std::cout << YELLOW << "param(" << i << ")= " << *itr << NC << std::endl;
        i++;
    }
#endif
*/
    std::string message;
    send_quit_message(user, server, message);
#if DEBUG
    std::cout << RED << "EXIT QUIT CMD" << std::endl;
#endif
}