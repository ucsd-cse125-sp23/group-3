#include "include/Server.h"
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
         serv->send_init_packet(id, id);
         std::cout << "connected ss " << ss <<" with id" << serv->ids[id] << std::endl;
     }
     while (1) {
         // reinitialize all needed data
         serv->initialize_game();

         // send initial gamedata to all clients
         for (int i = 0; i < NUM_PLAYERS; i++)
         {
             serv->send_gamedata(i);
         }

         // character selection
         int num_selection = 0;
         int idx = 0;
         while (num_selection < 4)
         {
             int character = serv->handle_acq(idx % NUM_PLAYERS);
             if (character != -1) num_selection++;
             idx++;
         }

         // wait for ready action and send init packet;blocks until 4 connect
         for (int i = 0; i < NUM_PLAYERS; i++)
         {
             int check_recv_ready = serv->recv_event(i);
             while (check_recv_ready != (int)EventType::READY) {
                 check_recv_ready = serv->recv_event(i);
             }
         }

         SOCKET cp_sessions[NUM_PLAYERS];

         // Reorder sessions with: A,B,C,D
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
         }

         while (1) {

             std::chrono::milliseconds start = std::chrono::duration_cast<std::chrono::milliseconds>(
                 std::chrono::system_clock::now().time_since_epoch()
             );

             std::chrono::milliseconds end = std::chrono::duration_cast<std::chrono::milliseconds>(
                 std::chrono::system_clock::now().time_since_epoch()
             );

             serv->check_event = { -1, -1, -1, -1 };
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
             serv->checkGameEndLogic();
             for (int j = 0; j < NUM_PLAYERS; j++)
             {
                 serv->send_gamedata(j);
             }
             end = std::chrono::duration_cast<std::chrono::milliseconds>(
                 std::chrono::system_clock::now().time_since_epoch()
             );

             serv->cleanUpSkillStatus();
             serv->updateByEvent(all_records);
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
     }
    
     delete serv;
}