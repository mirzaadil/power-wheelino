#include <iostream>
#include "pthread.h"
#include "PSerialComm.h"
#include "udpserver.h"
#include <strings.h>
#include <string.h>

using namespace std;

struct threadparm_t {
   PSerialComm  *ser;
   char  drive;
   char  steering;
} ;

void *proxyThread(void *ptr);

int main (int argc, char* argv[]){
	char sDev[128];
	strcpy(sDev,"/dev/pts/1\0");
	if (argc > 1){
		strcpy(sDev,argv[1]);
		sDev[strlen(argv[1])] = 0;
	}

	char * buffer;
	cout << "Using Serial Port " << sDev << "\n";
	PSerialComm serial(sDev);
	udp_server server(50000);

	threadparm_t  gData;

	gData.ser = (PSerialComm *) &serial;


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
	buffer[0] = gData->drive;
	buffer[1] = gData->steering;
	buffer[2] = 0x7F;

	//mySerial = (SerialComm *) gData->ser;

	printf("%d \t %d\n\r",gData->drive,gData->steering);
	gData->ser->writeOut(buffer);
//	gData->ser->write(gData->drive);
//	gData->ser->write(gData->steering);
//	gData->ser->write((char)0x7F);

}
