#include <IRC.hpp>

void        Commands::send_quit_message(User *user, IRC *server)
{
    (void)user;
    (void)server;

    
    return ;
}

//TODO: Mahaut + Baudoin (+Damien )?
void        Commands::quit_cmd(User *user, IRC *server)
{
    (void)user;
    (void)server;

    send_quit_message();    
    return ;
}