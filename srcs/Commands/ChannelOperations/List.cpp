#include <IRC.hpp>

//duplicate in build_replies.cpp
template <typename T>
std::string test_string(T val)
{
    std::stringstream stream;
    stream << val;
    return stream.str();
}

void Commands::list(User *user, IRC *server)
{
    std::vector<std::string> params = user->get_params();
    std::vector<std::string> reply_params;
    if (params.size() == 0 || (params.size() == 1 && params[0] == ""))
    {
        std::cout << BLUE << "DEBUG: has 0 params in list" << NC << std::endl;
        server->send_rpl("321", user, reply_params, "");
        std::vector<Channel *> chans = server->get_channels();
        for (std::vector<Channel *>::iterator it = chans.begin(); it != chans.end(); it++)
        {
            std::string nb = test_string((*it)->get_members_nb());

            reply_params.push_back((*it)->get_name());
            reply_params.push_back(nb);
            reply_params.push_back((*it)->get_topic());
            //std::cout << "topic:" << (*it)->get_topic() << std::endl;
            server->send_rpl("322", user, reply_params, "");
            reply_params.clear();
        }
        server->send_rpl("323", user, reply_params, "");
    }
    else
    {
        std::cout << BLUE << "DEBUG: has params in list" << NC << std::endl;
        std::vector<std::string> channels_name = old_ft_split(params[0], ",");
        server->send_rpl("321", user, reply_params, "");
        if (channels_name.size() > 0)
        {
            for (std::vector<std::string>::iterator it = channels_name.begin(); it != channels_name.end(); it++)
            {
                Channel *chan = server->get_channel_ptr((*it));
                if (chan)
                {
                    std::string nb = test_string(chan->get_members_nb());

                    reply_params.push_back(chan->get_name());
                    reply_params.push_back(nb);
                    reply_params.push_back(chan->get_topic());
                    server->send_rpl("322", user, reply_params, "");
                    reply_params.clear();
                }
            }
        }
        server->send_rpl("323", user, reply_params, "");
    }
}