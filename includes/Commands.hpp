#pragma once

#include <irc.hpp>

class Channel;
class User;
class IRC;

class Commands
{
public:
	Commands();
	Commands(Commands const &src);
	Commands &operator=(Commands const &src);
	virtual ~Commands();
	std::map<std::string, void (*)(User *, IRC *)> _cmds;

	/*** METHODS ***/
	std::map<std::string, void (*)(User *, IRC *)> get_cmds(void) const;
	std::map<std::string, void (*)(User *, IRC *)> _initCmds();

	static void unknown_cmd(User *user, IRC *server);
	static void motd_cmd(User *user, IRC *server);
	static void 		welcome_cmd(User *user, IRC *server);

private:
	static void 		time_cmd(User *user, IRC *server);
	static void 		cap_cmd(User *user, IRC *server);
	static void 		user_cmd(User *user, IRC *server);
	static void 		away_cmd(User *user, IRC *server);
	static void 		version_cmd(User *user, IRC *server);
	static void 		ping_cmd(User *user, IRC *server);
	static void			notice(User *user, IRC *server);
	static void			privmsg(User *user, IRC *server);
	static void 		kill(User *user, IRC *server);
	static void 		who(User *user, IRC *server);

	static void 		displayAllClients(Channel *channel);
	static void 		displayChannel(Channel *channel, User *client);
	static void			displayClientsFromChannel(Channel *channel, User *client);
	static void			paramsIsCorrectChannel(Commands *command, IRC *server);
	static void 		paramsIsCorrectOther(Commands *command, IRC *server);
	static std::string	whoHelpParameter(void);

	/**
	 * @brief
	 *
	 * @param command
	 * @param client
	 * @param server
	 * Parameters: ( <channel> *( "," <channel> ) [ <key> *( "," <key> ) ] )
	 ** Is used by user to request to start listening to a specific channel.
	 ** Server "should not use lists when reading JOIN messages to clients".
	 ** Once a user has join a channel, he is aware when a command is affecting the server :
	 ** JOIN, MODE, KICK, PART, QUIT and PRIVMSG/NOTICE.
	 ** See details on RFC 2812.
	 */
	static void 			join(User *user, IRC *server);

	static void				channel(User *user, IRC *server);


	static void 			nick_cmd(User *user, IRC *server);
	static bool				checkNickGrammar(std::string nick, IRC *server, User *user);
	static bool				nickIsAvailable(std::string nick, IRC *server, User *user);

	/**
	 * @brief
	 *
	 * @param command
	 * @param client
	 * @param server
	* The PART command causes the user sending the message to be removed
	* from the list of active members for all given channels listed in the
	* parameter string.  If a "Part Message" is given, this will be sent
	* instead of the default message, the nickname.  This request is always
	* granted by the server.
	* Parameters: <channel> *( "," <channel> ) [ <Part Message> ]
	 */
	static void part(User *user,IRC *server);

	/**
	 * @brief
	 *
	 * @param client
	 * @param server
	 * The KICK command can be used to request the forced removal of a user
   	 * from a channel.  It causes the <user> to PART from the <channel> by
     * force.  For the message to be syntactically correct, there MUST be
	 * either one channel parameter and multiple user parameter, or as many
     * channel parameters as there are user parameters.  If a "comment" is
     * given, this will be sent instead of the default message, the nickname
     * of the user issuing the KICK.
	 * Parameters: <channel> *( "," <channel> ) <user> *( "," <user> )
               [<comment>]
	 */
	static void kick(User *client, IRC *server);

	/**
	 * @brief
	 *
	 * @param client
	 * @param server
	 * Parameters: <channel> [ <topic> ]
	 * The TOPIC command is used to change or view the topic of a channel.
     * The topic for channel <channel> is returned if there is no <topic>
     * given.  If the <topic> parameter is present, the topic for that
     * channel will be changed, if this action is allowed for the user
     * requesting it.  If the <topic> parameter is an empty string, the
     * topic for that channel will be removed.
	 */
	static void topic(User *client, IRC *server);

	/**
	 * @brief
	 *
	 * @param client
	 * @param server
	 * 	 * The list command is used to list channels and their topics.  If the
     * <channel> parameter is used, only the status of that channel is
     * displayed.

   	 * If the <target> parameter is specified, the request is forwarded to
     * that server which will generate the reply.
	 * Parameters: [ <channel> *( "," <channel> ) [ <target> ] ]
	 */
	static void list(User *client, IRC *server);

	/**
	 * @brief
	 *
	 * @param user
	 * @param server
	 */
	static void				invite(User *user, IRC *server);
	static User 			*find_target_nick(std::string target_nick, User *user, IRC *server);
	static Channel			*find_target_channel(std::string target_channel, User *user, IRC *server);
	/**
	 * @brief
	 *
	 * @param client
	 * @param server
	 * By using the NAMES command, a user can list all nicknames that are
     * visible to him. For more details on what is visible and what is not,
     * see "Internet Relay Chat: Channel Management" [IRC-CHAN].  The
     * <channel> parameter specifies which channel(s) to return information
     * about.  There is no error reply for bad channel names.

     * If no <channel> parameter is given, a list of all channels and their
     * occupants is returned.  At the end of this list, a list of users who
     * are visible but either not on any channel or not on a visible channel
     * are listed as being on `channel' "*".
	 * Parameters: [ <channel> *( "," <channel> ) [ <target> ] ]
	 */
	static void names(User *client, IRC *server);
};

/*
** Attention cas particulier :
** Note that this message accepts a special argument ("0"), which is
   a special request to leave all channels the user is currently a member
   of.  The server will process this message as if the user had sent
   a PART command (See Section 3.2.2) for each channel he is a member
   of.
*/