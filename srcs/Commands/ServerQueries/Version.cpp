#include <IRC.hpp>

void Commands::version_cmd(User *user, IRC *server) // 351 & 402 reply
{
    (void)user;
    (void)server;
    std::vector<std::string> reply_params;
    std::string              reply;


    if (user->get_params().empty() || (user->get_params()[0] == server->get_name())) // si pas de server precise donné l'actuel
    {
        // TODO check for degublevel & comments (hardcoded atm)
        reply_params.push_back(server->get_version());
        reply_params.push_back("debuglevel00");
        reply_params.push_back(server->get_name());
        reply_params.push_back("random comments as test");
        reply = build_reply(351, user, reply_params);
        server->_response_queue.push_back(std::make_pair(user->get_socket(), reply));
        reply_params.clear();
    }
    else if (!user->get_params().empty() && user->get_params()[0] != server->get_name())
    {
        reply_params.push_back(user->get_params()[0]);
        reply = build_reply(402, user, reply_params);
        server->_response_queue.push_back(std::make_pair(user->get_socket(), reply));
        reply_params.clear();
    }
}