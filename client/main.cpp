#include "Client.h"

int main(){
	Client* cli = new Client();

	// listen for init packet
	int assigned_id = cli->accept_init();
	while (assigned_id == -1) {
		assigned_id = cli->accept_init();
	}

	while(1){
		cli->update();
	}
}