#include <irc.hpp>
#include <string>


#include <string>
#include <sstream>

template <typename T>
std::string ToString(T val)
{
    std::stringstream stream;
    stream << val;
    return stream.str();
}

/**
 * @brief format the code into a valid string for the server reply (ex: int 1 --> str 001)
 *
 * @param code
 * @return std::string
 * TODO: renommer avec User
 */
std::string format_code_str(int code)
{
    if (code < 10)
        return "00" + ToString(code);
    else if (code < 100)
        return "0" + ToString(code);
    return ToString(code);
}

std::string build_reply(int code, User *user, std::vector<std::string> params)
{
    (void)code;
    (void)user;
    std::string code_str;
    std::string prefix;

    code_str = format_code_str(code);
    if (user->get_nickname().empty())
        prefix = ":" + user->get_hostname() + " " + code_str + " * ";
    else
        prefix = ":" + user->get_hostname() + " " + code_str + " " + user->get_nickname() + " ";
    switch (code)
    {
    case 1:
        return prefix + RPL_WELCOME(params[0], params[1], params[2]);
    case 2:
        return prefix + RPL_YOURHOST(params[0], "1.0");
    case 3:
        return prefix + RPL_CREATED(params[0]);
    case 4: // TODO remove hardcoded version value
        return prefix + RPL_MYINFO(params[0], "1.0", USER_VALID_MODES, CHANNEL_VALID_MODES);
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
    return std::string("");
}
