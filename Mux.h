/* 
* ------------------------------- iBee - 2017/2018 Ⓒ---------------------------------
* Date: 06-12-2017
* Description: the Mux module contains all functionality to read all attached sensors attached to the multiplexer 
*
*/

#ifndef MUX_H
#define MUX_H

#include "Arduino.h"
#include <DHT.h>
#pragma once

#define MUX_S0 4
#define MUX_S1 5
#define MUX_S2 6

#define MUX_PINS_USED 7

/* 
* @Desc Function that declares the pinmodes for the muxpins
*/
void muxSetup(void);

/*
* @Desc Function that reads a temperaturevalue via multiplexer
* @Param &dht Dht object needed for functioncall
* @Param muxPin the muxpin to be called
* @Return Temperaturevalue of a single sensor
*/
float readMuxTemp(DHT &dht, uint8_t muxPin);

/* 
* @Desc Function that reads a humidityvalue via multiplexer
* @Param Dht object needed for functioncall
* @Param muxPin the muxpin to be called
* @Return Humidityvalue of a single sensor
*/
float readMuxHum(DHT &dht, uint8_t muxPin);

#endif