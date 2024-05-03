/*
 * Brains.h
 *
 *  Created on: 02 May 2024
 *      Author: jan
 */
#include "arduino.h"
#pragma once

#define BEFORE_PAUZE 0
#define IN_PAUZE 1
#define AFTER_PAUZE 2

class Brains {
private:
	uint32_t mySketchDuration;
	uint32_t myPauzeDuration;

	uint32_t mySketchTriggerTime=0;
	uint32_t myPauzeTriggerTime=0;
	uint8_t myPauzeState; //0=before pauze 1= in pauze 2=after pauze


public:
	Brains(	uint32_t sketchDuration, uint32_t pauzeDuration);
	virtual ~Brains();
	void setup();
	void loop();
};
