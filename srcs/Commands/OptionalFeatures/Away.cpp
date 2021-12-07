#include <irc.hpp>

//TODO: A remettre a jour avec la nouvelle version de client
void Commands::away_cmd(User *client, IRC *server) // 305 & 306 reply
{
    (void)client;
    (void)server;
    /*
    std::vector<std::string> reply_params;
    std::string              reply;

    if (client->get_is_away() && client->get_params()[0].empty()) // s'il est deja afk mais pas de param on le marque non afk
    {
        client->set_is_away(false);
        client->set_away_mssg("");
        reply = build_reply(305, client, reply_params);
    }
    else if (client->get_is_away() && !client->get_params()[0].empty()) // s'il est deja afk est change son mssg d'away
    {
        client->set_is_away(false);
        client->set_away_mssg(client->get_params()[0]);
        reply = build_reply(306, client, reply_params);
#if DEBUG
        std::cout << "DEBUG: "
                  << "set away with away_mssg:" << client->get_away_mssg() << std::endl;
#endif
    }
    else if (!client->get_is_away() && !client->get_params()[0].empty()) // pas encore afk et avec un mssg
    {
        client->set_is_away(true);
        client->set_away_mssg(client->get_params()[0]);
        reply = build_reply(306, client, reply_params);
#if DEBUG
        std::cout << "DEBUG: "
                  << "set away with away_mssg:" << client->get_away_mssg() << std::endl;
#endif
    }
    else if (!client->get_is_away() && client->get_params()[0].empty()) // pas encore afk sans mssg
    {
        client->set_is_away(true);
        client->set_away_mssg("I'm away (default message)");
        reply = build_reply(306, client, reply_params);
#if DEBUG
        std::cout << "DEBUG: "
                  << "set away with away_mssg:" << client->get_away_mssg() << std::endl;
#endif
    }
    send_reply(reply);
    */
}