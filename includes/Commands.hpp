#pragma once

#include <IRC.hpp>

class Channel;
class User;
class IRC;

class Commands
{
private:
	Commands(Commands const &src);
	Commands &operator=(Commands const &src);

public:
	Commands();
	virtual ~Commands();
	std::map<std::string, void (*)(User *, IRC *)> _cmds;

	/*** FUNCTIONS ***/
	std::map<std::string, void (*)(User *, IRC *)> get_cmds(void) const;
	std::map<std::string, void (*)(User *, IRC *)> _initCmds();

	static void unknown_cmd(User *user, IRC *server);
	static void motd_cmd(User *user, IRC *server);
	static void welcome_cmd(User *user, IRC *server);
	static void time_cmd(User *user, IRC *server);
	static void cap_cmd(User *user, IRC *server);
	static void user_cmd(User *user, IRC *server);
	static void quit_cmd(User *user, IRC *server);
	static void ping_cmd(User *user, IRC *server);
	static void away_cmd(User *user, IRC *server);
	static void version_cmd(User *user, IRC *server);
	static void pass(User *user, IRC *server);
	static void kill(User *user, IRC *server);

	static void who(User *user, IRC *server);
	static int who_match_user(User *user, IRC *server);

	static void oper(User *user, IRC *server);
	static void die(User *user, IRC *server);

	static void notice(User *user, IRC *server);
	static void send_full_notice(User *target, User *user, IRC *server, std::vector<std::string> message);

	static void displayAllClients(Channel *channel);
	static void displayChannel(Channel *channel, User *client);
	static void displayClientsFromChannel(Channel *channel, User *client);
	static void paramsIsCorrectChannel(Commands *command, IRC *server);
	static void paramsIsCorrectOther(Commands *command, IRC *server);
	void displayMode(void) const;

	static void join(User *user, IRC *server);
	static void loop_join(User *user, IRC *server, unsigned int index);
	static void check_roles(Channel *chan, User *user, bool added);
	static void user_joins(User *user, IRC *server, Channel *chan, int index);
	static void user_parts(User *user, IRC *server, Channel *chan, int index, std::string bye_message);

	static void nick_cmd(User *user, IRC *server);
	static bool checkNickGrammar(std::string nick, IRC *server, User *user);
	static bool nickIsAvailable(std::string nick, IRC *server, User *user);

	static void part(User *user, IRC *server);
	static void loop_part(User *user, IRC *server, std::string bye_message, unsigned int index);
	static void send_part_message(Channel *channel, User *user, std::vector<std::string> message, IRC *server);
	static std::string get_bye_message(User *user, IRC *server);

	static void mode(User *user, IRC *server);
	static void mode_channel(User *user, IRC *s_messerver);
	static void mode_user(User *user, IRC *server);
	static void modif_user(User *user, IRC *server, std::string modifications);

	static void handle_key(Channel *channel, User *user, std::string modes, std::string key, bool add);

	static void kick(User *client, IRC *server);

	static void send_topic_message(User *user, Channel *chan, IRC *server, bool same_args);
	static void topic(User *client, IRC *server);
	static bool same_arguments(User *user, IRC *server);

	static void check_topic(Channel *channel, User *user, IRC *server);

	static void list(User *client, IRC *server);

	static void invite(User *user, IRC *server);
	static User *find_target_nick(std::string target_nick, User *user, IRC *server);
	static Channel *find_target_channel(std::string target_channel, User *user, IRC *server);

	static void names(User *user, IRC *server);
	static void send_members_nick(User *user, IRC *server);

	static void privmsg(User *user, IRC *server);
	static std::vector<std::string> fill_recipients(std::string targets);

	static bool should_ignore_key(Channel *channel, std::vector<std::string> params);
	static std::string get_channel_key(Channel *channel);

	static void get_channel_targets(User *user, IRC *server);
	static void get_key_targets(User *user, IRC *server);

	static void return_error(std::string error_code, User *user, IRC *server, std::vector<std::string> error, std::string arg);
};