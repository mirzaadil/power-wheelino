#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>



class udp_client {
	int sock;
	struct sockaddr_in server_addr;
	struct hostent *host;
	char send_data[2];
	int port;


public:
	udp_client(char* dstServer, int dstPort){
		host = (struct hostent *) gethostbyname((char*)dstServer);
		port = dstPort;
	}

	void send(bool fwd, char speed, bool left, char angle) {
		send_data[0] = (fwd*128) | speed;
		send_data[1] = (left*128) | angle;
		//send_data[2] = '\0';
		if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
		{
			perror("socket");
			exit(1);
		}

		server_addr.sin_family = AF_INET;
		server_addr.sin_port = htons(port);
		server_addr.sin_addr = *((struct in_addr *)host->h_addr);
		bzero(&(server_addr.sin_zero),8);

		sendto(sock,
				send_data,
				strlen(send_data),
				0,
				(struct sockaddr *)&server_addr,
				sizeof(struct sockaddr)
		);


	}
};
