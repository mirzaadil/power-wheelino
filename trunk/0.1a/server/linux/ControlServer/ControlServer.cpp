#include <iostream>
#include "pthread.h"
#include "SerialComm.h"
#include "udpserver.h"

using namespace std;

struct threadparm_t {
   SerialComm  *ser;
   char  drive;
   char  steering;
} ;

void *proxyThread(void *ptr);

int main (int argc, char* argv[]){

	char * buffer;

	SerialComm serial("/dev/pts/3");
	udp_server server(50000);

	threadparm_t  gData;

	gData.ser = (SerialComm *) &serial;


	while (1){

		buffer = server.listen();

		gData.drive = buffer[0];
		gData.steering = buffer[1];

		pthread_t thread;
		pthread_create(&thread, NULL, proxyThread, &gData);
		pthread_detach(thread);

		//serial.write(pbuffer);
	}


}

void *proxyThread (void *ptr){
	threadparm_t *gData;
	gData = (threadparm_t *) ptr;

	printf("%d \t %d\n\r",gData->drive,gData->steering);
}
