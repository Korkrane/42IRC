#include <irc.hpp>
//
std::string format_code_str(int code)
{
    if (code < 10)
        return "00" + std::to_string(code);
    else if (code < 100)
        return "0" + std::to_string(code);
    return std::to_string(code);
}

std::string build_reply(int code, User *user, std::vector<std::string> params)
{
    (void)code;
    (void)user;
    (void)params;
    std::string code_str;
    std::string prefix;
    std::string date = "Mon Nov 22 2021";

    code_str = format_code_str(code);
    if (user->get_nickname().empty())
        prefix = ":" + user->get_hostname() + " " + code_str + " * ";
    else
        prefix = ":" + user->get_hostname() + " " + code_str + " " + user->get_nickname() + " ";
    switch (code)
    {
    case 1:
        return prefix + RPL_WELCOME(user->get_nickname(), user->get_username(), user->get_hostname());
    case 2: // TODO servername not user->hostname for 2 & 4
        return prefix + RPL_YOURHOST(user->get_hostname(), "1.0");
    case 3: // TODO remove hardcoded date
        return prefix + RPL_CREATED(date);
    case 4: // TODO remove hardcoded value
        return prefix + RPL_MYINFO(user->get_hostname(), "1.0", "|list of user mode avai|", "|list of user mode avai|");
    case 305:
        return prefix + RPL_UNAWAY();
    case 306:
        return prefix + RPL_NOWAWAY();
    case 351:
        return prefix + RPL_VERSION(params[0], params[1], params[2], params[3]);
    case 372:
        return prefix + RPL_MOTD(params[0]);
    case 375:
        return prefix + RPL_MOTDSTART(params[0]);
    case 376:
        return prefix + RPL_ENDOFMOTD();
    case 391:
        return prefix + RPL_TIME(params[0], params[1]);
    case 402:
        return prefix + ERR_NOSUCHSERVER(params[0]);
    case 421:
        return prefix + ERR_UNKNOWNCOMMAND(params[0]);
    case 422:
        return prefix + ERR_NOMOTD();
    default:
        return std::string("");
    }
    return;
}
*/