
#include <IRC.hpp>

void Commands::kick(User *user, IRC *server)
{
	std::vector<std::string> params;
	std::vector<std::string> reply_params;

	params = user->get_params();

	if (params.size() <= 2)
	{
		reply_params.push_back(user->get_command_name());
		server->send_rpl("461", user, reply_params, "");
		return;
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

	for (std::vector<Channel *>::iterator it = chans.begin(); it != chans.end(); it++)
	{
		if ((*it))
		{
			if ((*it)->user_is_member(user) == false) //ERR_NOTONCHANNEL
			{
				reply_params.push_back((*it)->get_name());
				server->send_rpl("442", user, reply_params, "");
				reply_params.clear();
				chans_i++;
				continue;
			}
			else if ((*it)->user_is_member(user) == true && (*it)->user_is_operator(user) == false) //ERR_CHANOPRIVSNEEDED
			{
				reply_params.push_back((*it)->get_name());
				server->send_rpl("482", user, reply_params, "");
				reply_params.clear();
				chans_i++;
				continue;
			}
			int user_i = 0;
			for (std::vector<User *>::iterator it2 = targets.begin(); it2 != targets.end(); it2++)
			{
				if (!(*it2)) //ERR_NOSUCHNICK
				{
					reply_params.push_back(targets_name[user_i]);
					server->send_rpl("401", user, reply_params, "");
					reply_params.clear();
				}
				else if ((*it)->user_is_member((*it2)) == false) //ERR_USERNOTINCHANNEL
				{
					reply_params.push_back((*it2)->get_nickname());
					reply_params.push_back((*it)->get_name());
					server->send_rpl("441", user, reply_params, "");
					reply_params.clear();
				}
				else //VALID REQUEST
				{
					//has duplicate code in IRC l.155
					//query modif results
					//delete in members vector channel
					(*it)->deleteMember(user);
					//delete in operators vector channel
					if ((*it)->user_is_operator(user))
					{
						(*it)->delete_operator(user);
						// TODO add new operator randomly if it was the only operator in the chan
					}
					//delete in owner if he it was him
					if ((*it)->user_is_owner(user))
						(*it)->delete_owner();
					(*it2)->remove_channel_from_list((*it));

					//reply
					reply_params.push_back(user->get_nickname());
					reply_params.push_back(user->get_username());
					reply_params.push_back(user->get_hostname());
					reply_params.push_back((*it)->get_name());
					reply_params.push_back((*it2)->get_nickname());
					if (params.size() == 3)
						reply_params.push_back(params[2]);
					else
						reply_params.push_back(":" + user->get_nickname());
					server->send_rpl_to_all_members("", (*it)->get_members(), reply_params, "KICK");
					reply_params.clear();

					//TODO if channel become empty delete it (chanop kick himself)
					/*
					if ((*it)->get_members_nb() == 0)
						server->drop_channel((*it));
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