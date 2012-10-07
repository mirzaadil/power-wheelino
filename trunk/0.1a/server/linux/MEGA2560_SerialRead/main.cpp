#include <Arduino.h>
#include <Servo/Servo.h>

//int ledPin = 13; // LED connected to digital pin 13

//Serial Buffer
char inData[4];

//# of Bytes Read
int bRead;

//Hardware
Servo steering;
Servo drive;

//Value Containers
int rawSteeringVal;
int rawDriveVal;
int processedSteeringVal;
int processedDriveVal;

void setup(){

	Serial.begin(57600);	// Open serial port, set data rate to 57600 bps
	Serial.setTimeout(100);	//Set serial timeout (ms)
	//TODO: Tune this value !!!
	//pinMode(ledPin, OUTPUT);	// sets the digital pin as output

	steering.attach(5);		//Steering Servo Pin 5
	drive.attach(6);		//Drive Servo (motor) Pin 6

	Serial.println("------------------");
	Serial.println("   Started");
	Serial.println("------------------");
}

void loop(void){

    bRead = Serial.readBytesUntil(0x7F,inData,4);

    if ( bRead != 2 ){	//Timeout or Noise
    	Serial.print("! ");
    	inData[0] = 0b00000000; //Steering
    	inData[1] = 0b00000000; //Drive
    } else { //2 bytes and Delimiter
    	//Correct # of Bytes
    	Serial.print("* ");
    }

    rawSteeringVal = (int)inData[0];
    rawDriveVal = (int)inData[1];

    //convert input range to desired angles
    //using 60-120 provides 60 deg of movement L/R of center
    processedSteeringVal = map(rawSteeringVal,-126,126,60,120);
    processedDriveVal = map(rawDriveVal,-126,126,60,120);

    //Send to Hardware
    steering.write(processedSteeringVal);
    drive.write(processedDriveVal);

    //Print Report
    Serial.print(bRead);
    Serial.print("\t");
    Serial.print(processedSteeringVal);
    Serial.print("\t");
    Serial.println(processedDriveVal);

}


int main(void)
{
	init();

	setup();

	for (;;)
	loop();
	if (serialEventRun) serialEventRun();
	return 0;
}
