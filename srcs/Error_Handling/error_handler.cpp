#include <irc.hpp>

/**
 * @brief 
 * 
 * @param error_code 
 * @param user 
 * @param channel 
 * @param parameter 
 */
void error_handler(std::string error_code, User *user, Channel *channel, std::vector<std::string> parameter)
{
    unsigned int code;

    (void)channel;
    code = atoi(error_code.c_str());
    std::string error_to_send;
    switch (code)
    {
        case 401:
        {
            error_to_send = ERR_NOSUCHNICK(parameter.front());
            break ;
        }
        case 402:
        {
            error_to_send = ERR_NOSUCHSERVER(parameter.front());
            break ;
        }
        case 403:
        {
            error_to_send = ERR_NOSUCHCHANNEL(parameter.front());
            break ;
        }
        case 404:
        {
            error_to_send = ERR_CANNOTSENDTOCHAN(parameter.front());
            break ;
        }
        case 405:
        {
            error_to_send = ERR_TOOMANYCHANNELS(parameter.front());
            break ;
        }
        case 406:
        {
            error_to_send = ERR_WASNOSUCHNICK(parameter.front());
            break ;
        }
        case 407:
        {
            error_to_send = ERR_TOOMANYTARGETS(parameter.front());
            break ;
        }
        case 409:
        {
            error_to_send = ERR_NOORIGIN();
            break ;
        }
        case 411:
        {
            error_to_send = ERR_NORECIPIENT(parameter.front());
            break ;
        }
        case 412:
        {
            error_to_send = ERR_NOTEXTTOSEND();
            break ;
        }
        case 413:
        {
            error_to_send = ERR_NOTOPLEVEL(parameter.front());
            break ;
        }
        case 414:
        {
            error_to_send = ERR_WILDTOPLEVEL(parameter.front());
            break ;
        }
        case 415:
        {
            error_to_send = ERR_BADMASK(parameter.front());
            break ;
        }
        case 421:
        {
            error_to_send = ERR_UNKNOWNCOMMAND(parameter.front());
            break ;
        }
        case 422:
        {
            error_to_send = ERR_NOMOTD();
            break ;
        }
        case 423:
        {
            error_to_send = ERR_NOADMININFO(parameter.front());
            break ;
        }
        case 424:
        {
            std::vector<std::string>::iterator it = parameter.begin();
            std::vector<std::string>::iterator it2 = it++;
            std::string val1 = (*it);
            std::string val2 = (*it2);
            error_to_send = ERR_FILEERROR(val1, val2);
            break ;
        }
        case 431:
        {
            std::vector<std::string>::iterator it = parameter.begin();
            std::vector<std::string>::iterator it2 = it++;
            std::string val1 = (*it);
            std::string val2 = (*it2);
            error_to_send = ERR_FILEERROR(val1, val2);
            break ;
        }
        case 432:
        {
            error_to_send = ERR_ERRONEUSNICKNAME(parameter.front());
            break ;
        }
        case 433:
        {
            error_to_send = ERR_NICKNAMEINUSE(parameter.front());
            break ;
        }
        case 436:
        {
            error_to_send = ERR_NICKCOLLISION(parameter.front(), user->get_realname(), user->get_hostname());
            break ;
        }
        case 437:
        {
            error_to_send = ERR_UNAVAILRESOURCE(parameter.front());
            break ;
        }
        case 441:
        {
            std::vector<std::string>::iterator it = parameter.begin();
            std::vector<std::string>::iterator it2 = it++;
            std::string val1 = (*it);
            std::string val2 = (*it2);
            error_to_send = ERR_USERNOTINCHANNEL(val1, val2);
            break ;
        }
        case 442:
        {
            error_to_send = ERR_NOTONCHANNEL(parameter.front());
            break ;
        }
        case 443:
        {
            std::vector<std::string>::iterator it = parameter.begin();
            std::vector<std::string>::iterator it2 = it++;
            std::string val1 = (*it);
            std::string val2 = (*it2);
            error_to_send = ERR_USERONCHANNEL(val1, val2);
            break ;
        }
        case 444:
        {
            error_to_send = ERR_NOLOGIN(parameter.front());
            break ;
        }
        case 445:
        {
            error_to_send = ERR_SUMMONDISABLED();
            break ;
        }
        case 446:
        {
            error_to_send = ERR_USERSDISABLED();
            break ;
        }
        case 451:
        {
            error_to_send = ERR_NOTREGISTERED();
            break ;
        }
        case 461:
        {
            error_to_send = ERR_NEEDMOREPARAMS(parameter.front());
            break ;
        }
        case 462:
        {
            error_to_send = ERR_ALREADYREGISTRED();
            break ;
        }
        case 463:
        {
            error_to_send = ERR_NOPERMFORHOST();
            break ;
        }
        case 464:
        {
            error_to_send = ERR_PASSWDMISMATCH();
            break ;
        }
        case 465:
        {
            error_to_send = ERR_YOUREBANNEDCREEP();
            break ;
        }
        case 466:
        {
            //A tester pour voir quelle messsage associer
            break ;
        }
        case 467:
        {
            error_to_send = ERR_KEYSET(parameter.front());
            break ;
        }
        case 471:
        {
            error_to_send = ERR_CHANNELISFULL(parameter.front());
            break ;
        }
        case 472:
        {
            std::vector<std::string>::iterator it = parameter.begin();
            std::vector<std::string>::iterator it2 = it++;
            std::string val1 = (*it);
            std::string val2 = (*it2);
            error_to_send = ERR_UNKNOWNMODE(val1, val2);
            break ;
        }
        case 473:
        {
            error_to_send = ERR_INVITEONLYCHAN(parameter.front());
            break ;
        }
        case 474:
        {
            error_to_send = ERR_BANNEDFROMCHAN(parameter.front());
            break ;
        }
        case 475:
        {
            error_to_send = ERR_BADCHANNELKEY(parameter.front());
            break ;
        }
        case 476:
        {
            error_to_send = ERR_BADCHANMASK(parameter.front());
            break ;
        }
        case 477:
        {
            error_to_send = ERR_NOCHANMODES(parameter.front());
            break ;
        }
        case 478:
        {
            std::vector<std::string>::iterator it = parameter.begin();
            std::vector<std::string>::iterator it2 = it++;
            std::string val1 = (*it);
            std::string val2 = (*it2);
            error_to_send = ERR_BANLISTFULL(val1, val2);
            break ;
        }
        case 481:
        {
            error_to_send = ERR_NOPRIVILEGES();
            break ;
        }
        case 482:
        {
            error_to_send = ERR_CHANOPRIVSNEEDED(parameter.front());
            break ;
        }
        case 483:
        {
            error_to_send = ERR_CANTKILLSERVER();
            break ;
        }
        case 484:
        {
            error_to_send = ERR_RESTRICTED();
            break ;
        }
        case 485:
        {
            error_to_send = ERR_UNIQOPRIVSNEEDED();
            break ;
        }
        case 491:
        {
            error_to_send = ERR_NOOPERHOST();
            break ;
        }
        case 501:
        {
            error_to_send = ERR_UMODEUNKNOWNFLAG();
            break ;
        }
        case 502:
        {
            error_to_send = ERR_USERSDONTMATCH();
            break ;
        }
    }
    user->get_server()->_response_queue.push_back(std::make_pair(user->get_socket(), error_to_send));
    return ;
}