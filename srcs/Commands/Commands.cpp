#include <IRC.hpp>

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
	cmds.insert(std::pair<std::string, void (*)(User *, IRC *)>("VERSION", version_cmd));
	cmds.insert(std::pair<std::string, void (*)(User *, IRC *)>("PING", ping_cmd));
	cmds.insert(std::pair<std::string, void (*)(User *, IRC *)>("CAP", cap_cmd));
	cmds.insert(std::pair<std::string, void (*)(User *, IRC *)>("NICK", nick_cmd));
	cmds.insert(std::pair<std::string, void (*)(User *, IRC *)>("USER", user_cmd));
	cmds.insert(std::pair<std::string, void (*)(User *, IRC *)>("MODE", mode));
	cmds.insert(std::pair<std::string, void (*)(User *, IRC *)>("JOIN", join));
	cmds.insert(std::pair<std::string, void (*)(User *, IRC *)>("INVITE", invite));
	cmds.insert(std::pair<std::string, void (*)(User *, IRC *)>("KICK", kick));
	cmds.insert(std::pair<std::string, void (*)(User *, IRC *)>("LIST", list));
	cmds.insert(std::pair<std::string, void (*)(User *, IRC *)>("MODE", names));
	cmds.insert(std::pair<std::string, void (*)(User *, IRC *)>("NAMES", list));
	cmds.insert(std::pair<std::string, void (*)(User *, IRC *)>("PART", list));
	cmds.insert(std::pair<std::string, void (*)(User *, IRC *)>("TOPIC", list));
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

//TODO: similaire au error_handler ? A mettre en commmun?
void											Commands::send_rpl(std::string error_code, User *user, Channel *channel, std::string arg)
{
	unsigned int code;

	(void)channel;
	code = atoi(error_code.c_str());
	std::string rpl;
	switch (code)
	{
		case 1:
		{
			rpl += "Welcome to the Internet Relay Network " + user->get_nickname() + "\r\n";
			break;
		}
		case 2:
		{
			rpl += "Your host is " + user->get_server_name() + ", running on version [1]\r\n";
			break;
		}
		case 3:
		{
			rpl += "This server was created " + user->get_server()->get_server_creation() + "\r\n";
			break;
		}
		case 4:
		{
			rpl += user->get_server_name() + " version [1]. Available user MODE : +Oa . Avalaible channel MODE : none. \r\n";
			break;
		}
		case 5:
		{
			rpl +="Sorry IRC's capacity is full. Please retry connection later\r\n";
			break;
		}
		case 221: //RPL_UMODEIS
		{
			if (user->user_is_operator() == false || user->user_is_away())
				rpl += user->get_nickname() + " :no mode set";
			else
				rpl += user->get_nickname() + " :active mode +";
			if (user->user_is_away() == true)
				rpl += "a";
			if (user->user_is_away() == true)
				rpl += "O";
			rpl +="\r\n";
			break;
		}
		case 301: //RPL_AWAY
		{
			rpl += (arg + "\r\n");
			break;
		}
		case 305: //RPL_UNAWAY
		{
			rpl += "You are no longer marked as being away\r\n";
			break;
		}
		case 306: //RPL_NOWAWAY
		{
			rpl += "You have been marked as being away\r\n" ;
			break;
		}
		case 315: //RPL_ENDWHO
		{
			if (arg.empty())
				rpl += user->get_server_name();
			else
				rpl += arg;
			rpl += " :End of WHO list\r\n" ;
			break ;
		}
		case 322: //RPL_LIST
		{
			rpl += (user->get_server_name() + " :" + channel->get_topic() + "\r\n");
			break;
		}
		case 323: //RPL_LISTEND
		{
			rpl += " :End of LIST\r\n";
			break;
		}
		case 331: //RPL_NOTOPIC
		{
			rpl += (channel->get_name() + " :No topic is set\r\n");
			break;
		}
		case 332: //RPL_TOPIC
		{
			rpl +=(channel->get_name() + " :" + channel->get_topic() + "\r\n");
			break;
		}
		//TODO: a tester
		case 341:
		{
			rpl = init_rpl(user);
			rpl += channel->get_name();
			rpl += " " + user->get_nickname();
			rpl += "\r\n";
			break;
		}
		case 352: //RPL_WHO
		{
			rpl = ":127.0.0.1 " + error_code + " " + user->get_nickname() + " ";
			rpl += arg;
			break;
		}
		case 353: // RPL_NAMEREPLY
		{
			rpl = ":127.0.0.1 " + error_code + " " +  user->get_nickname();
			rpl += (" = " + channel->get_name() + " :");
			std::vector<User *> tmp = channel->get_members();
			std::vector<User *>::iterator it = tmp.begin();
			std::vector<User *>::iterator ite = tmp.end();
			while (it != ite)
			{
				if (channel->user_is_operator(*it) == 1)
					rpl += "@";
				rpl += ((*it)->get_nickname() + " ");
				it++;
			}
			rpl +=  "\r\n";
			//std::cout << "rpl: |" << rpl << "|" << std::endl;
			break;
		}
		case 366: // ENDOFNAMES
		{
			rpl = ":127.0.0.1 " + error_code + " " +  user->get_nickname() + " ";
			if (channel)
				rpl += channel->get_name();
			else
				rpl += arg;
			rpl += " :End of NAMES list\r\n";
			break;
		}
		case 375:
		{
			rpl += ":- " + user->get_server_name() + " Message of the day - \r\n";
			break;
		}
		case 376:
		{
			rpl += ":End of MOTD command\r\n";
			break;
		}
		case 381: // YOUREOPER
		{
			rpl += "You are now an IRC operator\r\n";
			break;
		}
		case 4242:
		{
			rpl += ":" + user->get_server_name() + " " + error_code + " " + user->get_nickname() + " :";
			rpl = "[CAP] : IRC_90'S does not handle capabilities\r\n";
			break;
		}
		case 4243:
		{
			rpl += user->get_nickname() + ": sets mode " + arg + " on " + user->get_nickname() + "\r\n";
			break;
		}
		case 4244: // customhelp
		{
			// Liste des commandes dispo sur notre IRC
			rpl += "Available commands:\n";
			rpl += "---> Globales: NICK | OPER | MODE | WHO | AWAY | HELP | KILL | QUIT \n";
			rpl += "---> On Channels: JOIN | PART | TOPIC | NAMES | LIST | KICK\n";
			rpl += "---> To send messages: PRIVMSG | NOTICE";
			rpl += "\r\n";
			break;
		}
		case 4245:
		{
			rpl += arg + "\r\n";
			break;
		}
		default:
		{
			rpl = "No RPL set \r\n";
			break;
		}
	}
	//Envoie du message a la queue du serveur
	user->get_server()->_response_queue.push_back(std::make_pair(user->get_socket(), rpl));
	return ;
}

std::vector<std::string>			Commands::store_second_param_message(std::vector<std::string> params)
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

bool								Commands::prefixed_by_colon(std::string str)
{
	if (str[0] == ':')
		return (true);
	return (false);
}
