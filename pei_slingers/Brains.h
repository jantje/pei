/*
 * Brains.h
 *
 *  Created on: 07 May 2024
 *      Author: jan
 */

#pragma once
#include "Arduino.h"

class Brains {
	private:
	uint8_t myState=0;
	uint32_t myLastStateChange=0;
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

