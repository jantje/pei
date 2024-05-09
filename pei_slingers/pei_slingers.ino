#include "pei_slingers.h"

#define MOTOR_STEPS 3200
#define DIR_PIN 12
#define STEP_PIN 11
#define ENABLE_PIN 13
#define SWITCH_PIN A0
#define SWITCH_GND A1
Stapper myStapper = Stapper( STEP_PIN, DIR_PIN, ENABLE_PIN, MOTOR_STEPS);
Brains brains=Brains();
uint32_t loopMillis=0;
uint32_t loopMicros=0;
uint32_t lastPlot=0;

SimpleSwitch mySwitch=SimpleSwitch(SWITCH_PIN,LOW);

void setup() {
	//give the serial monitor time to get connected
	delay(2000);
    Serial.begin(9600);
    Serial.println("starting pei_slingers");
	pinMode(SWITCH_GND, OUTPUT);
	digitalWrite(SWITCH_GND, LOW);
    myStapper.setup();
    Serial.println("pei_slingers started");
    brains.setup();
    mySwitch.setup();

}

void loop() {
	loopMillis=millis();
	loopMicros=micros();
	brains.loop();
	myStapper.loop();
	mySwitch.loop();
	if(loopMillis-lastPlot>1000){
		lastPlot=loopMillis;
		int16_t state=brains.getState()*100;
		int16_t direction=myStapper.getDirection()*150;
		int16_t steps=myStapper.getNumSteps();
		int16_t roundsPer100Minutes=myStapper.getActualRoundsPerMinute()*100;

		plot4(Serial,state,direction,steps,roundsPer100Minutes);
		Serial.print(state);
		Serial.print(";");
		Serial.print(direction);
		Serial.print(";");
		Serial.print(steps);
		Serial.print(";");
		Serial.println(roundsPer100Minutes);
	}

}
