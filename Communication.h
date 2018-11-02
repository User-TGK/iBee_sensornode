/* 
* ------------------------------- iBee - 2017/2018 Ⓒ---------------------------------
* Date: 06-12-2017
* Description: the communication module ensures MDP messages can be send via the RF24 chip.
* the module contains functionalities for requesting a nonce and sending MDP messages.
* This is the only module that creates communication with a controller.
*
*/

#ifndef COMMUNICATION_H
#define COMMUNICATION_H

/* SPI bus is used for a connection to the sound measurement chip and the RF24 chip */
#include <SPI.h>

/* RF24 library to use RF24 functionality in an easy way */
#include "RF24.h"

/* MDP contains the message protocol implementation and configuration for the communication */
#include "MDP.h"

/*
* @Desc function that will execute the setup for the RF24 chip. Among other things,
* the datarate and power usage of the RF24 chip will be set in this function. 
*/
void rf24Setup();

/*
* @Desc function that will request a nonce at the controller so the controller will be able to
* authenticate this certain node.
* @Param MDPInstance the instance of the MDP that needs a nonce
* @Param nodeId the nodeId of the beehive that needs a (new) nonce
* @Return true if the nonce was sucessfully requested and updated, false if not
*/
bool requestNonce(MDP MDPInstance, byte nodeId);

/*
* @Desc function that will send a certain MDPMsg to the controller
* @Param msg the MDP message to be send
* @Return true if the message was sucessfully send and acknowledged, false if:
* 1) the message wasn't received, 2) the message was invalid, 3) the message contained invalid values
*/
bool sendMessage(MDPMsg msg);

#endif