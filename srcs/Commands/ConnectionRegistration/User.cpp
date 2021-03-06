#include <IRC.hpp>

void Commands::user_cmd(User *user, IRC *server)
{
#if DEBUG
	std::cout << RED << "ENTER ENTER USER CMD" << NC << std::endl;
#endif

	std::vector<std::string> params;

	if (user->is_registered() == true)
	{
		server->send_rpl("462", user, params, "");
		return;
	}
	else if (user->get_params_size() < 4)
	{
#if DEBUG
		std::cout << RED << "DEBUG: NOT ENOUGH PARAMS IN USER COMMAND" << NC << std::endl;
#endif
		params.push_back(user->get_command_name());
		server->send_rpl("461", user, params, "");
		return;
	}
	else
	{
#if DEBUG
		std::cout << PURPLE << "DEBUG: SUCCESS USER COMMAND" << NC << std::endl;
#endif
		user->set_username(user->get_params()[0]);
		user->set_hostname(user->get_params()[2]);
		user->set_realname(user->get_params()[3]);
		if (!user->get_nickname().empty()) //dans le cas ou pas de nick a la connection il devra refaire un /nick valide
			user->is_registered(true);
	}
#if DEBUG
	std::cout << RED << "EXIT USER CMD " << NC << std::endl;
#endif
}
