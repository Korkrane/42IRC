#include <IRC.hpp>

void Commands::mode_user(User *user, IRC *server)
{
    int param_size = user->get_params_size();
    std::vector<std::string> params = user->get_params();
    std::vector<std::string> reply_params;
    if (param_size == 0)
    {
        server->send_rpl("461", user, reply_params, ""); //ERR_NEEDMOREPARAMS
        return;
    }
    else if (param_size == 1) //SI JUSTE LA TARGET
    {
        if (server->find_user(params[0]))
        {
            if (user->get_nickname() == params[0])
            {
                reply_params.push_back(user->get_modes());
                server->send_rpl("221", user, reply_params, ""); //RPL_UMODEIS
            }
            else
                server->send_rpl("502", user, reply_params, ""); //ERR_USERDONTMATCH
        }
        else
        {
            reply_params.push_back(params[0]);
            server->send_rpl("401", user, reply_params, ""); //ERR_NO_SUCHNICK
        }
        return;
    }
    else if (param_size == 2) //SI TARGET + MODES TO CHANGE
    {
        if (user->get_nickname() == params[0])
        {
            bool has_unknown_mode = false;
            bool sign = true;
            std::string modes(USER_VALID_MODES);
            std::string modes_changed;
            for (std::string::iterator it = params[1].begin(); it != params[1].end(); it++)
            {
                if ((*it) == '-')
                {
                    sign = false;
                    modes_changed.push_back((*it));
                    continue;
                }
                else if ((*it) == '+')
                {
                    sign = true;
                    modes_changed.push_back((*it));
                    continue;
                }
                //std::cout << "value tested: " << (*it) << std::endl;
                if (modes.find((*it)) != std::string::npos)
                {
                    std::string user_modes = user->get_modes();
                    if (sign == true && (user_modes.find((*it)) == std::string::npos)) //add mode to user
                    {
                        //std::cout << "add mode" << std::endl;
                        modes_changed.push_back((*it));
                        user->set_modes(user->get_modes() + (*it));
                    }
                    else if (sign == false && (user_modes.find((*it)) != std::string::npos)) //remove mode to user
                    {
                        //std::cout << "remove mode" << std::endl;
                        modes_changed.push_back((*it));
                        user_modes.erase(std::remove(user_modes.begin(), user_modes.end(), (*it)), user_modes.end());
                        user->set_modes(user_modes);
                    }
                }
                else
                    has_unknown_mode = true;
            }
            if (has_unknown_mode)
            {
                server->send_rpl("501", user, reply_params, "");
                reply_params.clear();
            }
            //here need to format string replied for reply -+i+
            std::string format_modes_params;
            std::cout << "modes_changed before put it in format_modes:" << modes_changed << std::endl;
            for (std::string::iterator it = modes_changed.begin(); it != modes_changed.end(); it++)
            {
                if (format_modes_params.empty() && ((*it) != '-' && (*it) != '+'))
                    format_modes_params.push_back('+');
                if ((*it) != '+' && (*it) != '-')
                {
                    format_modes_params.push_back((*it));
                    continue;
                }
                if (((*it) == '+' || (*it) == '-') && (*(it + 1) != '+' && *(it + 1) != '-' && (it + 1) != modes_changed.end()))
                    format_modes_params.push_back((*it));
            }
            std::cout << "after patching reply format:" << format_modes_params << std::endl;
            if (!format_modes_params.empty())
            {
                reply_params.push_back(format_modes_params);
                server->send_rpl("1005", user, reply_params, "MODE_USER");
                modif_user(user, server, format_modes_params);
            }
        }
        else
            server->send_rpl("502", user, reply_params, ""); //ERR_USERDONTMATCH
    }
}

//TODO to complete based on what mode we are implementing - a separer dans la partie connection registration?
void Commands::modif_user(User *user, IRC *server, std::string modifications)
{
    (void)server;
    bool sign;
    for (std::string::iterator it = modifications.begin(); it != modifications.end(); it++)
    {
        switch ((*it))
        {
        case '+':
        {
            sign = true;
            continue;
        }
        case '-':
        {
            sign = false;
            continue;
        }
        case 'a':
        {
            (sign == true) ? user->is_away(true) : user->is_away(false);
            std::cout << "after mode affect a user away ? " << user->is_away() << std::endl;
            continue;
        }
        case 'i':
            continue;
        case 'w':
            continue;
        case 'r':
            continue;
        case 'o':
        {
            (sign == true) ? user->is_operator(true) : user->is_operator(false);
            std::cout << "after mode affect a user operator ? " << user->is_operator() << std::endl;
            continue;
        }
        case 'O':
            continue;
        case 's':
            continue;
        default:
            continue;
        }
    }
}
