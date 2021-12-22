#include <IRC.hpp>

Commands::Commands() : _cmds(_initCmds()){};

Commands::~Commands()
{
}

std::map<std::string, void (*)(User *, IRC *)> Commands::get_cmds(void) const
{
	return _cmds;
}

std::map<std::string, void (*)(User *, IRC *)> Commands::_initCmds()
{
	std::map<std::string, void (*)(User *, IRC *)> cmds;

	cmds.insert(std::pair<std::string, void (*)(User *, IRC *)>("TIME", time_cmd));
	cmds.insert(std::pair<std::string, void (*)(User *, IRC *)>("AWAY", away_cmd));
	cmds.insert(std::pair<std::string, void (*)(User *, IRC *)>("WELCOME", welcome_cmd));
	cmds.insert(std::pair<std::string, void (*)(User *, IRC *)>("MOTD", motd_cmd));
	cmds.insert(std::pair<std::string, void (*)(User *, IRC *)>("VERSION", version_cmd));
	cmds.insert(std::pair<std::string, void (*)(User *, IRC *)>("QUIT", quit_cmd));
	cmds.insert(std::pair<std::string, void (*)(User *, IRC *)>("PING", ping_cmd));
	cmds.insert(std::pair<std::string, void (*)(User *, IRC *)>("CAP", cap_cmd));
	cmds.insert(std::pair<std::string, void (*)(User *, IRC *)>("NICK", nick_cmd));
	cmds.insert(std::pair<std::string, void (*)(User *, IRC *)>("USER", user_cmd));
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
	cmds.insert(std::pair<std::string, void (*)(User *, IRC *)>("OPER", oper));
	cmds.insert(std::pair<std::string, void (*)(User *, IRC *)>("KILL", kill));
	//cmds.insert(std::pair<std::string, void (*)(User *, IRC *)>("DIE", die));
	cmds.insert(std::pair<std::string, void (*)(User *, IRC *)>("NOTICE", notice));
	cmds.insert(std::pair<std::string, void (*)(User *, IRC *)>("WHO", who));
	return cmds;
}

//Attention similaire a la meme sur channel
std::string Commands::get_channel_key(Channel *channel)
{
	if (!channel)
		return ("");
	std::string key = channel->get_key();
#if DEBUG
	std::cout << "DEBUG: COMMAND : The correct channel key is " << key << std::endl;
#endif
	return (key);
}

void Commands::get_channel_targets(User *user, IRC *server)
{
	(void)server;
	std::vector<std::string> params = user->get_params();

	if (params.size() >= 1)
		user->ft_split_channels(params.front(), ',');
#if DEBUG == 1
	std::cout << "Params front is " << params.front() << std::endl;
#endif
}

//TODO remove server from proto
std::string Commands::get_bye_message(User *user, IRC *server)
{
	(void)server;

	//tous les mots qui viennent apres le premier font partie de la string
	std::string bye_message = "";
	std::vector<std::string> params = user->get_params();
	unsigned int size = params.size();
	if (size == 0)
		return (bye_message);
	std::vector<std::string>::iterator it = params.begin();
	it++; //on skippe le premier mot
	std::vector<std::string>::iterator ite = params.end();
	while (it != ite)
	{
		bye_message += (*it);
		if (it + 1 == ite)
			break;
		bye_message += " ";
		it++;
	}
#if DEBUG == 1
	std::cout << "Bye message: " << bye_message << std::endl;
#endif
	return (bye_message);
}

//TODO remove server from proto
void Commands::get_key_targets(User *user, IRC *server)
{
	(void)server;
	std::vector<std::string> params = user->get_params();

	if (params.size() > 1)
		user->ft_split_args(params[1], ',');
}

void Commands::return_error(std::string error_code, User *user, IRC *server, std::vector<std::string> error, std::string arg)
{
	server->send_rpl(error_code, user, error, arg);
	user->_splitted_args.clear();
	user->_splitted_channels.clear();
	return;
}