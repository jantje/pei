/*
 * Brains.cpp
 *
 *  Created on: 02 May 2024
 *      Author: jan
 */

#include "pei_wasmachine.h"
//number of miliseconds one needs to be in the sketch
//before the pauze can start
#define WAIT_TIME 789

Brains::Brains(uint32_t sketchDuration, uint32_t pauzeDuration) {
	myPauzeDuration = pauzeDuration;
	mySketchDuration = sketchDuration;
	myPauzeState=AFTER_PAUZE;
	mySketchTriggerTime=0;
}

Brains::~Brains() {
}

void Brains::setup() {
	randomSeed(analogRead(0));
}

void Brains::loop() {


	switch (myPauzeState){
	case AFTER_PAUZE:{
		if(loopMillis>mySketchTriggerTime){
			myPauzeTriggerTime=mySketchTriggerTime+WAIT_TIME+random(mySketchDuration-myPauzeDuration-WAIT_TIME);
			mySketchTriggerTime=mySketchTriggerTime+mySketchDuration;
			myPauzeState=BEFORE_PAUZE;
		}
		break;
	}
	case BEFORE_PAUZE:{
		if(loopMillis>myPauzeTriggerTime  ){
			myPauzeState=IN_PAUZE;
			wasMachine_1.pauze();
			wasMachine_2.pauze();
			wasMachine_3.pauze();
			wasMachine_4.pauze();
		}
		break;
	}
	case IN_PAUZE:{
		if(  loopMillis>(myPauzeTriggerTime +myPauzeDuration)){
			myPauzeState=AFTER_PAUZE;
			wasMachine_1.stopPauze();
			wasMachine_2.stopPauze();
			wasMachine_3.stopPauze();
			wasMachine_4.stopPauze();
		}
	}
	}




}
