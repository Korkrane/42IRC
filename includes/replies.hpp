/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replies.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 19:43:12 by bahaas            #+#    #+#             */
/*   Updated: 2021/11/25 17:55:39 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPLIES_HPP
#define REPLIES_HPP

// ERROR REPLIES --> https://datatracker.ietf.org/doc/html/rfc2812#section-5.2

#define ERR_NOSUCHNICK(nickname)             (nickname + " :No such nick/channel\r\n")                              // 401
#define ERR_NOSUCHSERVER(servername)         (servername + " :No such server\r\n")                                  // 402
#define ERR_NOSUCHCHANNEL(channelname)       (channelname + " :No such channel \r\n")                               // 403
#define ERR_CANNOTSENDTOCHAN(channelname)    (channelname + " :Cannot send to channel\r\n")                         // 404
#define ERR_TOOMANYCHANNELS(channelname)     (channelname + " :You have joined too many channels\r\n")              // 405
#define ERR_WASNOSUCHNICK(nickname)          (nickname + " :There was no such nickname\r\n")                        // 406
#define ERR_TOOMANYTARGETS(nickname)         (nickname + " :Duplicate recipients. No message delivered\r\n")        // 407
#define ERR_NOORIGIN()                       (" :No origin specified\r\n")                                          // 409                                                                                // 409
#define ERR_NORECIPIENT(command)             (":No recipient given" + command + "\r\n")                             // 411
#define ERR_NOTEXTTOSEND()                   (":No text to send\r\n")                                               // 412
#define ERR_NOTOPLEVEL(mask)                 (mask + " :No toplevel domain specified\r\n")                          // 413
#define ERR_WILDTOPLEVEL(mask)               (mask + " :Wildcard in toplevel domain\r\n")                           // 414
#define ERR_BADMASK(mask)                    (mask + " :Bad Server/host mask\r\n")                                  // 415
#define ERR_UNKNOWNCOMMAND(command)          (command + " :Unknown command\r\n")                                    // 421
#define ERR_NOMOTD()                         ("MOTD File is missing\r\n")                                           // 422
#define ERR_NOADMININFO(server)              (server + " :No administrative info available\r\n")                    // 423
#define ERR_FILEERROR(fileop, file)          (":File error doing" + fileop + " on" + file + "\r\n")                 // 424
#define ERR_NONICKNAMEGIVEN()                ("No nickname given\r\n")                                              // 431
#define ERR_ERRONEUSNICKNAME(nick)           (nick + " :Erroneous nickname\r\n")                                    // 432
#define ERR_NICKNAMEINUSE(nick)              (nick + " :Nickname is already in use\r\n")                            // 433
#define ERR_NICKCOLLISION(nick, user, host)  (nick + " :Nickname collision KILL from" + user + "@" + host + "\r\n") // 436
#define ERR_UNAVAILRESOURCE(nick_or_channel) (nick_or_channel + " :Nick/channel is temporarily unavailable\r\n")    // 437
#define ERR_USERNOTINCHANNEL(nick, channel)  (nick + " " + channel + " :They aren't on that channel\r\n")           // 441
#define ERR_NOTONCHANNEL(channel)            (channel + " :You're not on that channel\r\n")                         // 442
#define ERR_USERONCHANNEL(user, channel)     (user + " " + channel + " :is already on channel\r\n")                 // 443
#define ERR_NOLOGIN(user)                    (user + " :User not logged in\r\n")                                    // 444
#define ERR_SUMMONDISABLED()                 (":SUMMON has been disabled\r\n")                                      // 445
#define ERR_USERSDISABLED()                  (":USERS has been disabled\r\n")                                       // 446
#define ERR_NOTREGISTERED()                  (":You have not registred\r\n")                                        // 451
#define ERR_NEEDMOREPARAMS(command)          (command + " :Not enough parameters\r\n")                              // 461
#define ERR_ALREADYREGISTRED()               (":Unauthorized command (already registered)\r\n")                     // 462
#define ERR_NOPERMFORHOST()                  (":Your host isn't among the privileged\r\n")                          // 463
#define ERR_PASSWDMISMATCH()                 ("Password incorect\r\n")                                              // 464
#define ERR_YOUREBANNEDCREEP()               ("You are banned from this server\r\n")                                // 465
#define ERR_YOUWILLBEBANNED                                                                                         // no mssg defined yet                                                                                        // 466
#define ERR_KEYSET(channel)                  (channel + " :Channel key already set\r\n")                            // 467
#define ERR_CHANNELISFULL(channel)           (channel + " :Cannot join channel (+l)\r\n")                           // 471
#define ERR_UNKNOWNMODE(char, channel)       (char + " :is unknown mode char to me for" + channel + "\r\n")         // 472
#define ERR_INVITEONLYCHAN(channel)          (channel + " :Cannot join channel (+i)\r\n")                           // 473
#define ERR_BANNEDFROMCHAN(channel)          (channel + " :Cannot join channel (+b)\r\n")                           // 474
#define ERR_BADCHANNELKEY(channel)           (channel + " :Cannot join channel (+k)\r\n")                           // 475
#define ERR_BADCHANMASK(channel)             (channel + " :Bad channel Mask\r\n")                                   // 476
#define ERR_NOCHANMODES(channel)             (channel + " :Channel doesn't support modes\r\n")                      // 477
#define ERR_BANLISTFULL(channel, char)       (channel + " " + char + " :Channel list is full\r\n")                  // 478
#define ERR_NOPRIVILEGES()                   (":Permission Denied- You're not an IRC operator\r\n")                 // 481
#define ERR_CHANOPRIVSNEEDED(channel)        (channel + " :You're not channel operator\r\n")                        // 482
#define ERR_CANTKILLSERVER()                 (":You can't kill a server!\r\n")                                      // 483
#define ERR_RESTRICTED()                     ("Your connection is restricted !\r\n")                                // 484
#define ERR_UNIQOPRIVSNEEDED()               ("You're not the original channel operator\r\n")                       // 485
#define ERR_NOOPERHOST()                     (":No O-lines for your host\r\n")                                      // 491
#define ERR_UMODEUNKNOWNFLAG()               (":Unknown MODE flag\r\n")                                             // 501
#define ERR_USERSDONTMATCH()                 (":Cannot change mode for other users\r\n")                            // 502

// COMMAND REPLIES --> https://datatracker.ietf.org/doc/html/rfc2812#section-5.1
// The server sends Replies 001 to 004 to a user upon successful registration.
// Replies 311 - 313, 317 - 319 are all replies generated in response to a WHOIS message.

#define RPL_WELCOME(nick, user, host)                                    (":Welcome to the Internet Relay Network " + nick + "!" + user + "@" + host + "\r\n") // 001
#define RPL_YOURHOST(servername, ver)                                    (":Your host is " + servername + ", running version " + ver + "\r\n")                 // 002
#define RPL_CREATED(date)                                                (":This server was created " + date + "\r\n")                                         // 003
#define RPL_MYINFO(servername, version, av_user_modes, av_channel_modes) (servername + " " + version + " " + av_user_modes + " " + av_channel_modes + "\r\n")  // 004
#define RPL_BOUNCE(servername, portnumber)                               ("Try server" + servername + ", port" + portnumber "\r\n")                            // 005
#define RPL_USERHOST                                                                                                                                           // 302 weird one, not sure of the output
#define RPL_ISON                                                                                                                                               // 303 weird one, not sure of the output
#define RPL_AWAY(nick, away_message)                                     (nick + " :" + away_message + "\r\n")                                                 // 301
#define RPL_UNAWAY()                                                     (":You are no longer marked as being away\r\n")                                       // 305
#define RPL_NOWAWAY()                                                    (":You have been marked as being away\r\n")                                           // 306
#define RPL_WHOISUSER(nick, user, host, real_name)                       (nick + " " + user + " " + host + " * :" + real_name + "\r\n")                        // 311
#define RPL_WHOISSERVER(nick, server, server_info)                       (nick + " " + server + " :" + server_info + "\r\n")                                   // 312
#define RPL_WHOISOPERATOR                                                (nick)(nick + " :is an IRC operator\r\n")                                             // 313
#define RPL_WHOISIDLE(nick, integer)                                     (nick + " " + integer + " :secons idle\r\n")                                          // 317
#define RPL_ENDOFWHOIS(nick)                                             (nick + " :End of WHOIS list\r\n")                                                    // 318
#define RPL_WHOISCHANNELS                                                                                                                                      // 319 weird one, not sure of the output
#define RPL_WHOWASUSER(nick, user, host, real_name)                      (nick + " " + user + " " + host + " * :" + real_name + "\r\n")                        // 314
#define RPL_ENDOFWHOWAS(nick)                                            (nick + " :End of WHOAS\r\n")                                                         // 369
//#define RPL_LISTSTART                                                                                                                                          // 321 obsolete. Not used
#define RPL_LIST                                                                                                                       // 322 weird one, not sure of the output
#define RPL_LISTEND()                                      (+":End of LIST\r\n")                                                       // 323
#define RPL_UNIQOPIS(channel, nickname)                    (channel + " " + nickname + "\r\n")                                         // 325
#define RPL_CHANNELMODEIS(channel, mode, mode_params)      (channel + " " + mode + " " + mode_params + "\r\n")                         // 324
#define RPL_NOTOPIC(channel)                               (channel + " :No topic is set\r\n")                                         // 331
#define RPL_TOPIC(channel, topic)                          (channel + " :" + topic + "\r\n")                                           // 332
#define RPL_INVITING(channel, nick)                        (channel + " " + nick "\r\n")                                               // 341
#define RPL_SUMMONING(user)                                (user + " :Summoning user to IRC\r\n")                                      // 342
#define RPL_INVITELIST(channel, invitemask)                (channel + " " + invitemask + "\r\n")                                       // 346
#define RPL_ENDOFINTIELIST(channel)                        (channel + " :End of channel invite list\r\n")                              // 347
#define RPL_EXCEPTLIST(channel, exceptionmask)             (channel + " " + exceptionmask + "\r\n")                                    // 348
#define RPL_ENDOFEXCEPTLIST(channel)                       (channel + " :End of channel exception list\r\n")                           // 349
#define RPL_VERSION(version, debuglevel, server, comments) (version + "." + debuglevel + " " + server " :" + comments + "\r\n")        // 351
#define RPL_WHOREPLY                                                                                                                   // 352 weird one, not sure of the output
#define RPL_ENDOFWHO(name)                                 (name + " :End of WHO list\r\n")                                            // 315
#define RPL_NAMREPLY                                                                                                                   // 353 weird one, not sure of the output
#define RPL_ENDOFNAMES(channel)                            (channel + " :End of NAMES list\r\n")                                       // 366
#define RPL_LINKS(mask, server, hopcount, server_info)     (mask + " " + server + " :" + hopcount + " " + server_info + "\r\n")        // 364
#define RPL_ENDOFLINKS(mask)                               (mask + " :End of LINKS list\r\n")                                          // 365
#define RPL_BANLIST(channel, banmask)                      (channel + " " + banmask + "\r\n")                                          // 367
#define RPL_ENDOFBANLIST(channel)                          (channel + " :End of channel ban list\r\n")                                 // 368
#define RPL_INFO(string)                                   (":" + string + "\r\n")                                                     // 371
#define RPL_ENDOFINFO()                                    (":End of INFO list\r\n")                                                   // 374
#define RPL_MOTDSTART(server)                              (":- " + server + " Message of the day - \r\n")                             // 375
#define RPL_MOTD(text)                                     (":- " + text + "\r\n")                                                     // 372
#define RPL_ENDOFMOTD()                                    (":End of MOTD command\r\n")                                                // 376
#define RPL_YOUREOPER()                                    (":You are now an IRC operator\r\n")                                        // 381
#define RPL_REHASHING(config_file)                         (config_file + " :Rehashing\r\n")                                           // 382
#define RPL_YOURESERVICE(servicename)                      ("You are service " + servicename + "\r\n")                                 // 383
#define RPL_TIME(server, local_time)                       (server + " :" + local_time + "\r\n")                                       // 391
#define RPL_USERSSTART()                                   (":UserID Terminal Host\r\n")                                               // 392
#define RPL_USERS(username, ttyline, hostname)             (":" + username + " " + ttyline + " " + hostname + "\r\n")                  // 393
#define RPL_ENDOFUSERS()                                   (":End of users\r\n")                                                       // 394
#define RPL_NOUSERS()                                      (":Nobody logged in\r\n")                                                   // 395
#define RPL_TRACELINK                                                                                                                  // 200 weird one, not sure of the output
#define RPL_TRACECONNECTING(class, server)                 ("Try. " + class + " " + server + "\r\n")                                   // 201
#define RPL_TRACEHANDSHAKE(class, server)                  ("H.S " + class + " " + server + "\r\n")                                    // 202
#define RPL_TRACEUNKNOWN(class, client_ip)                 ("??? " + class + " [" + client_ip + "]\r\n")                               // 203
#define RPL_TRACEOPERATOR(class, nick)                     ("Oper " + class + " " + nick + "\r\n")                                     // 204
#define RPL_TRACEUSER(class, nick)                         ("User " + class + " " + nick + "\r\n")                                     // 205
#define RPL_TRACESERVER                                                                                                                // 206 weird one, not sure of the output
#define RPL_TRACESERVICE(class, name, type, active_type)   ("Service " + class + " " + name + " " + type + " " + active_type + "\r\n") // 207
#define RPL_TRACENEWTYPE(newtype, client_name)             (newtype + " 0 " + client_name + "\r\n")                                    // 208
#define RPL_TRACECLASS(class, count)                       ("Class " + class + " " + count + "\r\n")                                   // 209
// #define RPL_TRACERECONNECT                                                                                                                // 210 Unused
#define RPL_TRACELOG(logfile, debug_level)                                                            ("File" + logfile + " " + debug_level + "\r\n")                          // 261
#define RPL_TRACEEND(server_name, v_debug_level)                                                      (server_name + " " + v_debug_level + " :End of TRACE\r\n")               // 262
#define RPL_STATSLINKINFO(linkname, sendq, sent_mssg, sent_Kbytes, recv_mssg, recv_Kbytes, time_open) (linkname + " " + sendq + "\r\n")                                        // 211 check if used
#define RPL_STATSCOMMANDS(command, count, byte_count, remote_count)                                   (command + " " + count + " " + byte_count + " " + remote_count + "\r\n") // 212
//#define RPL_STATSCLINE      // 213
//#define RPL_STATSNLINE      // 214
//#define RPL_STATSILINE      // 215
//#define RPL_STATSKLINE      // 216
//#define RPL_STATSQLINE      // 217
//#define RPL_STATSYLINE      // 218
#define RPL_ENDOFSTATS (stats_letter)(stats_letter + " :End of STATS report\r\n") // 219
//#define RPL_STATSVLINE      // 240
//#define RPL_STATSLLINE      // 241
#define RPL_STATSUPTIME (up_format)(":Server Up " + up_format + "\r\n")           // 242
#define RPL_STATSOLINE  (hostmask, name)("O " + hostmask + " * " + name + "\r\n") // 243
//#define RPL_STATSHLINE      // 244
#define RPL_UMODEIS                (user_mode_string)(user_mode_string + "\r\n")                                                                                                          // 221
#define RPL_SERVLIST               (name, server, mask, type, hopcount, info)(name + " " + server + " " + mask + " " + type + " " + hopcount + " " + info + "\r\n")                       // 234
#define RPL_SERVLISTEND            (mask, type)(mask + " " + type + " :End of service listing\r\n")                                                                                       // 235
#define RPL_LUSERCLIENT            (integer_c, intger_service, integer_serv)(":There are " + integer_c + " users and " + integer_service + " services on" + integer_serv + "servers\r\n") // 251
#define RPL_LUSEROP                (integer)(integer + " :operator(s) online\r\n")                                                                                                        // 252
#define RPL_LUSERUNKNOWN           (integer)(integer + " :unknown connection(s)\r\n")                                                                                                     // 253
#define RPL_LUSERCHANNELS          (integer)(integer + " :channels formed\r\n")                                                                                                           // 254
#define RPL_LUSERME                (integer_c, integer_s)(":I have " + integer_c + " clients and " + integer_s + "servers\r\n")                                                           // 255
#define RPL_ADMINME                (server)(server + " :Administrative info\r\n")                                                                                                         // 256
#define RPL_ADMINLOC1              (admin_info)(":" + admin_info + "\r\n")                                                                                                                // 257
#define RPL_ADMINLOC2(admin_info)  (":" + admin_info + "\r\n")                                                                                                                            // 258
#define RPL_ADMINEMAIL(admin_info) (":" + admin_info + "\r\n")                                                                                                                            // 259

#endif // !REPLIES_HPP