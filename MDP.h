/* 
* ------------------------------- iBee - 2017/2018 Ⓒ---------------------------------
* Date: 06-12-2017
* Description: the MDP protocol is implemented with a class MDP that contains all non-message-specific configuration,
* such as node_id and nonce. The class also contains an array of all seperate messages, that are implemented by a struct
*
*/

#ifndef MDP_h
#define MDP_h

#include "Arduino.h"
#include "MDPConfig.h"
#pragma once

/* Any instance of this struct represents a single MDP message */
struct MDPMsg
{
  byte nodeId;	
  byte messageId;
  uint16_t nonce;
  float payload[NROFPAYLOADS];
};

class MDP {
public:
    /*
    * @Desc Constructor of MDP. Create a new MDP instance each time a valid nonce is requested.
    * @Param aNodeId the node id of the beehive the node is placed in.
    * @Param aNonce the (valid) nonce to authenticate your beehive.
    * @Param aPSK the pre-shared key to be set for this node (shared with controller in advance).
    */
    MDP(byte aNodeId, uint16_t aNonce, char aPSK[NROFPSKTOKENS]);

    /* 
    * @Desc function that creates a new MDP message.
    * @Param messageId a valid message id is required for your new MDP message.
    * @Param payload an array of payloads that contains the data to be send.
    */
    void createMessage(byte messageId, float payload[NROFPAYLOADS]);
   
    /*
    * @Desc function that resets the set payloads of the MDP instance.
    */
    void reset();

    /*
    * @Desc function that prints the stored MDP messages
    */
    void printStoredMessages();

    /*
    * @Desc function that updates the set nonce with a new nonce
    * @Param newNonce the new nonce that replaces the old one
    */
    void updateNonce(uint16_t newNonce);

     /* An array that stores the created MDP messages.*/
     MDPMsg storedMessages[NROFMDPMESSAGES];

private:
    /* The node id of the beehive the node is placed in. */
    byte nodeId;
    /* The (valid) nonce to authenticate your node. */
    uint16_t nonce;
    /* The pre-shared key with the controller. Has to be set in the main (.ino) file */
    char PSK[NROFPSKTOKENS];
};

#endif