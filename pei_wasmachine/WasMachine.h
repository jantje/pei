/*
 * WasMachine.h
 *
 *  Created on: 02 May 2024
 *      Author: jan
 */

#include "Arduino.h"
#pragma once

class WasMachine {
private:
	uint8_t myPin;
	uint8_t myActualPinState;
	uint32_t myActualStartTime;
	uint32_t myRequiredStartDelay;
	uint32_t myRequiredRestartDelay;
	uint32_t myRequiredOnTime;
	boolean myIsRunning;
	boolean myIsPauzed;
	boolean myIsRunningRequested;
	boolean myIsPauzedRequested;
	boolean myIsPauzedStopRequested;

public:
	WasMachine(uint8_t pin, uint32_t startDelay, uint32_t onTime,
			uint32_t restartDelay);
	virtual ~WasMachine();
	void pauze();
	void stopPauze();
	void start();
	void stop();
	void setup();
	void loop();
	int16_t getActualPinValue(){return myActualPinState;}
private:
	uint8_t expectedPinState();
	void setMotor(uint8_t pinState);
};
