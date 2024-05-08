/*
 * Stapper.h
 *
 *  Created on: 05 May 2024
 *      Author: jan
 */

#pragma once

#include "Arduino.h"


class Stapper {
private :
	uint8_t myStepPin;
	uint8_t myDirectionPin;
	uint8_t myEnablePin;
	uint16_t myStepsPerRound;

	uint16_t myNewRoundsPerMinute=0;
	uint32_t myNewAccelerationDuration=0;
	uint32_t myNewLastSetSpeed=0;
	uint16_t myRoundsPerMinute=0;
	uint32_t myAccelerationDuration=0;
	uint32_t myLastSetSpeed=0;
	uint32_t myLastAccelerationDuration=0;
	uint32_t myNextStepDuration=0;  //time till the step pin needs to be set high
	uint32_t myLastStepTime=0;
	int16_t myDirection=0;
	int16_t myNumSteps=0;
	boolean myHasStepped=false;
private :
	void calculateNextStepParams();
public:
	Stapper(uint8_t stepPin, uint8_t directionPin, uint8_t enablePin,uint16_t stepsPerRound);
	virtual ~Stapper();
	void setup();
	void loop();
	void setSpeed(uint16_t roundsPerMinute,uint32_t accelerationDuration);
	int16_t getDirection(){return myDirection;};
	int16_t getNumSteps();
};

