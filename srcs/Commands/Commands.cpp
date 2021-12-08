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