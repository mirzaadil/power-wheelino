#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <fstream>
#include <libexplain/tcsetattr.h>




//using namespace std;

class PSerialComm {

private:
        static const int Dsize = 1;
        //LibSerial::SerialStream myss;
        int fd,c, res;
        struct termios toptions;
public:

        PSerialComm( char * serialPort) {
			//#define BAUDRATE B57600
			//#define MODEMDEVICE "/dev/ttyS1"
			#define _POSIX_SOURCE 1 /* POSIX compliant source */
			#define FALSE 0
			#define TRUE 1


			/* Open serial port */
			fd = open(serialPort, O_RDWR | O_NOCTTY  );
			if (fd <0) {std::perror(serialPort); exit(-1); }

			/* save current port settings */
			if (tcgetattr(fd,&toptions) < 0) {
				std::perror("init_serialport: Unable to get attributes");
				//exit(-1);
			}


			cfsetospeed(&toptions,B57600);// 57600 baud
			cfsetispeed(&toptions,B57600);

			// 8N1
			toptions.c_cflag &= ~PARENB;
			toptions.c_cflag &= ~CSTOPB;
			toptions.c_cflag &= ~CSIZE;
			toptions.c_cflag |= CS8;

			//No Flow Control
			toptions.c_cflag &= ~CRTSCTS;

			// turn on READ & ignore ctrl lines
			toptions.c_cflag |= CREAD | CLOCAL;

			// turn off s/w flow ctrl
			toptions.c_iflag &= ~(IXON | IXOFF | IXANY);

			// make raw
			toptions.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
			toptions.c_oflag &= ~OPOST;

		    // see: http://unixwiz.net/techtips/termios-vmin-vtime.html
			toptions.c_cc[VTIME]    = 0;   /* inter-character timer unused */
			toptions.c_cc[VMIN]     = 1;   /* blocking read until 5 chars received */


		    if( tcsetattr(fd, TCSANOW, &toptions) < 0) {
		        std::perror("init_serialport: Couldn't set term attributes");
		       // exit(-1);
		    }

        }

        int writeOut(char buffer[]){
        	int n;
        	n = write(fd , buffer ,3);
			return n;
        }
        int writeOut(char byte){
        	int n;
        	n = write(fd, &byte,1);
        	return 0;
        }

};
