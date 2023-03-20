//
// Created by martian on 3/13/2023.
//
#ifndef AES_AES_H
#define AES_AES_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Extracting [i][j]th element from a two dimensional array represented as a one-dimensional array
#define GET_ELEM(arr, i, j, n) (arr[n * i + j])

/*
 * Functions from aes.c
 */
extern const uint16_t PP;

uint8_t gfadd(uint8_t x, uint8_t y);

uint8_t gfmul(uint8_t x, uint8_t y);

/*
 * Other
 */
int gentable(void);

void print_table(uint8_t *, uint8_t);

#endif //AES_AES_H
