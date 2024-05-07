#include "pei_slingers.h"

#define MOTOR_STEPS 20
#define DIR_PIN 12
#define STEP_PIN 11
#define ENABLE_PIN 13
#define SWITCH_PIN 10
Stapper myStapper = Stapper( STEP_PIN, DIR_PIN, ENABLE_PIN, MOTOR_STEPS);
Brains brains=Brains();
uint32_t loopMillis=0;
uint32_t lastPlot=0;

SimpleSwitch mySwitch=SimpleSwitch(SWITCH_PIN,LOW);

void setup() {
	//give the serial monitor time to get connected
	delay(2000);
    Serial.begin(9600);
    Serial.println("starting pei_slingers");
    myStapper.setup();
    Serial.println("pei_slingers started");
    brains.setup();
    mySwitch.setup();

}

void loop() {
	loopMillis=millis();
	brains.loop();
	myStapper.loop();
	mySwitch.loop();
	if(loopMillis-lastPlot>10){
		lastPlot=loopMillis;
	plot3(Serial,brains.getState(),myStapper.getDirection()*150,myStapper.hasStepped()?100:0);
	}

}
