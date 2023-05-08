#include "include/Server.h"
#include <chrono>

int main()
{

     Server* serv = new Server();
     for (auto a : serv->ids)
 	    std::cout << a << " ";
     // blocks until 4 clients
     for (int id = 0; id < NUM_PLAYERS; id ++){
         SOCKET ss = INVALID_SOCKET;
         while(ss == INVALID_SOCKET){
             ss = accept(serv->ListenSocket, NULL, NULL);
         }
         serv->sessions[id] = ss;
         std::cout << "connected ss " << ss <<" with id" << serv->ids[id] << std::endl;
     }

     // send initial gamedata to all clients
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

     SOCKET cp_sessions[NUM_PLAYERS];

     // Reorder sessions with: A,B,C,D
     //for (int ind = 0; ind < 4; ind ++) {
     //    cp_sessions[ind] = serv->sessions[serv->ids[ind]];
     //}
     for (int i = 0; i < 4; i++)
     {
         auto it = std::find(serv->ids.begin(), serv->ids.end(), i);
         int client_id_idx = it - serv->ids.begin();
         cp_sessions[i] = serv->sessions[client_id_idx];
     }
     for (int ind = 0; ind < 4; ind++) {
         serv->sessions[ind] = cp_sessions[ind];
     }

     // send updated game data
     serv->gd->gamestate = GameState::IN_GAME;
     for (int i = 0; i < NUM_PLAYERS; i++)
     {
         serv->send_gamedata(i);
         std::cout << "init: " << serv->gd->remaining_time << std::endl;
     }

     while (1) {

         std::chrono::milliseconds start = std::chrono::duration_cast<std::chrono::milliseconds>(
             std::chrono::system_clock::now().time_since_epoch()
         );

         std::chrono::milliseconds end = std::chrono::duration_cast<std::chrono::milliseconds>(
             std::chrono::system_clock::now().time_since_epoch()
         );

         serv->check_event = {-1, -1, -1, -1};
         std::unordered_map<int, std::vector<int>> all_records;
         while (end - start < (std::chrono::milliseconds)LISTEN_TICK) {

             for (int i = 0; i < NUM_PLAYERS; i++)
             {
                 if (serv->check_event[i] != -1)
                 {
                     continue; // continue if we already receive 1 event from this client
                 }
                 all_records[i] = serv->recv_eventRecords(i);
             }
             end = std::chrono::duration_cast<std::chrono::milliseconds>(
                 std::chrono::system_clock::now().time_since_epoch()
             );
         }

         serv->updateByEvent(all_records);
         std::cout << "In game: " << serv->gd->remaining_time << std::endl;
         serv->checkGameEndLogic();
         for (int j = 0; j < NUM_PLAYERS; j++)
         {
             serv->send_gamedata(j);
         }
         end = std::chrono::duration_cast<std::chrono::milliseconds>(
             std::chrono::system_clock::now().time_since_epoch()
         );
         while (end - start < (std::chrono::milliseconds)TICK_TIME) {
             // wait until tick time
             end = std::chrono::duration_cast<std::chrono::milliseconds>(
                 std::chrono::system_clock::now().time_since_epoch()
             );
         }
     }
    
     delete serv;
}