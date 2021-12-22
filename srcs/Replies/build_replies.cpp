#include <IRC.hpp>

std::string IRC::build_reply(std::string code, User *user, std::vector<std::string> params, std::string command)
{
    int int_code = atoi(code.c_str());

    std::string prefix;
    if (user->get_nickname().empty())
        prefix = ":" + user->get_hostname() + " " + code + " * ";
    else
        prefix = ":" + user->get_hostname() + " " + code + " " + user->get_nickname() + " ";

    if (command.empty())
    {
        switch (int_code)
        {
        case 1:
            return prefix + RPL_WELCOME(params[0], params[1], params[2]);
        case 2:
            return prefix + RPL_YOURHOST(params[0], "1.0");
        case 3:
            return prefix + RPL_CREATED(params[0]);
        case 4:
            return prefix + RPL_MYINFO(params[0], "1.0", USER_VALID_MODES, CHANNEL_VALID_MODES);
        case 221:
            return prefix + RPL_UMODEIS(user->get_modes());
        case 301:
            return prefix + RPL_AWAY(params[0], params[1]);
        case 305:
            return prefix + RPL_UNAWAY();
        case 306:
            return prefix + RPL_NOWAWAY();
        case 315:
        {
            std::string rpl = ":";
            Channel *channel = this->find_channel(params[0]);
            rpl += user->get_nickname() + "!" + user->get_nickname() + "@0 315 : ";
            rpl += channel->get_name() + " :End of WHO list \r\n";
            return (rpl);
        }
        case 321:
            return prefix + RPL_LISTSTART();
        case 322:
            return prefix + RPL_LIST(params[0], params[1], params[2]);
        case 323:
            return prefix + RPL_LISTEND();
        case 324:
            return prefix + RPL_CHANNELMODEIS(params[0], params[1], params[2]);
        case 351:
            return prefix + RPL_VERSION(params[0], params[1], params[2], params[3]);
        case 331:
            return prefix + RPL_NOTOPIC(params[0]);
        case 332:
            return prefix + RPL_TOPIC(params[0], params[1]);
        case 341:
            return prefix + RPL_INVITING(params[0], params[1]);
            /*
        case 342:
            return prefix + RPL_SUMMONING(user->get_name());
        case 351:
            return prefix + RPL_VERSION();
            */
            //TODO: a tester
        case 353:
        {
            /*
                prefix += " = " + channels[0]->get_name() + " :";
                std::vector<User *> tmp = channels[0]->get_members();
                std::vector<User *>::iterator it = tmp.begin();
                std::vector<User *>::iterator ite = tmp.end();
                while (it != ite)
                {
                    if (channels[0]->user_is_operator(*it) == 1)
                        prefix += "@";
                    prefix += ((*it)->get_nickname() + " ");
                    it++;
                }
                prefix +=  "\r\n";
                return prefix;
                */
        }
        case 366:
        {
            std::string rpl = ":127.0.0.1 " + code + " " + user->get_nickname() + " ";
            int size = params.size();
            if (size > 0)
                rpl += params[0];
            rpl += " :End of NAMES list\r\n";
#if DEBUG == 1
            std::cout << rpl << std::endl;
#endif
            return (rpl);
        }
        case 371:
            return prefix + RPL_INFO(params[0]);
        case 372:
            return prefix + RPL_MOTD(params[0]);
        case 374:
            return prefix + RPL_ENDOFINFO();
        case 375:
            return prefix + RPL_MOTDSTART(params[0]);
        case 376:
            return prefix + RPL_ENDOFMOTD();
        case 381:
            return prefix + RPL_YOUREOPER();
        case 391:
            return prefix + RPL_TIME(params[0], params[1]);
        case 401:
            return prefix + ERR_NOSUCHNICK(params[0]);
        case 402:
            return prefix + ERR_NOSUCHSERVER(params[0]);
        case 403:
            return prefix + ERR_NOSUCHCHANNEL(params[0]);
        case 404:
            return prefix + ERR_CANNOTSENDTOCHAN(params[0]);
        case 405:
            return prefix + ERR_TOOMANYCHANNELS(params[0]);
        case 406:
            return prefix + ERR_WASNOSUCHNICK(params[0]);
        case 407:
            return prefix + ERR_TOOMANYCHANNELS(params[0]);
        case 409:
            return prefix + ERR_NOORIGIN();
        case 411:
            return prefix + ERR_NORECIPIENT(params[0]);
        case 412:
            return prefix + ERR_NOTEXTTOSEND();
        case 413:
            return prefix + ERR_NOTOPLEVEL(params[0]);
        case 414:
            return prefix + ERR_WILDTOPLEVEL(params[0]);
        case 415:
            return prefix + ERR_BADMASK(params[0]);
        case 421:
            return prefix + ERR_UNKNOWNCOMMAND(params[0]);
        case 422:
            return prefix + ERR_NOMOTD();
        case 423:
            return prefix + ERR_NOADMININFO(params[0]);
        case 424:
        {
            std::vector<std::string>::iterator it = params.begin();
            std::vector<std::string>::iterator it2 = it++;
            std::string val1 = (*it);
            std::string val2 = (*it2);
            return prefix + ERR_FILEERROR(val1, val2);
        }
        case 431:
            return prefix + ERR_NONICKNAMEGIVEN();
        case 432:
            return prefix + ERR_ERRONEUSNICKNAME(params[0]);
        case 433:
            return prefix + ERR_NICKNAMEINUSE(params[0]);
        //TODO: tester si on retourne bien les bons attributs
        case 436:
            return prefix + ERR_NICKCOLLISION(params[0], user->get_realname(), user->get_hostname());
        case 437:
            return prefix + ERR_UNAVAILRESOURCE(params[0]);
        case 441:
        {
            std::vector<std::string>::iterator it = params.begin();
            std::vector<std::string>::iterator it2 = it++;
            std::string val1 = (*it);
            std::string val2 = (*it2);
            return prefix + ERR_USERNOTINCHANNEL(val1, val2);
        }
        case 442:
            return prefix + ERR_NOTONCHANNEL(params[0]);
        case 443:
        {
            std::vector<std::string>::iterator it = params.begin();
            std::vector<std::string>::iterator it2 = it++;
            std::string val1 = (*it);
            std::string val2 = (*it2);
            return prefix + ERR_USERONCHANNEL(val1, val2);
        }
        case 444:
            return prefix + ERR_NOLOGIN(params[0]);
        case 445:
            return prefix + ERR_SUMMONDISABLED();
        case 446:
            return prefix + ERR_USERSDISABLED();
        case 451:
            return prefix + ERR_NOTREGISTERED();
        case 461:
            return prefix + ERR_NEEDMOREPARAMS(params[0]);
        case 462:
            return prefix + ERR_ALREADYREGISTRED();
        case 463:
            return prefix + ERR_NOPERMFORHOST();
        case 464:
            return prefix + ERR_PASSWDMISMATCH();
        case 465:
            return prefix + ERR_YOUREBANNEDCREEP();
        case 467:
            return prefix + ERR_KEYSET(params[0]);
        case 471:
            return prefix + ERR_CHANNELISFULL(params[0]);
        case 472:
            return prefix + ERR_UNKNOWNMODE(params[0], params[1]);
        case 473:
            return prefix + ERR_INVITEONLYCHAN(params[0]);
        case 474:
            return prefix + ERR_BANNEDFROMCHAN(params[0]);
        case 475:
            return prefix + ERR_BADCHANNELKEY(params[0]);
        case 477:
            return prefix + ERR_NOCHANMODES(params[0]);
        case 478:
        {
            std::vector<std::string>::iterator it = params.begin();
            std::vector<std::string>::iterator it2 = it++;
            std::string val1 = (*it);
            std::string val2 = (*it2);
            return prefix + ERR_BANLISTFULL(val1, val2);
        }
        case 481:
            return prefix + ERR_NOPRIVILEGES();
        case 482:
            return prefix + ERR_CHANOPRIVSNEEDED(params[0]);
        case 483:
            return prefix + ERR_CANTKILLSERVER();
        case 484:
            return prefix + ERR_RESTRICTED();
        case 485:
            return prefix + ERR_UNIQOPRIVSNEEDED();
        case 491:
            return prefix + ERR_NOOPERHOST();
        case 501:
            return prefix + ERR_UMODEUNKNOWNFLAG();
        case 502:
            return prefix + ERR_USERSDONTMATCH();
        case 999:
            return (":127.0.0.1 PONG\r\n");
        case 998:
            return prefix + "ERROR\r\n";
        default:
            return std::string("");
        }
    }
    else
    {
        if (command.compare("JOIN") == 0)
            return (":" + user->get_nickname() + "!" + user->get_username() + "@" + "0 " + command + " " + params[0] + "\r\n");
        else if (command.compare("PART") == 0)
        {
            return (":" + params[0] + "!" + params[1] + "@" + "127.0.0.1 " + command + " " + params[2] + " " + params[3] + "\r\n");
        }
        //Attention comportement differents en fontion du nombre de params
        //J ai repris send topic message
        /*
        else if (command.compare("TOPIC") == 0)
        {
            unsigned int size = params.size();
            std::string rpl = ":" + user->get_nickname() + "!" + user->get_username() + "@" + "0";
#if MALATINI == 1
            std::cout << PURPLE << "Topic size is " << size << NC << std::endl;
            std::cout << PURPLE << params[0] << std::endl;
            std::cout << params[1] << NC << std::endl;
#endif
            if (size > 1 && params[1].compare(":No topic is set"))
                rpl += " TOPIC ";
            else
                rpl += " 331 : ";
            rpl += params[0] + " ";
            rpl += params[1] + "\r\n";
            return rpl;
        }
        */
        /*
        else if (command.compare("NAMES") == 0)
        {
            std::string rpl = ":" + user->get_nickname() + "!" + user->get_username() + "@" + "127.0.0.1";
            int size = params.size();
            if (size > 0)
            {
                if (!params[0].empty())
                    rpl += params[0];
            }
            rpl += " :End of NAMES list\r\n";
            #if DEBUG == 1
                std::cout << "Names reply is "<< rpl << std::endl;
            #endif
            return (rpl);
        }
        */
        if (command == "PRIVMSG")
            return (":" + params[0] + "!" + params[1] + "@" + params[2] + " " + command + " " + params[3] + " " + params[4] + "\r\n");
        else if (command == "NOTICE")
        {
            if (code == "server")
                return (":" + params[0] + " " + command + " " + params[1] + " " + params[2] + "\r\n");
            else
                return (":" + params[0] + "!" + params[1] + "@" + params[2] + " " + command + " " + params[3] + " " + params[4] + "\r\n");
        }
        else if (command == "INVITE")
            return (":" + params[0] + "!" + params[1] + "@" + params[2] + " " + command + " " + params[3] + " " + params[4] + "\r\n");
        else if (command == "KICK")
            return (":" + params[0] + "!" + params[1] + "@" + params[2] + " " + command + " " + params[3] + " " + params[4] + " " + params[5] + "\r\n");
        else if (command == "MODE_USER")
            return (":" + user->get_nickname() + " MODE " + user->get_nickname() + " :" + params[0] + "\r\n");
        else if (command == "MODE_CHANNEL")
            return (":" + params[0] + "!" + params[1] + "@" + params[2] + " MODE " + params[3] + " " + params[4] + " " + params[5] + "\r\n");
    }
#if DEBUG == 1
    std::cout << PURPLE << "BUILD : REPLY : Error, did not match any case" << std::endl;
#endif
    return prefix;
}