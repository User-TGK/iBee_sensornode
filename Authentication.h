#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include <stdint.h>
#include <string.h>

/**
 * @Desc Function that returns a binary hash based of a key and a nonce value..
 * @param nonce contains a random number that is generated in linux.
 * @return uint16_t Returns a binary hash value
 */

uint16_t myhash(uint16_t nonce, char nodePSK[9]);

#endif