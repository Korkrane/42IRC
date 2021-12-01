#include "../../includes/irc.hpp"

/**
 * @brief 
 * 
 * @param nickname 
 * @return true 
 * @return false 
 * TODO: faire des tests sur un server 
 */
static bool checkNickGrammar(std::string nickname)
{
    //Attention a certains caracteres speciaux
    std::string special("[]\\_^{|}");
    //Le premier caractere doit etre un alpha
    //le premier caractere ne doit pas faire partie du charset special
    //voir autres cas
}

/**
 * @brief 
 * 
 * @param command 
 * @param client 
 * @param server 
 * Parameters: <nickname>
 * NICK command is used to give user a nickname or change the existing
   one.
 */
void		Commands::nick(Commands *command, Client *client, Server *server)
{
    //On verifie le nombre de param (doit etre egal a 2)

    //Puis on verifie si le nickname est correct grammaticallement (fonction de grammar)

    //Puis on verifie que le nickname n existe pas deja (-> sinon cas de collision)
    //Preparer la reponse pour le serveur
    //Modifier les infos relatives au client pour enregistrer le nickname
    return ;
}

