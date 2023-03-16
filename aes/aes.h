//
// Created by martian on 3/13/2023.
//
#ifndef AES_AES_H
#define AES_AES_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * Functions from aes.c
 */

uint8_t gfadd(uint8_t x, uint8_t y);
uint8_t gfmul(uint8_t x, uint8_t y);

/*
 * Other
 */

int gentable();

#endif //AES_AES_H
