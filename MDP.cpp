#include "MDP.h"
#include "Authentication.h"

MDP::MDP(byte aNodeId, uint16_t aNonce, char aPSK[NROFPSKTOKENS]):
    nodeId(aNodeId), nonce(aNonce) {
    
    for (uint8_t i = 0; i < NROFPSKTOKENS; i++) {
        this->PSK[i] = aPSK[i];
    }
}

void MDP::createMessage(byte messageId, float payload[NROFPAYLOADS]) {
    static MDPMsg newMessage;
    newMessage.nodeId = nodeId;
    newMessage.messageId = messageId;
    newMessage.nonce = myhash(nonce, this->PSK);

    for (uint8_t i = 0; i < NROFPAYLOADS; i++) {
        newMessage.payload[i] = payload[i];
    }
    storedMessages[messageId] = newMessage;
}

void MDP::reset() {
    for (uint8_t i = 0; i < 4; i++) {
        for (uint8_t j = 0; j < NROFPAYLOADS; j++) {
            this->storedMessages[i].payload[j] = 0.0;
        }
    }
}

void MDP::updateNonce(uint16_t newNonce) {
    this->nonce = newNonce;
}

void MDP::printStoredMessages() {
    for (uint8_t i = 0; i < NROFMDPMESSAGES; i ++) {
        Serial.print(this->storedMessages[i].nodeId);
        Serial.print(" ");
        Serial.print(this->storedMessages[i].messageId);
        Serial.print(" ");
        Serial.print(this->storedMessages[i].nonce);
        for (uint8_t j = 0; j < NROFPAYLOADS; j ++) {
            Serial.print(" ");
            Serial.print(this->storedMessages[i].payload[j]);
        }
        Serial.println();
    }
}