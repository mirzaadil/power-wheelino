#include "udpclient.h"
#include <iostream>

using namespace std;
const bool LEFT = true;
const bool RIGHT = false;
const bool FORWARD = true;
const bool REVERSE = false;


int main(int argc, char* argv[]) {
	bool fwd = atoi(argv[1]);
	int speed = atoi(argv[2]);
	bool dir = atoi(argv[3]);
	int angle = atoi(argv[4]);
	udp_client* ucli = new udp_client((char *)"127.0.0.1",50000);
	ucli->send(
			fwd,	//Drive Direction FORWARD | REVERSE
			speed,			//Speed (0-127)
			dir,		//Steering Direction LEFT | RIGHT
			angle			//Steering Angle (0-127)
	);

//		udp_client* ucli = new udp_client((char *)"127.0.0.1",50000);
//		ucli->send(
//				FORWARD,	//Drive Direction FORWARD | REVERSE
//				10,			//Speed (0-127)
//				RIGHT,		//Steering Direction LEFT | RIGHT
//				16			//Steering Angle (0-127)
//		);

//		ucli->send(
//				REVERSE,	//Drive Direction FORWARD | REVERSE
//				10,			//Speed (0-127)
//				RIGHT,		//Steering Direction LEFT | RIGHT
//				16			//Steering Angle (0-127)
//		);

}
