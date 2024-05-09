/*
 * Brains.h
 *
 *  Created on: 07 May 2024
 *      Author: jan
 */

#pragma once
#include "Arduino.h"
#define TOTAL_STATES 4
#define EEPROM_WRITE_LOCATION 0

class Brains {
	private:
	uint8_t myState=TOTAL_STATES+1;
	uint8_t myNewState=0;
	uint32_t myLastStateChange=0;
	boolean myIsWitchClosed=false;
public:
	Brains();
	virtual ~Brains();
	void setup();
	void loop();
	uint8_t getState(){return myState;}
	void changeToState1();
	void changeToState2();
	void changeToState3();
	void changeToState4();
};

