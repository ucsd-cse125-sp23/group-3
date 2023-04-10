#include "Server.h"

int main(){
	Server* serv = new Server();
	while(1){
		serv->update();
	}
}