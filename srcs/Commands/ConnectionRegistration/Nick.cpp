#include <IRC.hpp>
#include <algorithm>

bool Commands::nickIsAvailable(std::string nickname, IRC *server, User *user)
{
	(void)user;

	//Capitalizer pour etre sensible a la casse
	std::string str(nickname);
	std::transform(str.begin(), str.end(), str.begin(), ::toupper);

	//Faire le tour des user et voir si leur nickname correspond
	std::vector<User *> users = server->get_users();
	std::vector<User *>::iterator it = users.begin();
	std::vector<User *>::iterator ite = users.end();
	std::string cmp;
	while (it != ite)
	{
		cmp = (*it)->get_nickname();
		std::transform(cmp.begin(), cmp.end(), cmp.begin(), ::toupper);
		if (cmp.compare(str) == 0)
		{
#if DEBUG
			std::cout << "There must be a nickname collision." << std::endl;
			std::cout << str << " is should be the same as " << cmp << std::endl;
#endif
			return (false);
		}
		it++;
	}
	return (true);
}

bool Commands::checkNickGrammar(std::string nickname, IRC *server, User *user)
{
	(void)server;
	(void)user;

	int i = 0;
	int length = nickname.length();

	//Preparation du vector qu'on envoie en cas d'erreur
	std::vector<std::string> param_error;
	//TODO: build reply
	//param_error.push_back(nickname);

	//La taille du nick ne doit pas depasser 9 idealement
	if (length > 9)
	{
#if DEBUG
		std::cout << "Nickname size is too big and should be avoided." << std::endl;
#endif
		//TODO: build reply
		//error_handler("432", user, NULL, param_error);
		return (false);
	}
	while (i < length)
	{
		if (!std::strchr(NICK_VALID_CHARS, nickname[i]))
		{
#if DEBUG
			std::cout << "Found special char that should be avoided." << std::endl;
#endif
			//TODO: build reply
			//error_handler("432", user, NULL, param_error);
			return (false);
		}
		i++;
	}
	//Le premier caractere doit etre un alpha (a retester)
	if (!isalpha(nickname[0]))
	{
#if DEBUG
		std::cout << "The nickname does not start with an alpha and that should be avoided." << std::endl;
#endif
		//TODO: build reply
		//error_handler("432", user, NULL, param_error);
		return (false);
	}

	return true;
}

void Commands::nick_cmd(User *user, IRC *server)
{
#if DEBUG
	std::cout << RED << "ENTER NICK CMD " << NC << std::endl;
#endif

	std::vector<std::string> params;
	// check if nick given
	if (user->get_params_size() != 1)
	{
		params.push_back(user->get_command_name());
		server->send_rpl("431", user, params, ""); //ERR_NONICKNAMEGIVEN
		return;
	}
	//check if nick is valid
	std::string nick = user->get_params().front();
	if (checkNickGrammar(nick, server, user) == false)
	{
		params.push_back(nick);
		server->send_rpl("432", user, params, ""); //ERR_ERRONEOUSNICKNAME
		return;
	}
	//check nick collision
	if (nickIsAvailable(nick, server, user) == false)
	{
		params.push_back(user->get_params().front());
		//TODO check if serv has to sent error code or command name
		server->send_rpl("433", user, params, "");
		return;
	}

	user->set_nickname(nick);

	if (!user->get_realname().empty() && !user->get_hostname().empty() && !user->get_username().empty()) //lier au cas dans user.cpp ligne33
		user->is_registered(true);
#if DEBUG
	std::cout << RED << "EXIT NICK CMD " << NC << std::endl;
#endif
}