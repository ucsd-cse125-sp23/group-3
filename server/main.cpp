#include "Server.h"
#include <GLFW/glfw3.h>

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
         double start = glfwGetTime();
         double end = glfwGetTime();
         int events[4] = {-1, -1, -1, -1};
         while (end - start < (double)LISTEN_TICK / 1000.0) {
             for (int i = 0; i < NUM_PLAYERS; i++)
             {
                 if (events[i] != -1)
                 {
                     continue; // continue if we already receive 1 event from this client
                 }
                 int check_event = serv->recv_event(i);
                 events[i] = check_event;
             }
             end = glfwGetTime();
         }
         serv->updateByEvent((EventType)events[0], (EventType)events[1], (EventType)events[2], (EventType)events[3]);
         for (int j = 0; j < NUM_PLAYERS; j++)
         {
             serv->send_gamedata(j);
         }
         end = glfwGetTime();
         while (end - start < (double)TICK_TIME / 1000.0) {
             // wait until tick time
             end = glfwGetTime();
         }
     }
    
    /* while(1){
         int ret = serv->update();
         if (ret == -1){
             break;
         }
     }*/
     delete serv;
}