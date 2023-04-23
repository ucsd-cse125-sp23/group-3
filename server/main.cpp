#include "Server.h"

int main()
{

     Server* serv = new Server();
     
     // blocks until 4 clients
     for (int id = 0; id < NUM_PLAYERS; id ++){
         SOCKET ss = INVALID_SOCKET;
         while(ss == INVALID_SOCKET){
             ss = accept(serv->ListenSocket, NULL, NULL);
         }
         serv->sessions[id] = ss;
         std::cout << "connected ss " << ss << std::endl;
     }
     // send init packet
     for (int i = 0; i < NUM_PLAYERS; i++)
     {
         serv->send_init_packet(i);
     }
    
     while(1){
         int ret = serv->update();
         if (ret == -1){
             break;
         }
     }
     delete serv;
}