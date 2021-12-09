#include <IRC.hpp>

void Commands::user_cmd(User *user, IRC *server)
{
    std::string reply;
    std::vector<std::string> reply_params;

    #if DEBUG
        std::cout << RED << "ENTER ENTER USER CMD" << NC << std::endl;
    #endif

    if(user->user_is_registered() == true)
    {
        #if DEBUG
            std::cout << RED << "DEBUG: USER ALREADY REGISTERED " << NC << std::endl;
        #endif
        reply = build_reply(462, user, reply_params);
        server->_response_queue.push_back(std::make_pair(user->get_socket(), reply));
        return ;
    }
    else if(user->get_params_size() < 4)
    {
        #if DEBUG
            std::cout << RED << "DEBUG: NOT ENOUGH PARAMS IN USER COMMAND" << NC << std::endl;
        #endif
        reply_params.push_back(user->get_command_name());
        reply = build_reply(461, user, reply_params);
        server->_response_queue.push_back(std::make_pair(user->get_socket(), reply));
        return ;
    }
    else
    {
        #if DEBUG
            std::cout << YELLOW << "DEBUG: SUCCESS USER COMMAND" << NC << std::endl;
        #endif
        user->set_username(user->get_params()[0]);
        user->set_hostname(user->get_params()[2]);
        user->set_realname(user->get_params()[3]);
        user->set_registered_user(true);
    }
    #if DEBUG
        std::cout << RED << "EXIT USER CMD " << NC << std::endl;
    #endif
}
