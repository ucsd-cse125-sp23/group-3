#include "Server.h"
#include <GLFW/glfw3.h>
#include <chrono>

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
         std::cout << "sending id:" << serv->ids[i] << std::endl;
         int check_recv_ready = serv->recv_event(i);
         while (check_recv_ready == -1) {
             check_recv_ready = serv->recv_event(i);
         }
         serv->send_init_packet(i, serv->ids[i]); // TODO: add randomly assign character logic
     }

     // send updated game data
     serv->gd->gamestate = GameState::IN_GAME;
     for (int i = 0; i < NUM_PLAYERS; i++)
     {
         serv->send_gamedata(serv->ids[i]);
     }

     while (1) {

         std::chrono::milliseconds start = std::chrono::duration_cast<std::chrono::milliseconds>(
             std::chrono::system_clock::now().time_since_epoch()
         );
         //double start = glfwGetTime();

         std::chrono::milliseconds end = std::chrono::duration_cast<std::chrono::milliseconds>(
             std::chrono::system_clock::now().time_since_epoch()
         );
         //double end = glfwGetTime();

         int events[4] = {-1, -1, -1, -1};
         while (end - start < (std::chrono::milliseconds)LISTEN_TICK) {

             for (int i = 0; i < NUM_PLAYERS; i++)
             {
                 if (events[serv->ids[i]] != -1)
                 {
                     continue; // continue if we already receive 1 event from this client
                 }
                 int check_event = serv->recv_event(serv->ids[i]);
                 events[serv->ids[i]] = check_event;
             }
             end = std::chrono::duration_cast<std::chrono::milliseconds>(
                 std::chrono::system_clock::now().time_since_epoch()
             );
             //end = glfwGetTime();
         }
         serv->updateByEvent((EventType)events[serv->ids[0]], (EventType)events[serv->ids[1]], (EventType)events[serv->ids[2]], (EventType)events[serv->ids[3]]);
         for (int j = 0; j < NUM_PLAYERS; j++)
         {
             serv->send_gamedata(serv->ids[j]);
         }
         end = std::chrono::duration_cast<std::chrono::milliseconds>(
             std::chrono::system_clock::now().time_since_epoch()
         );
         //end = glfwGetTime();
         while (end - start < (std::chrono::milliseconds)TICK_TIME) {
             // wait until tick time
             end = std::chrono::duration_cast<std::chrono::milliseconds>(
                 std::chrono::system_clock::now().time_since_epoch()
             );
             //end = glfwGetTime();
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