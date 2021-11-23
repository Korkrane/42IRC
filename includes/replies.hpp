/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replies.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 19:43:12 by bahaas            #+#    #+#             */
/*   Updated: 2021/11/23 21:53:08 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPLIES_HPP
#define REPLIES_HPP

#include "irc.hpp"

// ERROR REPLIES --> https://datatracker.ietf.org/doc/html/rfc2812#section-5.2

#define ERR_NOSUCHNICK(nickname) (nickname + " :No such nick/channel\r\n")                                         // 401
#define ERR_NOSUCHSERVER(servername) (servername + " :No such server\r\n")                                         // 402
#define ERR_NOSUCHCHANNEL(channelname) (channelname + " :No such channel \r\n")                                    // 403
#define ERR_CANNOTSENDTOCHAN(channelname) (channelname + " :Cannot send to channel\r\n")                           // 404
#define ERR_TOOMANYCHANNELS(channelname) (channelname + " :You have joined too many channels\r\n")                 // 405
#define ERR_WASNOSUCHNICK(nickname) (nickname + " :There was no such nickname\r\n")                                // 406
#define ERR_TOOMANYTARGETS(nickname) (nickname + " :Duplicate recipients. No message delivered\r\n")               // 407
#define ERR_NOORIGIN ()(" :No origin specified\r\n")                                                               // 409                                                                                // 409
#define ERR_NORECIPIENT (command)(":No recipient given" + command + "\r\n")                                        // 411
#define ERR_NOTEXTTOSEND ()(":No text to send\r\n")                                                                // 412
#define ERR_NOTOPLEVEL (mask)(mask + " :No toplevel domain specified\r\n")                                         // 413
#define ERR_WILDTOPLEVEL (mask)(mask + " :Wildcard in toplevel domain\r\n")                                        // 414
#define ERR_BADMASK (mask)(mask + " :Bad Server/host mask\r\n")                                                    // 415
#define ERR_UNKNOWNCOMMAND (command)(command + " :Unknown command\r\n")                                            // 421
#define ERR_NOMOTD ()("MOTD File is missing\r\n")                                                                  // 422
#define ERR_NOADMININFO (server)(server + " :No administrative info available\r\n")                                // 423
#define ERR_FILEERROR (fileop, file)(":File error doing" + fileop + " on" + file + "\r\n")                         // 424
#define ERR_NONICKNAMEGIVEN ()("No nickname given\r\n")                                                            // 431
#define ERR_ERRONEUSNICKNAME (nick)(nick + " :Erroneous nickname\r\n")                                             // 432
#define ERR_NICKNAMEINUSE (nick)(nick + " :Nickname is already in use\r\n")                                        // 433
#define ERR_NICKCOLLISION (nick, user, host)(nick + " :Nickname collision KILL from" + user + "@" + host + "\r\n") // 436
#define ERR_UNAVAILRESOURCE (nick_or_channel)(nick_or_channel + " :Nick/channel is temporarily unavailable\r\n")   // 437
#define ERR_USERNOTINCHANNEL (nick, channel)(nick + " " + channel + " :They aren't on that channel\r\n")           // 441
#define ERR_NOTONCHANNEL (channel)(channel + " :You're not on that channel\r\n")                                   // 442
#define ERR_USERONCHANNEL (user, channel)(user + " " + channel + " :is already on channel\r\n")                    // 443
#define ERR_NOLOGIN (user)(user + " :User not logged in\r\n")                                                      // 444
#define ERR_SUMMONDISABLED ()(":SUMMON has been disabled\r\n")                                                     // 445
#define ERR_USERSDISABLED ()(":USERS has been disabled\r\n")                                                       // 446
#define ERR_NOTREGISTERED ()(":You have not registred\r\n")                                                        // 451
#define ERR_NEEDMOREPARAMS (command)(command + " :Not enough parameters\r\n")                                      // 461
#define ERR_ALREADYREGISTRED ()(":Unauthorized command (already registered)\r\n")                                  // 462
#define ERR_NOPERMFORHOST ()(":Your host isn't among the privileged\r\n")                                          // 463
#define ERR_PASSWDMISMATCH ()("Password incorect\r\n")                                                             // 464
#define ERR_YOUREBANNEDCREEP ()("You are banned from this server\r\n")                                             // 465
#define ERR_YOUWILLBEBANNED                                                                                        // no mssg defined yet                                                                                        // 466
#define ERR_KEYSET (channel)(channel + " :Channel key already set\r\n")                                            // 467
#define ERR_CHANNELISFULL (channel)(channel + " :Cannot join channel (+l)\r\n")                                    // 471
#define ERR_UNKNOWNMODE (char, channel)(char + " :is unknown mode char to me for" + channel + "\r\n")              // 472
#define ERR_INVITEONLYCHAN (channel)(channel + " :Cannot join channel (+i)\r\n")                                   // 473
#define ERR_BANNEDFROMCHAN (channel)(channel + " :Cannot join channel (+b)\r\n")                                   // 474
#define ERR_BADCHANNELKEY (channel)(channel + " :Cannot join channel (+k)\r\n")                                    // 475
#define ERR_BADCHANMASK (channel)(channel + " :Bad channel Mask\r\n")                                              // 476
#define ERR_NOCHANMODES (channel)(channel + " :Channel doesn't support modes\r\n")                                 // 477
#define ERR_BANLISTFULL (channel, char)(channel + " " + char + " :Channel list is full\r\n")                       // 478
#define ERR_NOPRIVILEGES ()(":Permission Denied- You're not an IRC operator\r\n")                                  // 481
#define ERR_CHANOPRIVSNEEDED (channel)(channel + " :You're not channel operator\r\n")                              // 482
#define ERR_CANTKILLSERVER ()(":You can't kill a server!\r\n")                                                     // 483
#define ERR_RESTRICTED ()("Your connection is restricted !\r\n")                                                   // 484
#define ERR_UNIQOPRIVSNEEDED ()("You're not the original channel operator\r\n")                                    // 485
#define ERR_NOOPERHOST ()(":No O-lines for your host\r\n")                                                         // 491
#define ERR_UMODEUNKNOWNFLAG ()(":Unknown MODE flag\r\n")                                                          // 501
#define ERR_USERSDONTMATCH ()(":Cannot change mode for other users\r\n")                                           // 502

// COMMAND REPLIES --> https://datatracker.ietf.org/doc/html/rfc2812#section-5.1
// The server sends Replies 001 to 004 to a user upon successful registration.
// Replies 311 - 313, 317 - 319 are all replies generated in response to a WHOIS message.

#define RPL_WELCOME (nick, user, host)("Welcome to the Internet Relay Network " + nick + "!" + user + "@" + host + "\r\n")                                    // 001
#define RPL_YOURHOST (servername, ver)("Your host is" + servername + ", running version " + ver + "\r\n")                                                     // 002
#define RPL_CREATED (date)("This server was created" + date + "\r\n")                                                                                         // 003
#define RPL_MYINFO (servername, version, av_user_modes, av_channel_modes)(servername + " " + version + " " + av_user_modes + " " + av_channel_modes + "\r\n") // 004
#define RPL_BOUNCE (servername, portnumber)("Try server" + servername + ", port" + portnumber "\r\n")                                                         // 005
#define RPL_USERHOST                                                                                                                                          // 302 weird one, not sure of the output
#define RPL_ISON                                                                                                                                              // 303 weird one, not sure of the output
#define RPL_AWAY (nick, away_message)(nick + " :" + away_message + "\r\n")                                                                                    // 301
#define RPL_UNAWAY ()(":You are no longer marked as being away\r\n")                                                                                          // 305
#define RPL_NOWAWAY ()(":You have been marked as being away\r\n")                                                                                             // 306
#define RPL_WHOISUSER (nick, user, host, real_name)(nick + " " + user + " " + host + " * :" + real_name + "\r\n")                                             // 311
#define RPL_WHOISSERVER (nick, server, server_info)(nick + " " + server + " :" + server_info + "\r\n")                                                        // 312
#define RPL_WHOISOPERATOR (nick)(nick + " :is an IRC operator\r\n")                                                                                           // 313
#define RPL_WHOISIDLE (nick, integer)(nick + " " + integer + " :secons idle\r\n")                                                                             // 317
#define RPL_ENDOFWHOIS (nick)(nick + " :End of WHOIS list\r\n")                                                                                               // 318
#define RPL_WHOISCHANNELS                                                                                                                                     // 319 weird one, not sure of the output
#define RPL_WHOWASUSER (nick, user, host, real_name)(nick + " " + user + " " + host + " * :" + real_name + "\r\n")                                            // 314
#define RPL_ENDOFWHOWAS (nick)(nick + " :End of WHOAS\r\n")                                                                                                   // 369
//#define RPL_LISTSTART                                                                                                                                          // 321 obsolete. Not used
#define RPL_LIST                                                                                          // 322 weird one, not sure of the output
#define RPL_LISTEND ()(+":End of LIST\r\n")                                                               // 323
#define RPL_UNIQOPIS (channel, nickname)(channel + " " + nickname + "\r\n")                               // 325
#define RPL_CHANNELMODEIS (channel, mode, mode_params)(channel + " " + mode + " " + mode_params + "\r\n") // 324
#define RPL_NOTOPIC (channel)(channel + " :No topic is set\r\n")                                          // 331
#define RPL_TOPIC (channel, topic)(channel + " :" + topic + "\r\n")                                       // 332
#define RPL_INVITING (channel, nick)(channel + " " + nick "\r\n")                                         // 341
#define RPL_SUMMONING (user)(user + " :Summoning user to IRC\r\n")                                        // 342
#define RPL_INVITELIST (channel, invitemask)(channel + " " + invitemask + "\r\n")                         // 346
#define RPL_ENDOFINTIELIST (channel)(channel + " :End of channel invite list\r\n")                        // 347
#define RPL_EXCEPTLIST (channel, exceptionmask)(channel + " " + exceptionmask + "\r\n")                   // 348
#define RPL_ENDOFEXCEPTLIST (channel)(channel + " :End of channel exception list\r\n")                    // 349
#define RPL_VERSION                                                                                       // 351
#define RPL_WHOREPLY                                                                                      // 352
#define RPL_ENDOFWHO q                                                                                    // 315
#define RPL_NAMREPLY                                                                                      // 353
#define RPL_ENDOFNAMES                                                                                    // 366
#define RPL_LINKS                                                                                         // 364
#define RPL_ENDOFLINKS                                                                                    // 365
#define RPL_BANLIST                                                                                       // 367
#define RPL_ENDOFBANLIST                                                                                  // 368
#define RPL_INFO                                                                                          // 371
#define RPL_ENDOFINFO                                                                                     // 374
#define RPL_MOTDSTART                                                                                     // 375
#define RPL_MOTD                                                                                          // 372
#define RPL_ENDOFMOTD                                                                                     // 376
#define RPL_YOUREOPER                                                                                     // 381
#define RPL_REHASHING                                                                                     // 382
#define RPL_TIME                                                                                          // 391
#define RPL_USERSSTART                                                                                    // 392
#define RPL_USERS                                                                                         // 393
#define RPL_ENDOFUSERS                                                                                    // 394
#define RPL_NOUSERS                                                                                       // 395
#define RPL_TRACELINK                                                                                     // 200
#define RPL_TRACECONNECTING                                                                               // 201
#define RPL_TRACEHANDSHAKE                                                                                // 202
#define RPL_TRACEUNKNOWN                                                                                  // 203
#define RPL_TRACEOPERATOR                                                                                 // 204
#define RPL_TRACEUSER                                                                                     // 205
#define RPL_TRACESERVER                                                                                   // 206
#define RPL_TRACENEWTYPE                                                                                  // 208
#define RPL_TRACELOG                                                                                      // 261
#define RPL_STATSLINKINFO                                                                                 // 211
#define RPL_STATSCOMMANDS                                                                                 // 212
//#define RPL_STATSCLINE      // 213
//#define RPL_STATSNLINE      // 214
//#define RPL_STATSILINE      // 215
//#define RPL_STATSKLINE      // 216
//#define RPL_STATSQLINE      // 217
//#define RPL_STATSYLINE      // 218
#define RPL_ENDOFSTATS // 219
//#define RPL_STATSVLINE    // 240
//#define RPL_STATSLLINE    // 241
#define RPL_STATSUPTIME // 242
#define RPL_STATSOLINE  // 243
//#define RPL_STATSHLINE    // 244
#define RPL_UMODEIS       // 221
#define RPL_LUSERCLIENT   // 251
#define RPL_LUSEROP       // 252
#define RPL_LUSERUNKNOWN  // 253
#define RPL_LUSERCHANNELS // 254
#define RPL_LUSERME       // 255
#define RPL_ADMINME       // 256
#define RPL_ADMINLOC1     // 257
#define RPL_ADMINLOC2     // 258
#define RPL_ADMINEMAIL    // 259

#endif // !REPLIES_HPP
