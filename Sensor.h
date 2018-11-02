/* 
* ------------------------------- iBee - 2017/2018 Ⓒ---------------------------------
* Date: 06-12-2017
* Description: the Sensor module contains all functionality to read all attached sensors in the form of an MDP payload
*
*/

#ifndef SENSOR_H
#define SENSOR_H

#pragma once
#include "Mux.h"
#include "Config.h"
#include "MDP.h"
/* 
* @Desc Function that declares the pinmodes for the sensors
*/
void sensorsSetup(void);

/*
* @Desc function that will return an MDP payload for a certain MDP message
* @Param storagePayload the array the payload has to be stored in
* @Param messageId the messageId of the payload
*/
void getPayload(float storagePayload[NROFPAYLOADS], uint8_t messageId);

/* 
* @Desc Function that reads the potmeter (to simulate weight changes)
* @Return integer mapped to simulate 0-50kg.
*/
float getWeight(void);

#endif