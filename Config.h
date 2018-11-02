/* 
* ------------------------------- iBee - 2017/2018 Ⓒ---------------------------------
* Date: 06-12-2017
* Description: this header file contains all configuration that is not used for either the communication (NRF24) or MDP
*
*/

#ifndef CONFIG_H
#define CONFIG_H

/// ------**** SENSOR SETTINGS ****------//
// Type
#define DHT_TYPE      DHT11

// Analog
#define MUX_PIN       A0
#define POTPIN        A1

// Digital
#define SOLO_DHT_PIN  7
#define REEDPIN       8
#define PHOTO1_PIN    2
#define PHOTO2_PIN    3

/// ------**** FAILURE SETTINGS ****------//
#define maxNrOfRetries 3
#define nrOfMDPMessages 4

/// ------**** NODE SETTINGS ****------//

// The nodeID of the beehive. Must be in range 1 - 254
#define NODEID 30

// If the interval set has passed the MDP messages will be send again
#define SENDINTERVAL 10000

#endif