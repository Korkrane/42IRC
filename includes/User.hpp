#pragma once

#include <IRC.hpp>

class IRC;
class Channel;

struct t_cmd
{
	std::string _unparsed;
	std::string _prefix;
	std::string _command;
	std::vector<std::string> _params;
};

class User
{
private:
	User(User const &src);
	User &operator=(User const &src);

	int _fd;
	std::string _nickname;
	std::string _username;
	std::string _hostname;
	std::string _realname;
	std::string _modes;
	std::string _away_mssg;
	std::string _password;
	std::string _message;
	std::vector<Channel *> _channels;
	unsigned int _channels_nb;

	bool _is_oper;
	bool _is_away;
	bool _user_has_registered_pass;
	bool _user_has_registered_nick;
	bool _is_registered;

	std::string _request;
	std::string _prefix;
	std::string _command;

public:
	User(void);
	User(int fd);
	virtual ~User();

	/*** VARIABLES ***/
	std::vector<std::string> _params;
	std::vector<std::string> _splitted_channels; //A clear a chaque commande comme le parsint
	std::vector<std::string> _splitted_args;
	std::vector<t_cmd> _commands;
	bool _to_delete;

	/*** GETTERS ***/
	std::string get_nickname(void) const;
	std::string get_username(void) const;
	std::string get_realname(void) const;
	std::string get_hostname(void) const;
	std::string get_modes(void) const;
	std::string get_away_mssg(void) const;
	std::string get_password(void) const;
	std::string get_message(void) const;
	int get_channels_nb(void) const;
	int get_fd(void) const;

	std::string get_request(void) const;
	std::vector<std::string> get_params(void) const;
	std::string get_command_name(void) const;
	std::string get_prefix(void) const;
	unsigned int get_params_size(void) const;

	bool is_registered(void) const;
	bool user_registered_password(void) const;
	bool user_registered_nickname(void) const;
	bool is_away(void) const;
	bool is_operator(void) const;
	std::vector<std::string> user_commands(void) const;

	/*** SETTERS ***/
	void set_fd(int fd);
	void set_nickname(std::string nickname);
	void set_username(std::string username);
	void set_realname(std::string realname);
	void set_hostname(std::string hostname);
	void set_modes(std::string modes);

	void is_registered(bool value);
	void is_operator(bool value);
	void is_away(bool value);

	void set_request(std::string request);
	void set_prefix(std::string);
	void set_command(std::string);
	void set_params(std::vector<std::string>);

	void set_password_as_registered(bool value);
	void set_registered_nickname(bool value);
	void set_away_mssg(std::string message);

	/*** METHODS ***/
	int store_string_until_char(std::string *dest, std::string *src, char c, int len); //TODO faire un namespace utils
	void patch_params(std::vector<std::string> *params);
	void split_string_to_vector(std::vector<std::string> *vec, std::string *str, char c); //TODO faire un namespace utils
	bool string_end_with(std::string const &fullString, std::string const &ending);		  //TODO faire un namespace

	void store_prefix(void);
	void store_command(void);
	void store_params(void);
	void store_prefix(std::vector<t_cmd>::iterator it);
	void store_command(std::vector<t_cmd>::iterator it);
	void store_params(std::vector<t_cmd>::iterator it);

	void be_added_to_channel(Channel *chan);
	void decrease_channel_nb();
	void increase_channel_nb();
	void add_channel_to_list(Channel *channel);
	void remove_channel_from_list(Channel *channel);

	void split_if_multiple_command();
	unsigned int count_commas(void) const;

	void ft_split_channels(std::string line, char charset);
	void ft_split_args(std::string line, char charset);

	/*** DEBUG ***/
	void display_client_info(void);
	void display_channels(void);
	void display_command(void);
	void display_params(void);
	void display_params_bis(void);
};

std::ostream &operator<<(std::ostream &COUT, User *user);