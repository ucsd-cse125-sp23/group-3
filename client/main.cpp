#include "Client.h"

int main(){
	Client* cli = new Client();
	while(1){
		cli->update();
	}
}