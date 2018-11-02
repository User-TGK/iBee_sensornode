#include "Communication.h"
#include "Arduino.h"
#include <stdio.h>

RF24 radio(NRF_CEPIN, NRF_CSPIN);

unsigned long previousMillis, currentMillis, previousRequestMillis, currentRequestMillis = 0;
unsigned long responseTime = 6000;

void rf24Setup() {
    radio.begin();
    radio.setPALevel(POWER_LVL);
    radio.setDataRate(DATA_RATE);
    radio.setChannel(RADIO_CHANNEL);	
    radio.setPayloadSize(PAYLOAD_SIZE);	
    radio.openWritingPipe(TX_PIPE);	
    radio.openReadingPipe(1, RX_PIPE);
    radio.stopListening();
}

bool requestNonce(MDP MDPInstance, byte nodeId) {
    uint8_t nonceSize = 6;
    MDPMsg requestMessage;
    requestMessage.nodeId = nodeId;
    requestMessage.messageId = REQUESTID;
    char nonce[nonceSize];
    radio.stopListening();

    if (radio.write((byte*)&requestMessage, sizeof(MDPMsg))) {
        radio.startListening();
        currentRequestMillis = millis();
        while (!radio.available()) {
            currentRequestMillis = millis();
            // TIMEOUT: Waiting time runs out; no ack received so sending message failed
            if (currentRequestMillis - previousRequestMillis > responseTime) {
                radio.stopListening();
                return false;
            }
        }
        // Receiving and updating generated nonce from controller
        while (radio.available()) {
            radio.read(&nonce, nonceSize);
        }
        if (nonce == NULL) {
            return false;
        }
        MDPInstance.updateNonce(atoi(nonce));
        return true;
    }
    return false;
}

bool sendMessage(MDPMsg msg){
    uint8_t charSize = 3;
    char ack[charSize];  
    previousMillis = millis();  
    radio.stopListening();
    // Try to write a message to the gateway; continue if successfully sent
    if (radio.write((byte*)&msg, sizeof(MDPMsg))) {
        radio.startListening();
        currentMillis = millis();
        // Block while no incoming message; leave loop when receiving a message or time runs out
        while (!radio.available()) {
            currentMillis = millis();
            // TIMEOUT: Waiting time runs out; no ack received so sending message failed
            if (currentMillis - previousMillis > responseTime) {
                return 0;
            }
        }
        // Receiving an acknowledge message
        while (radio.available()) {
        radio.read(&ack, charSize);
        }
        // If the character was a 's', the message was sucessfully stored at the controller
        // Return 1 to confirm message sending was successfull
        if (ack[0] == 's'){ 
            return 1; 
        }
        // If it wasn't an 's', the message was not sucessfully handled by the controller
        // Return 0 so the program understands the message has to be send again
        else { 
            return 0; 
        }
    }
    // If the message wasn't successfully sent return 0
    else {
        return 0;
    }
}