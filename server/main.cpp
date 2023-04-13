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
        std::cout << "connected " << id << std::endl;
    }
    
    while(1){
        int ret = serv->update();
        if (ret == -1){
            break;
        }
    }
    delete serv;
}