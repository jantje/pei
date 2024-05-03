/*
 * WasMachine.cpp
 *
 *  Created on: 02 May 2024
 *      Author: jan
 */
#include "pei_wasmachine.h"
#include "WasMachine.h"

WasMachine::WasMachine(uint8_t pin, uint32_t startDelay, uint32_t onTime,
		uint32_t restartDelay) {
	myPin = pin;
	myActualStartTime = 0;
	myRequiredStartDelay = startDelay;
	myRequiredRestartDelay = restartDelay;
	myRequiredOnTime = onTime;
	myIsRunning = false;
	myIsPauzed = false;
	myIsRunningRequested = false;
	myIsPauzedRequested = false;
	myIsPauzedStopRequested = false;
	myActualPinState = LOW;
}

WasMachine::~WasMachine() {
}

void WasMachine::pauze() {
	myIsPauzedRequested = true;
}

void WasMachine::stopPauze() {
	myIsPauzedStopRequested = true;
}

void WasMachine::start() {
	myIsRunningRequested = true;
}

void WasMachine::stop() {
	myIsRunningRequested = false;
}

void WasMachine::setup() {
	pinMode(myPin, OUTPUT);
}

void WasMachine::loop() {
	uint8_t calcState = expectedPinState();

	if (myIsRunningRequested && !myIsRunning) {
		//request to start running
		myIsRunning = true;
		myActualStartTime = loopMillis;
	}
	if (myIsPauzedRequested && !myIsPauzed) {
		//request to pauze
		myIsPauzed = true;
		setMotor( LOW);
	}
	if (myIsPauzedStopRequested && myIsPauzed) {
		//request to end pauze
		myIsPauzed = false;
		setMotor(calcState);
	}
	myIsRunningRequested = false;
	myIsPauzedRequested = false;
	myIsPauzedStopRequested = false;

	if (myIsPauzed) {
		return;
	}
		setMotor(calcState);

}

uint8_t WasMachine::expectedPinState() {


	uint32_t correctedMillis= loopMillis - myActualStartTime - myRequiredStartDelay;
	uint32_t cycleTime= myRequiredOnTime + myRequiredRestartDelay;

//	static uint32_t lastPlot;
//	if(loopMillis-lastPlot>=1000){
//		lastPlot=loopMillis;
//		plot3(Serial,correctedMillis,myRequiredOnTime,
//				correctedMillis% cycleTime);
//		Serial.print(correctedMillis);
//		Serial.print("  ");
//		Serial.print(myRequiredOnTime);
//		Serial.print("  ");
//		Serial.print(myRequiredRestartDelay);
//		Serial.print("  ");
//		Serial.print(cycleTime);
//				Serial.print("  ");
//		Serial.println(	correctedMillis% cycleTime);
//	}


	if (loopMillis < myActualStartTime + myRequiredStartDelay) {
		//waiting for first start
		return LOW;
	}
	if ((correctedMillis% cycleTime) < myRequiredOnTime) {
		return HIGH;
	}
	return LOW;
}

void WasMachine::setMotor(uint8_t pinState) {
	if (myActualPinState != pinState) {
		digitalWrite(myPin, pinState);
		myActualPinState = pinState;
		Serial.print("pin ");
		Serial.print(myPin);
		if (myActualPinState == LOW) {
			Serial.println(" LOW");
		} else {
			Serial.println(" HIGH");
		}
	}
}
