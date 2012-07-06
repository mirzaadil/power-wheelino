#include <iostream>
#include "SerialComm.h"
#include "udpserver.h"

using namespace std;

int main (int argc, char* argv[]){
	udp_server server(50000);

	SerialComm serial("/dev/pts/3");
	while (1){
		char * buffer;
		buffer = server.listen();
		char  pbuffer[2];
		pbuffer[0] = buffer[0];
		pbuffer[1] = buffer[1];

		serial.write(pbuffer);
	}


}
