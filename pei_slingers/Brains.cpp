/*
 * Brains.cpp
 *
 *  Created on: 07 May 2024
 *      Author: jan
 */

#include "pei_slingers.h"


Brains::Brains() {
	// TODO Auto-generated constructor stub

}

Brains::~Brains() {
	// TODO Auto-generated destructor stub
}

void Brains::setup() {
	uint8_t mem =EEPROM.get(EEPROM_WRITE_LOCATION, mem);
	if(mem > TOTAL_STATES){
		mem=0;
	}
	myNewState=mem;
}

void Brains::loop() {
	if (loopMillis - myLastStateChange > 1000) {
		//only change state once a second at most
		if (mySwitch.isClosed()) {
			if (!myIsWitchClosed) {
				myNewState=myState+1;
				if(myNewState>TOTAL_STATES){
					myNewState=1;
				}
				myIsWitchClosed = true;
			}

		} else {
			myIsWitchClosed = false;
		}
	}

	if (myNewState!=myState) {
		myLastStateChange = loopMillis;

		Serial.print("changing from state ");
		Serial.print(myState);
		Serial.print(" to state ");
		Serial.println(myNewState);
		myState=myNewState;
		EEPROM.put(EEPROM_WRITE_LOCATION, myState);


		switch (myState) {
		case 1:
			changeToState1();
			break;
		case 2:
			changeToState2();
			break;
		case 3:
			changeToState3();
			break;
		case 4:
			changeToState4();
			break;
		default:
			myState=1;
			myNewState=1;
			changeToState1();
			break;
		}

	}
}

void Brains::changeToState1() {
	myStapper.setSpeed(10, 20000);
}
void Brains::changeToState2() {
	myStapper.setSpeed(20, 20000);
}
void Brains::changeToState3() {
	myStapper.setSinusSpeed(45, 20000,10 MINUTES);
}
void Brains::changeToState4() {
	myStapper.setSinusSpeed(45, 20000,20 MINUTES);
}

