#include <IRC.hpp>

//TODO: a tester
void        Commands::oper(User *user, IRC *server)
{
    (void)user;
    (void)server;

    int size = user->get_params_size();
    std::vector<std::string> error;
    std::vector<std::string> params;

    if (size < 2)
    {
        //TODO: build reply
        /*
        error.push_back(user->get_command_name());
        error_handler("461", user, NULL, error);
        */
        return ;
    }
    //TODO: voir cas ou il y aurait trop d'arguments?

    //Check if the client is well registered 
    if (user->user_is_registered() == true)
    {
        //TODO: build reply
        //error_handler("491", user, NULL, error);
        return ;
    }
    std::string name = params[0];
    std::string password = params[1];

    //Check that the password and opername are correct ?
    //TODO: pas bien compris la notion de opername 

    return ;
}