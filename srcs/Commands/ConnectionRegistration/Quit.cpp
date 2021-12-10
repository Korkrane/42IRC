#include <IRC.hpp>

void Commands::send_quit_message(User *user, IRC *server, std::string message)
{
    (void)user;
    (void)server;
    (void)message;
    return;
}

//TODO: Mahaut + Baudoin (+Damien )?
void Commands::quit_cmd(User *user, IRC *server)
{
    (void)user;
    (void)server;

    std::vector<std::string> params = user->get_params();
    int size = user->get_params_size();
    std::string message; //Partie de la reponse qui sera envoyee au serveur
    std::vector<std::string>::iterator it = params.begin();
    std::vector<std::string>::iterator ite = params.end();

    if (size == 1)
        message = "";
    else
    {
        //On va faire le tour des tous les params et reconstiuer le message
        while (it != ite)
        {
            message += (*it);
            if (ite + 1 == ite) //pour eviter un espace vide a la fin
                break;
            message += " ";
            it++;
        }
    }
    send_quit_message(user, server, message);
    return;
}