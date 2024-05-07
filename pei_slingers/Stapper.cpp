/*
 * Stapper.cpp
 *
 *  Created on: 05 May 2024
 *      Author: jan
 */

#include "pei_slingers.h"

Stapper::Stapper(uint8_t stepPin, uint8_t directionPin, uint8_t enablePin,
		uint16_t stepsPerRound) {

	myStepPin =stepPin;
	myDirectionPin=directionPin;
	myEnablePin= enablePin;
	myStepsPerRound= stepsPerRound;
}

Stapper::~Stapper() {
}

void Stapper::setup() {
	pinMode(myStepPin,OUTPUT);
	pinMode(myDirectionPin,OUTPUT);
	pinMode(myEnablePin,OUTPUT);
	digitalWrite(myDirectionPin, LOW);
	digitalWrite(myEnablePin, HIGH);
}

void Stapper::loop() {
	if(myNewLastSetSpeed!=myLastSetSpeed){
		//we got new speed so we need to do some stuff here
		 myRoundsPerMinute=myNewRoundsPerMinute;
		 myAccelerationDuration=myNewAccelerationDuration;
		 myLastSetSpeed=myNewLastSetSpeed;
	}
	if(loopMillis-myLastStepTime > myNextStepDuration){
		myLastStepTime=loopMillis;
		calculateNextStepParams();
		digitalWrite(myStepPin,HIGH);
		delay(1); //TOFIX delay seems pretty long here delayMicroseconds
		digitalWrite(myStepPin,LOW);
		myHasStepped=true;

	}
}

void Stapper::calculateNextStepParams(){
	uint32_t stepsPerMinute= myRoundsPerMinute*myStepsPerRound;
	myNextStepDuration= 60000UL/ stepsPerMinute;
	Serial.println(myNextStepDuration);
	myDirection=1;
}

void Stapper::setSpeed(uint16_t roundsPerMinute,
		uint32_t accelerationDuration) {
	 myNewRoundsPerMinute=roundsPerMinute;
	 myNewAccelerationDuration=accelerationDuration;
	 myNewLastSetSpeed=loopMillis;
}

boolean Stapper::hasStepped() {
	boolean ret=myHasStepped;
	myHasStepped=false;
	return ret;

}
