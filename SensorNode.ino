/* 
* ------------------------------- iBee - 2017/2018 Ⓒ---------------------------------
*
* Project: iBee
* Date: 06-12-2017
* Libraries: nRF24L01, RF24, SPI
* Hardware: Arduino Mini 5V, NRF24L01, DHT22 (9x), magnetic read switch
* Description: The code for the sensornode to be implemented in beehives. In file 'config.h' the configuration for the RF chip, 
* sensor and other settings can be set. In this file contains the main (setup and loop functions in arduino);
*
* -------------------------------------------------------------------------------
*/

/* Contains all functionality to read out attatched sensors */
#include "Sensor.h"

/* Contains all functionality to MDP messages */
#include "Communication.h"

/* Timestamps which will determine when a MDP message group is send */
unsigned long previousMDP, currentMDP = 0;

/* The pre-shared key that is shared with the controller in advance of exchanging messages */
char PSK[9] = "A&lhNq4M";

/* The protocol instance wich creates the MDP messages */
MDP MDPInstance = MDP(byte(NODEID), 0, PSK);

/* Float array of payloads wich passes sensor values (from sensor.cpp) to MDP messages (MDP.cpp) */
float payload [NROFPAYLOADS];

/*
* @Desc function which creates the Measurement Data Protocol messages
*/
void createMessages() {
    for (uint8_t i = 0; i < nrOfMDPMessages; i++) {
        getPayload(payload, i);
        MDPInstance.createMessage(byte(i), payload);
    }
}

/*
* @Desc function which tries to send all MDP messages. Before doing so,
* the function will call a function to request a nonce, creates the MDP messages,
* and eventually give each message 5 opportunities to get to the controller
*/
void sendMessages() {
    if (requestNonce(MDPInstance, byte(NODEID))) {
        createMessages();
        //MDPInstance.printStoredMessages();
        uint8_t attempt;
        bool result;

        for(uint8_t i = 0; i < NROFMDPMESSAGES; i++) {
            attempt = result = 0;
            result = sendMessage(MDPInstance.storedMessages[i]);
            if(result == 1) { 
                continue; 
            }
            else if (result == 0 && attempt < maxNrOfRetries) {
                while (attempt <= maxNrOfRetries && result == 0) {
                    result = sendMessage(MDPInstance.storedMessages[i]);
                    attempt += 1;
                }
                continue;   
            }
            else {
                continue;
            }
        }
     }
    else {
        return;
    }
}

/* 
* @Desc Setup function of the main (.ino) program: function will initialize Serial communication, 
* and call functions which ensure setup of RF chip and all attachted sensors (and interrupts)
*/
void setup() {
    Serial.begin(115200);
    sensorsSetup();
    rf24Setup();
    attachInterrupt(digitalPinToInterrupt(REEDPIN), sendMessages, CHANGE);
}

/*
* @Desc The loop function will call the sendMessages function after a certain interval has passed
*/
void loop() {
    currentMDP = millis();
    if (currentMDP - previousMDP >= SENDINTERVAL) {
        sendMessages();
        previousMDP = currentMDP;
    }
}