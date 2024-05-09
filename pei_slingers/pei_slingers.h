/*
 * pei_slingers.h
 *
 *  Created on: 05 May 2024
 *      Author: jan
 */
#pragma once

#include "Arduino.h"
#include "Stapper.h"
#include "Brains.h"
#include "SimpleSwitch.h"
#include "SimPlot.h"
#include "EEPROM.h"

#define SECONDS   *1000UL
#define MINUTES  *60000UL

extern uint32_t loopMillis;
extern uint32_t loopMicros;
extern Stapper myStapper;
extern SimpleSwitch mySwitch;

