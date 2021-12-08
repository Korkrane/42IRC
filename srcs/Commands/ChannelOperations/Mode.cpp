#include <irc.hpp>

//set_user_mode
//set_output_mode
//switch_mode
//check_channel_errors?
//sortmodearg

void            Commands::mode(User *user, IRC *server)
{
    (void)user;
    (void)server;
    //Check du nombre d'arguments
    std::string modes;
    std::string channel;
    int param_size = user->get_params_size();
    std::vector<std::string> params;
    //Preparation du vecteur qui permet de gerer les erreurs
    std::vector<std::string> error;
    if (param_size < 2)
    {
        error.push_back(user->get_command_name());
        error_handler("461", user, NULL, error);
        return ;
    }
    //Verifier comment gerer plus de 2 arguments
    else
    {
        //On store la channel passee en parametre et les modes demandes
        channel = params[1];
        modes = params[2];
        //On check la channel (syntaxe)
        if (is_correct_channel_name(channel) == false)
        {
            error.push_back(channel);
            error_handler("403", user, NULL, error);
            return ;
        }
        //On check si la channel existe ?
        Channel *chan = NULL;
        if (server->has_channel(channel) == false)
        {
            //TODO: a tester
            return ;
        }
        chan = server->find_channel(channel);
        //On check si l'user est membre de la channel
        if (chan->user_is_member(user) == false)
        {
            error.push_back(user->get_nickname());
            error.push_back(channel);
            error_handler("441", user, NULL, error);
            return ;
        }
        //On doit checker les modes
        bool check = chan->check_channel_modes(modes);
        if (check == false)//ERR_UNKNOWN MODE
        {
            //Isoler le char qui n est pas reconnu
            std::string incorrect = chan->get_unknown_mode(channel);
            error.push_back(incorrect);
            error.push_back(channel);
            error_handler("472", user, chan, error);
        }
    }
    return ;
}