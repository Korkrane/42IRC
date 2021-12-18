#include <IRC.hpp>

void Commands::invite(User *user, IRC *server)
{
	std::vector<std::string> params;
	std::vector<std::string> reply_params;

	params = user->get_params();
	//1. Verifier le nombre d'argument
	if (params.size() < 2)
	{
		reply_params.push_back(user->get_command_name());
		server->send_rpl("461", user, reply_params, "");
		return;
	}
	//2. Verifier si le nickname correspond bien a quelqu'un
	User *target_user = server->get_user_ptr(params[0]);
	if (!target_user)
	{
		reply_params.push_back(params[0]);
		server->send_rpl("401", user, reply_params, "");
		return;
	}
	//3. Verifier si le channel correspond bien a un channel
	Channel *chan = server->get_channel_ptr(params[1]);
	if (chan)
	{
		//4. Verifier que le user est lui meme member
		if (chan->user_is_member(user) == false) //NOTONCHANNEL
		{
			reply_params.push_back(params[1]);
			server->send_rpl("442", user, reply_params, "");
		}
		//5. Verifier que chan si invite-only, user has op privilege
		else if (chan->get_modes().find('i') != std::string::npos && !chan->user_is_operator(user))
		{
			reply_params.push_back(params[1]);
			server->send_rpl("482", user, reply_params, "");
		}
		//6. Verifier que celui qui invite n'est pas deja sur le channel
		else if (chan->user_is_member(target_user) == true)
		{
			reply_params.push_back(params[0]);
			reply_params.push_back(params[1]);
			server->send_rpl("443", user, reply_params, "");
		}
		else
		{
			reply_params.push_back(target_user->get_nickname());
			reply_params.push_back(chan->get_name());
			server->send_rpl("341", user, reply_params, "");
			reply_params.clear();
			if (chan->user_is_operator(user))
			{
				std::string message = ":" + user->get_nickname() + " invited " + target_user->get_nickname() + " into the channel.";
				reply_params.push_back(user->get_hostname());
				reply_params.push_back("@" + chan->get_name());
				reply_params.push_back(message);
				server->send_rpl("server", user, reply_params, "NOTICE");
				reply_params.clear();
			}
			reply_params.push_back(user->get_nickname());
			reply_params.push_back(user->get_username());
			reply_params.push_back(user->get_hostname());
			reply_params.push_back(target_user->get_nickname());
			reply_params.push_back(":" + chan->get_name());
			server->send_rpl("1499", target_user, reply_params, "INVITE");
		}
	}
	else
	{
		reply_params.push_back(params[1]);
		server->send_rpl("403", user, reply_params, "");
	}
}