/* 
* ------------------------------- iBee - 2017/2018 Ⓒ---------------------------------
* Date: 06-12-2017
* Description: this header file contains all configuration that is used for either the communication (NRF24) or MDP
*
*/

#ifndef MDPCONFIG_H
#define MDPCONFIG_H

// ------**** NRF24L01 CHIP SETTINGS ****------//

#define RADIO_CHANNEL 71
#define POWER_LVL     RF24_PA_MAX
#define DATA_RATE     RF24_2MBPS
#define PAYLOAD_SIZE  32
#define NRF_CEPIN     9
#define NRF_CSPIN     10
#define TX_PIPE       0xB3B4B5B6F1LL
#define RX_PIPE       0xF0F0F0F0A2LL

// ------**** MDP SETTINGS ****------//

#define NROFMDPMESSAGES 4
#define NROFPAYLOADS 7
#define REQUESTID 255
#define NROFPSKTOKENS 9

#endif