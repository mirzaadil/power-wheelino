#include <Arduino.h>

// variables
int ledPin = 13; // LED connected to digital pin 13
char inData[16];
int bRead;

void setup(){
	Serial.begin(57600); // opens serial port, sets data rate to 9600 bps
	Serial.setTimeout(50000);
	pinMode(ledPin, OUTPUT);      // sets the digital pin as output
	Serial.println("------------------");
	Serial.println("   Started");
	Serial.println("------------------");
}

void loop(void){

	long before = millis();
    bRead = Serial.readBytesUntil(0x7F,inData,4);
    if ( bRead == 0 ){
    	Serial.println("Timeout");
    	inData[0] = 0b00000000;
    	inData[1] = 0b00000000;
    }
    if (bRead >3 ){
    	Serial.println("Error");
    }

    Serial.write(27);
    Serial.print("[2J"); // clear screen
    Serial.write(27); // ESC
    Serial.print("[H"); // cursor to home

    Serial.print("Bytes Read: ");
    Serial.println(bRead);
    Serial.println("First Byte");
    Serial.println((int)inData[0]);
    Serial.println(
    		map((int)inData[0],0,126,0,1024)
    );

    Serial.println("Second Byte");
    Serial.println((int)inData[1]);
    Serial.println("");
    Serial.println(millis() - before);


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
