#include <IRC.hpp>

Commands::Commands() : _cmds(_initCmds())
{
#if DEBUG
	std::cout << BLUE << "DEBUG: Commands constructor called" << NC << std::endl;
#endif
};

Commands::~Commands()
{
#if DEBUG
	std::cout << BLUE << "DEBUG: Command destructor called" << NC << std::endl;
#endif
}

std::map<std::string, void (*)(User *, IRC *)> Commands::get_cmds(void) const
{
	std::map<std::string, void (*)(User *, IRC *)> cmds = this->_cmds;
	return (cmds);
}

std::map<std::string, void (*)(User *, IRC *)> Commands::_initCmds()
{
	std::map<std::string, void (*)(User *, IRC *)> cmds;

	cmds.insert(std::pair<std::string, void (*)(User *, IRC *)>("TIME", time_cmd));
	cmds.insert(std::pair<std::string, void (*)(User *, IRC *)>("WELCOME", welcome_cmd));
	cmds.insert(std::pair<std::string, void (*)(User *, IRC *)>("MOTD", motd_cmd));
	cmds.insert(std::pair<std::string, void (*)(User *, IRC *)>("VERSION", version_cmd));
	cmds.insert(std::pair<std::string, void (*)(User *, IRC *)>("QUIT", quit_cmd));
	cmds.insert(std::pair<std::string, void (*)(User *, IRC *)>("PING", ping_cmd));
	cmds.insert(std::pair<std::string, void (*)(User *, IRC *)>("CAP", cap_cmd));
	cmds.insert(std::pair<std::string, void (*)(User *, IRC *)>("NICK", nick_cmd));
	cmds.insert(std::pair<std::string, void (*)(User *, IRC *)>("USER", user_cmd));
	cmds.insert(std::pair<std::string, void (*)(User *, IRC *)>("MODE", mode));
	cmds.insert(std::pair<std::string, void (*)(User *, IRC *)>("JOIN", join));
	cmds.insert(std::pair<std::string, void (*)(User *, IRC *)>("INVITE", invite));
	cmds.insert(std::pair<std::string, void (*)(User *, IRC *)>("KICK", kick));
	cmds.insert(std::pair<std::string, void (*)(User *, IRC *)>("LIST", list));
	cmds.insert(std::pair<std::string, void (*)(User *, IRC *)>("MODE", mode));
	cmds.insert(std::pair<std::string, void (*)(User *, IRC *)>("NAMES", names));
	cmds.insert(std::pair<std::string, void (*)(User *, IRC *)>("PART", part));
	cmds.insert(std::pair<std::string, void (*)(User *, IRC *)>("TOPIC", topic));
	cmds.insert(std::pair<std::string, void (*)(User *, IRC *)>("PASS", pass));
	cmds.insert(std::pair<std::string, void (*)(User *, IRC *)>("PRIVMSG", privmsg));
	return cmds;
}

std::vector<std::string> Commands::store_second_param_message(std::vector<std::string> params)
{
	std::vector<std::string> message;
	std::vector<std::string>::iterator it = params.begin();
	it++;
	std::vector<std::string>::iterator ite = params.end();
	while (it != ite)
	{
		message.push_back(*it);
		it++;
	}
	return (message);
}

bool Commands::prefixed_by_colon(std::string str)
{
	if (str[0] == ':')
		return (true);
	return (false);
}

//Attention similaire a la meme sur channel
std::string	Commands::get_channel_key(Channel *channel)
{
	if (!channel)
		return ("");
	std::string key = channel->get_key();
	#if DEBUG
		std::cout << "DEBUG: " << "COMMAND :" << "The correct channel key is " << key << std::endl;
	#endif
	return (key);
}

std::vector<std::string> Commands::get_channel_targets(User *user, IRC *server)
{
	(void)user;
	(void)server;
	std::vector<std::string> params = user->get_params();
	std::vector<std::string> targets = ft_split(params[0], ",");
	return (targets);
}

std::vector<std::string>	Commands::get_key_targets(User *user, IRC *server)
{
	(void)user;
	(void)server;
	std::vector<std::string> params = user->get_params();
	std::vector<std::string> targets = ft_split(params[1], ",");
	return (targets);
}