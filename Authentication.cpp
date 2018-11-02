#include "Authentication.h"
#include <stdio.h>

#define MAGIC		0xB819
#define START_VAL	0x7F03

/**
 * @Desc Function that rotates the value using a bitshift.
 * @param a contains a int number of the w2 array
 * @param a number that will be used to rotate the value.
 * @return a rotated number 
 */
static uint16_t lrotate(uint16_t a, uint8_t n) {
	return (a << n) | (a >> (16 - n));
}

uint16_t myhash(uint16_t nonce, char nodePSK[9]) {
	unsigned char w2[8];
	memcpy(w2, nodePSK, 8);
	uint16_t ret = START_VAL;

	for (uint8_t i = 0; i < 8; i++) {
		w2[i] = MAGIC % w2[i];
		w2[i] = lrotate(w2[i], i);
		if (i & 2) {
			w2[i] ^= nonce & 0xFF;
		} else {
			w2[i] ^= nonce >> 8;
		}
		w2[i] = lrotate(w2[i], 3);
	}
	ret += w2[0];
	ret += w2[1];
	ret += w2[6];
	ret += w2[7];
	ret += (uint16_t)(w2[2]) << 8;
	ret += (uint16_t)(w2[3]) << 8;
	ret += (uint16_t)(w2[4]) << 8;
	ret += (uint16_t)(w2[5]) << 8;

	lrotate(ret, 4);
	return ret;
}