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

}

void Brains::loop() {
	boolean changeState=myState == 0;
	if(mySwitch.isClosed()){
		if(!myIsWitchClosed){
			changeState=true;
			myIsWitchClosed=true;
		}

	}else{
		myIsWitchClosed=false;
	}

	if (changeState) {
		Serial.print("changing from state ");
		Serial.print(myState);
		myLastStateChange = loopMillis;
		switch (myState) {
		case 0:
			changeToState1();
			break;
		case 1:
			changeToState2();
			break;
		case 2:
			changeToState3();
			break;
		case 3:
			changeToState4();
			break;
		case 4:
			changeToState1();
			break;
		}
		Serial.print(" to state ");
		Serial.println(myState);
	}
}

void Brains::changeToState1() {
	myState = 1;
	myStapper.setSpeed(10, 500);
}
void Brains::changeToState2() {
	myState = 2;
	myStapper.setSpeed(20, 500);
}
void Brains::changeToState3() {
	myState = 3;
	myStapper.setSpeed(30, 500);
}
void Brains::changeToState4() {
	myState = 4;
	myStapper.setSpeed(40, 500);
}

