#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <string>

using namespace std;

class udp_server {

	//UDP Socket variables
	int sock;
	int bytes_read;
	socklen_t addr_len;
	int portNumber;									//Listen Port Number
	struct sockaddr_in server_addr , client_addr;	//Address Variables
	fd_set socks;
	struct timeval t;								//Socket Timeout variable


	//SerialComm mySerial;
	int rcvd;



public:
	udp_server(int portNum ) {
		portNumber = portNum;
		init();
	}

	char* listen() {
		char recv_data[10];
		char * pointer;
		while (1){
			while (1){
				FD_ZERO (&socks);
				FD_SET(sock, &socks);
				t.tv_sec = 1;
				t.tv_usec = 100000;
				  if (select (sock + 1, &socks, NULL, NULL, &t)){
					  bytes_read = recvfrom(
												  sock,
												  recv_data,
												  2,
												  0,
												  (struct sockaddr *)&client_addr,
												  &addr_len
												);


				  } else {
					  // read timeout
					  printf("!");
					  fflush(stdout);
					  rcvd = 0;
					  //char * tchar[] = {'\0','\0'};
					  //  return tchar;		//return 0 position if datastream is lost
					  return {"\0\0"};
					  //return *zerochar;
					  //break;

				  }


				  recv_data[bytes_read] = '\0';
				  if (rcvd == 0){
					char line[10] = "Connected";
					usleep(5000);//microseconds
					sendto(sock,line,9,0,(struct sockaddr*)&client_addr,sizeof(client_addr));
					printf("\nSent Connection Message\n");
				  }
				  rcvd++;
				  pointer = recv_data;
				  return pointer;
				  //printf("%d iteration\n",rcvd);
				  if (rcvd > 1000){rcvd = 0;}
				  //printf("\r\n(%s , %d) said : ",inet_ntoa(client_addr.sin_addr),
				  //				   ntohs(client_addr.sin_port)
				  //	);
				  string drive;
				  string direction;

				  int speed = recv_data[0];
				  int angle = recv_data[1];
				  //printf("%d - %d\r\n", speed,angle);

				  if (speed > -1){drive = "Fwd";} else {drive = "Rev";}
				  if (angle > -1){direction = "Right";} else {direction = "Left";}

				printf("\t %s @ %d and %s @ %d\r\n\0",
						  drive.c_str(),
						  speed,
						  direction.c_str(),
						  angle
						);
			  fflush(stdout);
			  pointer  = recv_data;
			  return pointer;

			}
		}
			return 0;
	}
private:
	void init(){
		if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
			perror("Socket");
			exit(1);
		}

		server_addr.sin_family = AF_INET;
		server_addr.sin_port = htons(portNumber);
		server_addr.sin_addr.s_addr = INADDR_ANY;
		bzero(&(server_addr.sin_zero),8);
		if (bind(sock,(struct sockaddr *)&server_addr,
			sizeof(struct sockaddr)) == -1)
		{
			perror("Bind");
			exit(1);
		}


		addr_len = sizeof(struct sockaddr);
		printf("\nUDPServer Waiting for client on port %d\n", portNumber);
		fflush(stdout);
		rcvd = 0;

	}

};


