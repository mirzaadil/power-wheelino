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
	int sock;
	int bytes_read;
	socklen_t addr_len;

	struct sockaddr_in server_addr , client_addr;
public:
	udp_server(int portNum )
	{
			if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
				perror("Socket");
				exit(1);
			}

			server_addr.sin_family = AF_INET;
			server_addr.sin_port = htons(portNum);
			server_addr.sin_addr.s_addr = INADDR_ANY;
			bzero(&(server_addr.sin_zero),8);


			if (bind(sock,(struct sockaddr *)&server_addr,
				sizeof(struct sockaddr)) == -1)
			{
				perror("Bind");
				exit(1);
			}

			addr_len = sizeof(struct sockaddr);

		printf("\nUDPServer Waiting for client on port %d", portNum);
			fflush(stdout);
	}
	char* listen() {
		char recv_data[10];
		while (1)
		{

			  bytes_read = recvfrom(
					  	  	  sock,
					  	  	  recv_data,
					  	  	  2,
					  	  	  0,
							  (struct sockaddr *)&client_addr,
							  &addr_len
							);


			  recv_data[bytes_read] = '\0';

			  printf("\n(%s , %d) said : ",inet_ntoa(client_addr.sin_addr),
										   ntohs(client_addr.sin_port));
			  string drive;
			  string direction;
			  
			  int speed = recv_data[0];
			  int angle = recv_data[1];
			  printf("%d - %d\n", speed,angle);

			  if (speed > 0){drive = "Fwd";} else {drive = "Rev";}
			  if (angle > 0){direction = "Left";} else {direction = "Right";}
			  
			printf("\t %s @ %d and %s @ %d",
					  drive.c_str(),
					  speed,
					  direction.c_str(),
					  angle
					);
		  fflush(stdout);
		  char * pointer = recv_data;
		  return pointer;

			}
			return 0;
	}
};



