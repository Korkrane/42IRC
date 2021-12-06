#include "../../includes/irc.hpp"

#include <cstdlib>

/**
 * @brief 
 * 
 * @param error_code 
 * @param client 
 * @param channel 
 * @param parameter 
 * TODO: a tester + voir si on peut faire un pointeur sur fonction
 * * pour que ce soit plus classe ?
 */
void error_handler(std::string error_code, User *client, Channel *channel, std::string parameter)
{
    //Besoin de faire une "correspondance" entre le message d erreur et le code
    unsigned int code;

    code = atoi(error_code.c_str());
    std::string error_to_send;
    switch (code)
    {
        case 401:
        {
            error_to_send = ERR_NOSUCHNICK(parameter);
            break ;
        }
        case 402:
        {
            error_to_send = ERR_NOSUCHSERVER(parameter);
            break ;
        }
        case 403:
        {
            error_to_send = ERR_NOSUCHCHANNEL(parameter);
            break ;
        }
        case 404:
        {
            error_to_send = ERR_CANNOTSENDTOCHAN(parameter);
            break ;
        }
        case 405:
        {
            error_to_send = ERR_TOOMANYCHANNELS(parameter);
            break ;
        }
        case 406:
        {
            error_to_send = ERR_WASNOSUCHNICK(parameter);
            break ;
        }
        case 407:
        {
            error_to_send = ERR_TOOMANYTARGETS(parameter);
            break ;
        }
        case 409:
        {
            error_to_send = ERR_NOORIGIN();
            break ;
        }
        case 411:
        {
            error_to_send = ERR_NORECIPIENT(parameter);
            break ;
        }
        case 412:
        {
            error_to_send = ERR_NOTEXTTOSEND();
            break ;
        }
        case 413:
        {
            error_to_send = ERR_NOTOPLEVEL(parameter);
            break ;
        }
        case 414:
        {
            error_to_send = ERR_WILDTOPLEVEL(parameter);
            break ;
        }
        case 415:
        {
            error_to_send = ERR_BADMASK(parameter);
            break ;
        }
        case 421:
        {
            error_to_send = ERR_UNKNOWNCOMMAND(parameter);
            break ;
        }
        case 422:
        {
            error_to_send = ERR_NOMOTD();
            break ;
        }
        case 423:
        {
            error_to_send = ERR_NOADMININFO(parameter);
            break ;
        }
        case 424:
        {
            /*
            ** Attention revoir ce cas particulier, pas sur qu ait 
            ** besoin de l implementer
            ** ou alors il faut que la fonctions soient variadiques pour
            ** qu elle puisse avoir un ou plusieurs arguments
            */
            error_to_send = ERR_FILEERROR(parameter, parameter);
            break ;
        }
        case 431:
        {
            /*
            ** Attention revoir ce cas particulier, pas sur qu ait 
            ** besoin de l implementer
            ** ou alors il faut que la fonctions soient variadiques pour
            ** qu elle puisse avoir un ou plusieurs arguments
            */
            error_to_send = ERR_FILEERROR(parameter, parameter);
            break ;
        }
        case 432:
        {
            error_to_send = ERR_ERRONEUSNICKNAME(parameter);
            break ;
        }
        case 433:
        {
            error_to_send = ERR_NICKNAMEINUSE(parameter);
            break ;
        }
        case 436:
        {
            /*
            ** A revoir egalement, pas sure des parametres
            */
            error_to_send = ERR_NICKCOLLISION(parameter, client->get_realname(), client->get_hostname());
            break ;
        }
        case 437:
        {
            error_to_send = ERR_UNAVAILRESOURCE(parameter);
            break ;
        }
        case 441:
        {
            /*
            ** A revoir egalement
            */ 
            error_to_send = ERR_USERNOTINCHANNEL(parameter, parameter);
            break ;
        }
        case 442:
        {
            error_to_send = ERR_NOTONCHANNEL(parameter);
            break ;
        }
        case 443:
        {
            /*
            ** A revoir
            */
            error_to_send = ERR_USERONCHANNEL(parameter, parameter);
            break ;
        }
        case 444:
        {
            error_to_send = ERR_NOLOGIN(parameter);
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
            error_to_send = ERR_NEEDMOREPARAMS(parameter);
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
            //attention revoir cas particulier
            //A tester pour voir quelle messsage associer
            break ;
        }
        case 467:
        {
            error_to_send = ERR_KEYSET(parameter);
            break ;
        }
        case 471:
        {
            error_to_send = ERR_CHANNELISFULL(parameter);
            break ;
        }
        case 472:
        {
            //A revoir
            error_to_send = ERR_UNKNOWNMODE(parameter, parameter);
            break ;
        }
        case 473:
        {
            error_to_send = ERR_INVITEONLYCHAN(parameter);
            break ;
        }
        case 474:
        {
            error_to_send = ERR_BANNEDFROMCHAN(parameter);
            break ;
        }
        case 475:
        {
            error_to_send = ERR_BADCHANNELKEY(parameter);
            break ;
        }
        case 476:
        {
            error_to_send = ERR_BADCHANMASK(parameter);
            break ;
        }
        case 477:
        {
            error_to_send = ERR_NOCHANMODES(parameter);
            break ;
        }
        case 478:
        {
            /*
            ** A revoir
            */
            error_to_send = ERR_BANLISTFULL(parameter, parameter);
            break ;
        }
        case 481:
        {
            error_to_send = ERR_NOPRIVILEGES();
            break ;
        }
        case 482:
        {
            error_to_send = ERR_CHANOPRIVSNEEDED(parameter);
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
    //fonction qui va permettre d envoyer le message au serveur
    //send(client->get_socket(), error_to_send.c_str());
    return ;
}