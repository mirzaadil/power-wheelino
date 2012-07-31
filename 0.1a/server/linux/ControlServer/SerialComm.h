#include <SerialStream.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

class SerialComm {

private:
        static const int Dsize = 1;
        LibSerial::SerialStream myss;

public:

        SerialComm( string serialPort) {

        	//      LibSerial::SerialStream myss = LibSerial::SerialStream("/dev/pts/8",
        	//                      LibSerial::SerialStreamBuf::BAUD_9600,
        	//                      LibSerial::SerialStreamBuf::CHAR_SIZE_8,
        	//                      LibSerial::SerialStreamBuf::PARITY_NONE,
        	//                      1,
        	//                      LibSerial::SerialStreamBuf::FLOW_CONTROL_NONE
        	//      );

			myss.Open(serialPort,std::ios_base::out);
			myss.SetBaudRate(LibSerial::SerialStreamBuf::BAUD_57600);
			myss.SetCharSize(LibSerial::SerialStreamBuf::CHAR_SIZE_8);
			myss.SetFlowControl(LibSerial::SerialStreamBuf::FLOW_CONTROL_NONE);
			myss.SetParity(LibSerial::SerialStreamBuf::PARITY_NONE);
			myss.SetNumOfStopBits(1);
        }

        int write(char buffer[]){

//          myss << "First " << buffer[0] <<"; Second " << buffer[1]<< "\n";
//          cout << buffer[1] << "\t" <<buffer[2];
			myss.write(buffer,2);
			//myss.Close();
			return 0;
        }
        int write(char byte){
        	myss << byte;

        }

};
