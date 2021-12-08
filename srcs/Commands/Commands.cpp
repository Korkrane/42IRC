#include <irc.hpp>

Commands::Commands() : _cmds(_initCmds())
{
	#if DEBUG
		std::cout << BLUE <<  "DEBUG: Commands constructor called" << NC << std::endl;
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
	return cmds;
}

//Ajout Mahaut pour reutilisation dans les commandes
std::string										Commands::init_rpl(User *user)
{
	std::string rpl;
	rpl = ":" + user->get_nickname() + "!" + user->get_username() + "@" + "0";
	return rpl;
}

void											Commands::send_rpl_to_all_members(Channel *channel, std::string rpl)
{
	std::vector<User *> members = channel->get_members();
	std::vector<User *>::iterator it = members.begin();
	std::vector<User *>::iterator ite = members.end();
	User *user = (*it);
	IRC *server = user->get_server();
	while (it != ite)
	{
		//TODO: a tester
		server->_response_queue.push_back(std::make_pair(user->get_socket(), rpl));
		it++;
	}
	return ;
}