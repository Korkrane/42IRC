
#include <IRC.hpp>

void Commands::kick(User *user, IRC *server)
{
	std::vector<std::string> params;
	std::vector<std::string> reply_params;

	params = user->get_params();

	if (params.size() <= 2)
	{
		/*
		reply_params.push_back(user->get_command_name());
		server->send_rpl("461", user, reply_params, "");
		return;
		*/
		params.push_back(":");
	}

	//1. fills vector of chans to affect and users to kick
	std::vector<std::string> chans_name = old_ft_split(params[0], ",");
	std::vector<std::string> targets_name = old_ft_split(params[1], ",");
	std::vector<Channel *> chans;
	std::vector<User *> targets;

	for (std::vector<std::string>::iterator it = chans_name.begin(); it != chans_name.end(); it++)
		chans.push_back(server->get_channel_ptr((*it)));
	for (std::vector<std::string>::iterator it = targets_name.begin(); it != targets_name.end(); it++)
		targets.push_back(server->get_user_ptr((*it)));
	int chans_i = 0;

	for (std::vector<Channel *>::iterator chan = chans.begin(); chan != chans.end(); chan++)
	{
		if ((*chan))
		{
			if ((*chan)->user_is_member(user) == false) //ERR_NOTONCHANNEL
			{
				reply_params.push_back((*chan)->get_name());
				server->send_rpl("442", user, reply_params, "");
				reply_params.clear();
				chans_i++;
				continue;
			}
			else if ((*chan)->user_is_member(user) == true && (*chan)->user_is_operator(user) == false) //ERR_CHANOPRIVSNEEDED
			{
				reply_params.push_back((*chan)->get_name());
				server->send_rpl("482", user, reply_params, "");
				reply_params.clear();
				chans_i++;
				continue;
			}
			int user_i = 0;
			for (std::vector<User *>::iterator target_to_kick = targets.begin(); target_to_kick != targets.end(); target_to_kick++)
			{
				if (!(*target_to_kick)) //ERR_NOSUCHNICK
				{
					reply_params.push_back(targets_name[user_i]);
					server->send_rpl("401", user, reply_params, "");
					reply_params.clear();
				}
				else if ((*chan)->user_is_member((*target_to_kick)) == false) //ERR_USERNOTINCHANNEL
				{
					reply_params.push_back((*target_to_kick)->get_nickname());
					reply_params.push_back((*chan)->get_name());
					server->send_rpl("441", user, reply_params, "");
					reply_params.clear();
				}
				else //VALID REQUEST
				{
					//reply
					reply_params.push_back(user->get_nickname());
					reply_params.push_back(user->get_username());
					reply_params.push_back(user->get_hostname());
					reply_params.push_back((*chan)->get_name());
					reply_params.push_back((*target_to_kick)->get_nickname());
					if (params.size() == 3 && params[2].length() != 1)
						reply_params.push_back(params[2]);
					else
						reply_params.push_back(":" + user->get_nickname());
					server->send_rpl_to_all_members("", (*chan)->get_members(), reply_params, "KICK");
					reply_params.clear();

					//has duplicate code in IRC l.155
					//remove channel from target channel list
					(*target_to_kick)->remove_channel_from_list((*chan));
					//delete target in members from channel
					(*chan)->deleteMember((*target_to_kick));
					//delete target in operators from channel
					if ((*chan)->user_is_operator((*target_to_kick)))
					{
						(*chan)->delete_operator((*target_to_kick));
						// TODO add new operator randomly if it was the only operator in the chan
					}
					//delete target in owner from channel
					if ((*chan)->user_is_owner((*target_to_kick)))
						(*chan)->delete_owner();

					//TODO if channel become empty delete it (chanop kick himself)
					/*
					if ((*chan)->get_members_nb() == 0)
						server->drop_channel((*chan));
					*/
				}
				user_i++;
			}
		}
		else //ERR_NOSUCHCHANNEL
		{
			reply_params.push_back(chans_name[chans_i]);
			server->send_rpl("403", user, reply_params, "");
			reply_params.clear();
			chans_i++;
			continue;
		}
	}
}