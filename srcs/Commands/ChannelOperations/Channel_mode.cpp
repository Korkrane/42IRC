#include <IRC.hpp>

void Commands::mode_channel(User *user, IRC *server)
{
#if DEBUG == 1
    std::cout << RED << "ENTER IN MODE CHANNEL" << NC << std::endl;
#endif
    int param_size = user->get_params_size();
    std::vector<std::string> params = user->get_params();
    std::vector<std::string> reply_params;
    Channel *chan = server->get_channel_ptr(params[0]);
    if (param_size == 1) //SI JUSTE LA CHANNEL
    {
        if (chan->get_name()[0] != '!')
        {
            //RPL_CHANNELMODEIS
            reply_params.push_back(chan->get_name());
            reply_params.push_back(chan->get_modes());
            //reply_params.push_back(chan->get_name()); //TODO
            server->send_rpl("324", user, reply_params, "");
        }
        else if (chan->get_name()[0] == '!')
        {
            //ERR_NOCHANMODES
            reply_params.push_back(chan->get_name());
            server->send_rpl("477", user, reply_params, "");
        }
        return;
    }
    else if (param_size == 2)
    {
        bool sign = true;
        std::string modes(CHANNEL_VALID_MODES);
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
            if (modes.find((*it)) != std::string::npos && (*it) == 't')
            {
                //AVANT TOUT CHECK SI USER QUI MODE EST DANS LA CHAN et qu'il est opchan
                if (chan->user_is_operator(user) == false)
                {
                    reply_params.push_back(chan->get_name());
                    server->send_rpl("482", user, reply_params, "");
                    reply_params.clear();
                }
                else
                {
                    std::string chan_modes = chan->get_modes();
                    if (sign == true) //add mode
                    {
                        std::cout << "add mode t" << std::endl;
                        chan->set_channel_modes(chan->get_modes() + "t");
                        modes_changed.push_back((*it));
                        reply_params.push_back(user->get_nickname());
                        reply_params.push_back(user->get_username());
                        reply_params.push_back(user->get_hostname());
                        reply_params.push_back(chan->get_name());
                        reply_params.push_back("+t");
                        reply_params.push_back("");
                        server->send_rpl_to_all_members("", chan->get_members(), reply_params, "MODE_CHANNEL");
                        reply_params.clear();
                    }
                    else if (sign == false) //remove mode
                    {
                        std::cout << "remove mode t" << std::endl;
                        chan_modes.erase(std::remove(chan_modes.begin(), chan_modes.end(), (*it)), chan_modes.end());
                        chan->set_modes(chan_modes);
                        modes_changed.push_back((*it));
                        reply_params.push_back(user->get_nickname());
                        reply_params.push_back(user->get_username());
                        reply_params.push_back(user->get_hostname());
                        reply_params.push_back(chan->get_name());
                        reply_params.push_back("-t");
                        reply_params.push_back("");
                        server->send_rpl_to_all_members("", chan->get_members(), reply_params, "MODE_CHANNEL");
                        reply_params.clear();
                    }
                }
            }
            else if (modes.find((*it)) != std::string::npos && (*it) != 't')
            {
                if (sign == false && (*it) == 'k') //drop key without arg
                {
                    std::string key = chan->get_key();
                    chan->unset_has_key();
                    chan->drop_key();
                    reply_params.push_back(user->get_nickname());
                    reply_params.push_back(user->get_username());
                    reply_params.push_back(user->get_hostname());
                    reply_params.push_back(chan->get_name());
                    reply_params.push_back("-k");
                    reply_params.push_back(key);
                    server->send_rpl_to_all_members("", chan->get_members(), reply_params, "MODE_CHANNEL");
                    reply_params.clear();
                }
                else
                {
                    reply_params.push_back(user->get_command_name());
                    server->send_rpl("461", user, reply_params, "");
                    reply_params.clear();
                }
            }
            else //unknown mode
            {    //TO TEST
                if ((*it) != 'o')
                {
                    std::string char_mode(1, (*it));
                    reply_params.push_back(char_mode);
                    reply_params.push_back(chan->get_name());
                    server->send_rpl("472", user, reply_params, "");
                    reply_params.clear();
                }
            }
        }
        return;
    }
    else if (param_size >= 3)
    {
        bool sign = true;
        std::string modes(CHANNEL_VALID_MODES);
        std::string modes_changed;
        //AVANT TOUT CHECK SI USER QUI MODE EST DANS LA CHAN et qu'il est opchan
        if (chan->user_is_operator(user) == false)
        {
            reply_params.push_back(chan->get_name());
            server->send_rpl("482", user, reply_params, "");
            reply_params.clear();
            return;
        }
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
            if (modes.find((*it)) != std::string::npos)
            {
                std::string chan_modes = chan->get_modes();
                if (sign == true) //add mode to user
                {
                    std::cout << "add mode" << std::endl;
                    modes_changed.push_back((*it));

                    switch ((*it))
                    {
                    case 'o':
                    {
                        //check si dans la chan ou non
                        //sinon donner les droits chanops
                        User *target = server->get_user_ptr(params[2]);
                        if (target)
                        {
                            if (chan->user_is_member(target) == false)
                            {
                                reply_params.push_back(target->get_nickname());
                                reply_params.push_back(chan->get_name());
                                server->send_rpl("441", user, reply_params, "");
                                reply_params.clear();
                            }
                            else
                            {
                                chan->newOperator(target);
                                reply_params.push_back(user->get_nickname());
                                reply_params.push_back(user->get_username());
                                reply_params.push_back(user->get_hostname());
                                reply_params.push_back(chan->get_name());
                                reply_params.push_back("+o");
                                reply_params.push_back(target->get_nickname());
                                server->send_rpl_to_all_members("", chan->get_members(), reply_params, "MODE_CHANNEL");
                                reply_params.clear();
                            }
                        }
                        else
                        {
                            reply_params.push_back(params[2]);
                            server->send_rpl("401", user, reply_params, "");
                            reply_params.clear();
                        }
                        break; //STOP LA SUITE DES MODES A AJOUTER
                    }
                    case 'k':
                    {
                        std::string key = params[2];
                        chan->set_has_key();
                        chan->set_key(key);
                        //TODO SEND REPLY
                        reply_params.push_back(user->get_nickname());
                        reply_params.push_back(user->get_username());
                        reply_params.push_back(user->get_hostname());
                        reply_params.push_back(chan->get_name());
                        reply_params.push_back("+k");
                        reply_params.push_back(key);
                        server->send_rpl_to_all_members("", chan->get_members(), reply_params, "MODE_CHANNEL");
                        reply_params.clear();
                        chan->set_channel_modes(chan->get_modes() + "k");
                        chan->set_has_key();
                        modes_changed.push_back((*it));
                        break; //STOP LA SUITE DES MODES A AJOUTER
                    }
                    default:
                        continue;
                    }
                }
                else if (sign == false) //remove mode to user
                {
                    std::cout << "remove mode" << std::endl;
                    modes_changed.push_back((*it));
                    switch ((*it))
                    {
                    case 'o':
                    {
                        User *target = server->get_user_ptr(params[2]);
                        if (target)
                        {
                            if (chan->user_is_member(target) == false)
                            {
                                reply_params.push_back(target->get_nickname());
                                reply_params.push_back(chan->get_name());
                                server->send_rpl("441", user, reply_params, "");
                                reply_params.clear();
                            }
                            else
                            {
                                chan->removeFromOperators(target);
                                reply_params.push_back(user->get_nickname());
                                reply_params.push_back(user->get_username());
                                reply_params.push_back(user->get_hostname());
                                reply_params.push_back(chan->get_name());
                                reply_params.push_back("-o");
                                reply_params.push_back(target->get_nickname());
                                server->send_rpl_to_all_members("", chan->get_members(), reply_params, "MODE_CHANNEL");
                                reply_params.clear();
                                //TODO SEND RPLY
                            }
                        }
                        else
                        {
                            reply_params.push_back(params[2]);
                            server->send_rpl("401", user, reply_params, "");
                            reply_params.clear();
                        }
                        break;
                    }
                    case 'k':
                    {
                        std::string key = chan->get_key();
                        chan->unset_has_key();
                        chan->drop_key();
                        reply_params.push_back(user->get_nickname());
                        reply_params.push_back(user->get_username());
                        reply_params.push_back(user->get_hostname());
                        reply_params.push_back(chan->get_name());
                        reply_params.push_back("-k");
                        reply_params.push_back(key);
                        server->send_rpl_to_all_members("", chan->get_members(), reply_params, "MODE_CHANNEL");
                        reply_params.clear();
                        std::string changed_modes = chan->get_modes();
                        changed_modes.erase(std::remove(changed_modes.begin(), changed_modes.end(), (*it)), changed_modes.end());
                        chan->set_channel_modes(changed_modes);
                        chan->unset_has_key();
                        break;
                    }
                    default:
                        continue;
                    }
                }
            }
        }
    }
}