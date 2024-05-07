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


void Brains::setup(){

}

void Brains::loop(){
	switch (myState){
	case 0:
		changeToState1();
		break;
	}
}


void Brains::changeToState1(){
	Serial.println("changing to state 1");
	myState=1;
	myLastStateChange=loopMillis;
	myStapper.setSpeed(10, 500);
}
void Brains::changeToState2(){
	Serial.println("changing to state 2");
	myState=2;
	myLastStateChange=loopMillis;
	myStapper.setSpeed(20, 500);
}
void Brains::changeToState3(){
	Serial.println("changing to state 3");
	myState=3;
	myLastStateChange=loopMillis;
	myStapper.setSpeed(30, 500);
}
void Brains::changeToState4(){
	Serial.println("changing to state 4");
	myState=4;
	myLastStateChange=loopMillis;
	myStapper.setSpeed(40, 500);
}

