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

     // send initial gamedata to all clients
     serv->gd = new GameData();
     for (int i = 0; i < NUM_PLAYERS; i++)
     {
         serv->send_gamedata(i);
     }

     // wait for ready action and send init packet;blocks until 4 connect
     for (int i = 0; i < NUM_PLAYERS; i++)
     {
         int check_recv_ready = serv->recv_event(i);
         while (check_recv_ready == -1) {
             check_recv_ready = serv->recv_event(i);
         }
         serv->send_init_packet(i);
     }

     // send updated game data
     serv->gd->gamestate = GameState::IN_GAME;
     for (int i = 0; i < NUM_PLAYERS; i++)
     {
         serv->send_gamedata(i);
     }

     while (1) {

     }
    
    /* while(1){
         int ret = serv->update();
         if (ret == -1){
             break;
         }
     }*/
     delete serv;
}