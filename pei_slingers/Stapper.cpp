/*
 * Stapper.cpp
 *
 *  Created on: 05 May 2024
 *      Author: jan
 */

#include "pei_slingers.h"

Stapper::Stapper(uint8_t stepPin, uint8_t directionPin, uint8_t enablePin,
		uint16_t stepsPerRound) {

	myStepPin = stepPin;
	myDirectionPin = directionPin;
	myEnablePin = enablePin;
	myStepsPerRound = stepsPerRound;
}

Stapper::~Stapper() {
}

void Stapper::setup() {
	pinMode(myStepPin, OUTPUT);
	pinMode(myDirectionPin, OUTPUT);
	pinMode(myEnablePin, OUTPUT);
	digitalWrite(myDirectionPin, HIGH);
	digitalWrite(myEnablePin, LOW);
}

#define HIGH_ON
#ifdef HIGH_ON
#define MY_ON HIGH
#define MY_OFF LOW
#else
#define MY_ON LOW
#define MY_OFF HIGH
#endif

void Stapper::loop() {

	if (myNewLastSetSpeed != myLastSetSpeed) {
		//we got new speed so we need to do some stuff here
		myOldRoundsPerMinute = myRoundsPerMinute;
		myRoundsPerMinute = myNewRoundsPerMinute;
		myAccelerationDuration = myNewAccelerationDuration;

		myMaxRoundsPerMinute = myNewMaxRoundsPerMinute;
		mySinusDuration = myNewSinusDuration;
		mySpeedType = myNewSpeedType;

		myLastSetSpeed = myNewLastSetSpeed;
	}

		if((loopMicros - myLastStepTime >= myNextStepDuration)) {
			if (myActualRoundsPerMinute != 0){
				if (myNewDirection != myDirection) {
					myDirection = myNewDirection;
					digitalWrite(myDirectionPin, myDirection);
				}
				digitalWrite(myStepPin, LOW);
				delayMicroseconds(10);
				digitalWrite(myStepPin, HIGH);
				myNumSteps++;
			}
		myLastStepTime = loopMicros;
		calculateNextStepParams();
	}
}

uint32_t map_uint32_t(uint32_t x, uint32_t in_min, uint32_t in_max,
		uint32_t out_min, uint32_t out_max) {
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void Stapper::calculateNextStepParams() {
	myActualRoundsPerMinute = myRoundsPerMinute;
	if (mySpeedType == CONSTANT) {
		myNewDirection = 1;
		if (loopMillis - myLastSetSpeed < myAccelerationDuration) {
			uint32_t time = loopMillis - myLastSetSpeed;
			if (myOldRoundsPerMinute == 0) {
				myOldRoundsPerMinute++;
			}
			myActualRoundsPerMinute = map(time, 0, myAccelerationDuration,
					myOldRoundsPerMinute, myRoundsPerMinute);
		}
	} else {
		uint32_t time = loopMillis - myLastSetSpeed;
		float angle = (((float) time) * 6.28) / ((float)mySinusDuration);
		float sinus = sin(angle);
		myActualRoundsPerMinute = abs(sinus) * myMaxRoundsPerMinute;
		sinus < 0 ? myNewDirection = LOW : myNewDirection = HIGH;
	}
//		Serial.print(time);
//		Serial.print(";");
//		Serial.print(myAccelerationDuration);
//		Serial.print(";");
//		Serial.print(myOldRoundsPerMinute);
////		Serial.print(";");
//		Serial.print(myRoundsPerMinute);
//		Serial.print(";");
//		Serial.println(myActualRoundsPerMinute);
	//usedRoundsPerMinute=usedRoundsPerMinute*(loopMillis-myLastSetSpeed/myAccelerationDuration);
	if (((int) (myActualRoundsPerMinute*100UL))== 0) {
		myNextStepDuration = 1000;
		myActualRoundsPerMinute=0;
	} else {
		uint32_t stepsPerMinute = myActualRoundsPerMinute
				* (uint32_t) myStepsPerRound;
		myNextStepDuration = 60000000UL / stepsPerMinute;
	}

//			Serial.print(stepsPerMinute);
//			Serial.print(";");
//			Serial.print(myNextStepDuration);
//			Serial.print(";");
//			Serial.print(myRoundsPerMinute);
//			Serial.print(";");
//			Serial.println(myActualRoundsPerMinute);

}

int16_t Stapper::getNumSteps() {
	int16_t ret = myNumSteps;
	myNumSteps = 0;
	return ret;

}

void Stapper::setSpeed(uint16_t roundsPerMinute,
		uint32_t accelerationDuration) {
	myNewRoundsPerMinute = roundsPerMinute;
	myNewAccelerationDuration = accelerationDuration;
	myNewSpeedType = CONSTANT;
	myNewLastSetSpeed = loopMillis;

}

void Stapper::setSinusSpeed(uint16_t maxRoundsPerMinute,
		uint32_t accelerationDuration, uint32_t sinusDuration) {
	myNewMaxRoundsPerMinute = maxRoundsPerMinute;
	myNewAccelerationDuration = accelerationDuration;
	myNewSinusDuration = sinusDuration;
	myNewSpeedType = SINUS;
	myNewLastSetSpeed = loopMillis;
}
