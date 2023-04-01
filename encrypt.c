//
// Created by varya on 3/29/2023.
//

#include "constants.h"
#include <stdlib.h>
#include <stdio.h>

// Number of columns in the state array
static const unsigned char N_b = 0x4;


/*
 * hexStr: The hex string to pass.
 * byteArr: The unsigned char array of size strlen(hexStr)/2.
 * byteArrLen:
 */

void transpose(uint8_t* in);

void hexify(const char* hexStr, uint8_t* byteArr, size_t byteArrLen) {
	for (size_t i = 0; i < byteArrLen; i++) {
		char buf[5] = {hexStr[0], hexStr[1]};
		byteArr[i] = (uint8_t)strtol(buf, NULL, 16);
		hexStr += 2 * sizeof(char);
	}
}

void xprintf(uint8_t* byteArr, size_t byteArrLen) {
	transpose(byteArr);
	for (int i = 0; i < byteArrLen/N_b; i++) {
		for (int j = 0; j < byteArrLen/N_b; j++) {
			printf("%02x", byteArr[i * N_b + j]);
		}
	}
}

void transpose(uint8_t* in) {
	for (int i = 0; i < 4; i++) {
		for (int j = i + 1; j < 4; j++) {			// in-place transpose, i < j < 4, out-of-place transpose 0 <= j < 4
			uint8_t temp = in[i * N_b + j];
			in[i * N_b + j] = in[j * N_b + i];
			in[j * N_b + i] = temp;
			//stateArr[j * N_b + i] = in[i * N_b + j];
		}
	}
}