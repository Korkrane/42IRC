#pragma once

#include <IRC.hpp>

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
	std::map<std::string, void (*)(User *, IRC *)>	get_cmds(void) const;
	std::map<std::string, void (*)(User *, IRC *)>	_initCmds();

	static void										unknown_cmd(User *user, IRC *server);
	static void 									motd_cmd(User *user, IRC *server);
	static void 									welcome_cmd(User *user, IRC *server);
	static void 									time_cmd(User *user, IRC *server);
	static void 									cap_cmd(User *user, IRC *server);
	static void 									user_cmd(User *user, IRC *server);

	static void 									quit_cmd(User *user, IRC *server);
	static void        								send_quit_message(User *user, IRC *server, std::string message);

	static void 									away_cmd(User *user, IRC *server);
	static void 									version_cmd(User *user, IRC *server);
	static void 									ping_cmd(User *user, IRC *server);
	static void 									pass(User *user, IRC *server);

	static void										notice(User *user, IRC *server);
	static void         							send_full_notice(User *target, User *user, IRC *server, std::vector<std::string> message);

	static void 									kill(User *user, IRC *server);
	static void 									who(User *user, IRC *server);
	static void 									oper(User *user, IRC *server);

	static void 									displayAllClients(Channel *channel);
	static void 									displayChannel(Channel *channel, User *client);
	static void										displayClientsFromChannel(Channel *channel, User *client);
	static void										paramsIsCorrectChannel(Commands *command, IRC *server);
	static void 									paramsIsCorrectOther(Commands *command, IRC *server);
	static std::string								whoHelpParameter(void);

	static std::string								init_rpl(User *user);
	static void										send_rpl_to_all_members(Channel *channel, std::string rpl);
	static void										send_rpl(std::string rpl, User *user, Channel *channel, std::string arg);

	static void 									join(User *user, IRC *server);
	static void										send_join_message(Channel *channel, User *user, std::vector<std::string> message);

	static void 									nick_cmd(User *user, IRC *server);
	static bool										checkNickGrammar(std::string nick, IRC *server, User *user);
	static bool										nickIsAvailable(std::string nick, IRC *server, User *user);
	static void										part(User *user,IRC *server);
	static void										send_part_message(Channel *channel, User *user, std::vector<std::string> message);

	static void										mode(User *user, IRC *server);
	static void										edit_modes(Channel *channel, User *user, std::string modes, std::string key, IRC *server);
	static bool										should_add_mode(std::string modes);
	static bool										should_remove_mode(std::string modes);
	static void										handle_key(Channel *channel, User *user, std::string modes, std::string key, bool add);

	static void 									kick(User *client, IRC *server);
	static void        								send_kick_message(Channel *channel, User *user, IRC *server, std::vector<std::string> comment);

	static void										topic(User *client, IRC *server);
	static void										check_topic(Channel *channel, User *user, IRC *server);
	static void										send_topic_message(Channel *channel, User *user, std::vector<std::string> message);

	static void										list(User *client, IRC *server);

	static void										invite(User *user, IRC *server);
	static User 									*find_target_nick(std::string target_nick, User *user, IRC *server);
	static Channel									*find_target_channel(std::string target_channel, User *user, IRC *server);

	static void 									names(User *user, IRC *server);
	static void										send_names_message(Channel *channel, User *user, IRC *server);

	static void										privmsg(User *user, IRC *server);
	static std::vector<std::string>					store_second_param_message(std::vector<std::string> params);
	static bool										prefixed_by_colon(std::string str);
	static void                						send_full_privmsg(User *target, User *user, IRC *server, std::vector<std::string>message);
	static void                						send_one_word_privmsg(User *target, User *user, IRC *server, std::string message);
};