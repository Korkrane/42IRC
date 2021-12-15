#pragma once

#include <IRC.hpp>

class Channel;
class User;
class IRC;

class Commands
{
private:
	/* Ajout des protos pour que la classe soit canonique */
	Commands(Commands const &src);
	Commands &operator=(Commands const &src);
public:
	Commands();
	virtual ~Commands();
	//TODO: a mettre en prive et faire un getter setter
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

	static void notice(User *user, IRC *server);
	static void send_full_notice(User *target, User *user, IRC *server, std::vector<std::string> message);

	static void kill(User *user, IRC *server);
	static void who(User *user, IRC *server);
	static void oper(User *user, IRC *server);

	static void displayAllClients(Channel *channel);
	static void displayChannel(Channel *channel, User *client);
	static void displayClientsFromChannel(Channel *channel, User *client);
	static void paramsIsCorrectChannel(Commands *command, IRC *server);
	static void paramsIsCorrectOther(Commands *command, IRC *server);
	static std::string whoHelpParameter(void);
	void displayMode(void) const;

	static void join(User *user, IRC *server);
	static void	check_roles(Channel *chan, User *user, bool added);
	static void user_joins(User *user, IRC *server, Channel *chan, int index);


	static void nick_cmd(User *user, IRC *server);
	static bool checkNickGrammar(std::string nick, IRC *server, User *user);
	static bool nickIsAvailable(std::string nick, IRC *server, User *user);

	static void part(User *user, IRC *server);
	static void send_part_message(Channel *channel, User *user, std::vector<std::string> message, IRC *server);

	static void mode(User *user, IRC *server);
	static void mode_channel(User *user, IRC *server);
	static void modif_user(User *user, IRC *server, std::string modifications);
	static void mode_user(User *user, IRC *server);
	static void edit_modes(Channel *channel, User *user, std::string modes, std::string key, IRC *server);
	static bool should_add_mode(std::string modes);
	static bool should_remove_mode(std::string modes);
	static void handle_key(Channel *channel, User *user, std::string modes, std::string key, bool add);

	static void kick(User *client, IRC *server);
	static void send_kick_message(Channel *channel, User *user, IRC *server, std::vector<std::string> comment);

	static void topic(User *client, IRC *server);
	static void check_topic(Channel *channel, User *user, IRC *server);
	static void send_topic_message(Channel *channel, User *user, std::vector<std::string> message, IRC *server);

	static void list(User *client, IRC *server);

	static void invite(User *user, IRC *server);
	static User *find_target_nick(std::string target_nick, User *user, IRC *server);
	static Channel *find_target_channel(std::string target_channel, User *user, IRC *server);

	static void names(User *user, IRC *server);
	static void send_names_message(Channel *channel, User *user, IRC *server);

	static void privmsg(User *user, IRC *server);
	static std::vector<std::string> fill_recipients(std::string targets);
	static std::vector<std::string> store_second_param_message(std::vector<std::string> params);
	static bool prefixed_by_colon(std::string str);
	static void send_full_privmsg(User *target, User *user, IRC *server, std::vector<std::string> message);
	static void send_one_word_privmsg(User *target, User *user, IRC *server, std::string message);
	static bool should_ignore_key(Channel *channel, std::vector<std::string> params);

	static std::string get_channel_key(Channel *channel);

	static void get_channel_targets(User *user, IRC *server);
	static void get_key_targets(User *user, IRC *server);

	static void	return_error(std::string error_code, User *user, IRC *server, std::vector<std::string> error, std::string arg);
};