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
	string sDev;
	sDev = "/dev/pts/1";
	if (argc > 1){
		sDev = argv[1];
	}
	char * buffer;
	cout << "Using Serial Port " << sDev << "\n";
	SerialComm serial(sDev);
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
	//SerialComm *mySerial;
	char buffer[3];
	buffer[1] = gData->drive;
	buffer[2] = gData->steering;
	buffer[3] = 0b00000000;

	//mySerial = (SerialComm *) gData->ser;

	printf("%d \t %d\n\r",gData->drive,gData->steering);
	gData->ser->write(buffer);
}
