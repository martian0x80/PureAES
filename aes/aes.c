// aes.x : This file contains the 'main' function. Program execution begins and ends there.
//

#include "aes.h"

// 1 word = 4 bytes = 32 bits
const unsigned char N_w = 0x20;

// Block size in words (:= 4 bytes = 32 bits = 128 bit), constant for all N_k sizes
const unsigned char N_b = 0x4;

// Key size/length, belongs in {4, 6, 8} words = {16, 24, 32} bytes = {128, 192, 256} bits
const unsigned char N_k;

// Number of rounds, a function of N_k, belongs in {10, 12, 14}
const unsigned char N_r;

// Reduction Irreducible polynomial GF(2^8)
const uint16_t PP = 0x11b;

/*
 * The addition of two elements in a finite field is achieved by adding the coefficients for the
 * corresponding powers in the polynomials for the two elements. The addition is performed with
 * the XOR operation (denoted by + ).
 * Alternatively, addition of finite field elements can be described as the modulo 2 addition of
 * corresponding bits in the byte. For two bytes {a7a6a5a4a3a2a1a0} and {b7b6b5b4b3b2b1b0}, the sum is
 * {c7c6c5c4c3c2c1c0}, where each ci = ai + bi (i.e., c7 = a7 + b7, c6 = a6 + b6, ...c0 = a0 + b0).
 * {01010111} + {10000011} = {11010100} (binary notation);
 * {57} + {83} = {d4} (hexadecimal notation)
 */

uint8_t gfadd(uint8_t byte1, uint8_t byte2) {
    return byte1 ^ byte2;
}

/*
 * 	Russian Peasant Multiplication
 * 	Based on the pseudo code explained in https://www.wikiwand.com/en/Finite_field_arithmetic#Rijndael's_(AES)_finite_field
 */
uint8_t gfmul(uint8_t x, uint8_t y) {
    uint8_t p = 0; // p is the product
    while (x != 0 && y != 0) {
        uint8_t carry = 0;
        if (y & 0x01) {
            p ^= x;
        }
        y >>= 1;
        if (x & 0x80) {
            carry = 1;
        }
        x <<= 1;
        if (carry) {
            x ^= PP;
        }
    }
    return p;
}

/*
 * 	Multiply the binary polynomial by x, which is equivalent to multiplication by 0x02 or 0b10.
 */
uint8_t xtime(uint8_t x) {
	return gfmul(x, 0x02);
}

/*
 * Addition of 'words' in GF(2^8), when the coefficients of the polynomial belong to GF(2^8) themselves.
 * Each word is a 32-bit integer, and the coefficients are the bytes of the word. Unlike the addition of
 * two bytes (gfmul() does this; binary polynomials in GF(2^8), the addition of two words is not simply the XOR of the corresponding bytes.
 * If a(x) = a^3 x^3 + a^2 x^2 + a^1 x^1 + a^0 x^0 and b(x) = b^3 x^3 + b^2 x^2 + b^1 x^1 + b^0 x^0, then
 * a(x) + b(x) = (a^3 + b^3) x^3 + (a^2 + b^2) x^2 + (a^1 + b^1) x^1 + (a^0 + b^0) x^0
 * Here, + is equivalent to XOR, and the coefficients of the polynomial are the bytes of the word.
 */
void gfadd_words(uint8_t* a, uint8_t* b, uint8_t* c) {
	/*
	c[0] = a[0] ^ b[0];
	c[1] = a[1] ^ b[1];
	c[2] = a[2] ^ b[2];
	c[3] = a[3] ^ b[3];
	*/

	// This is apparently equivalent to
	*(uint32_t *)c = *(uint32_t *)a ^ *(uint32_t *)b;
}

/*
 * Multiplication of 'words' in GF(2^8), when the coefficients of the polynomial belong to GF(2^8) themselves.
 * If a(x) = a^3 x^3 + a^2 x^2 + a^1 x^1 + a^0 x^0 and b(x) = b^3 x^3 + b^2 x^2 + b^1 x^1 + b^0 x^0, then
 * c(x) = a(x) * b(x) = c_6 x^6 + c_5 x^5 + c_4 x^4 + c_3 x^3 + c_2 x^2 + c_1 x^1 + c_0 x^0
 * where c_6 = a^3 b^3 + a^2 b^2 + a^1 b^1 + a^0 b^0
 * 		 c_5 = a^3 b^2 + a^2 b^1 + a^1 b^0
 * 				...
 * 		 c_0 = a^0 b^0
 * This product is reduced by applying mod(x^4 + 1)
 *
 * Inset matrix product representation here
 */
void gfmul_words(uint8_t a[], uint8_t b[], uint8_t c[]) {
	c[0] = gfmul(a[0], b[0]) ^ gfmul(a[3], b[1]) ^ gfmul(a[2], b[2]) ^ gfmul(a[1], b[3]);
	c[1] = gfmul(a[1], b[0]) ^ gfmul(a[0], b[1]) ^ gfmul(a[3], b[2]) ^ gfmul(a[2], b[3]);
	c[2] = gfmul(a[2], b[0]) ^ gfmul(a[1], b[1]) ^ gfmul(a[0], b[2]) ^ gfmul(a[3], b[3]);
	c[3] = gfmul(a[3], b[0]) ^ gfmul(a[2], b[1]) ^ gfmul(a[1], b[2]) ^ gfmul(a[0], b[3]);
}

void SubBytes() {}

int main(int argc, char **argv)
{	/*
	if (argc < 3) {
		printf("Insufficient args.\n");
	} else {
		int x = (int)strtol(argv[1], NULL, 16);
		int y = (int)strtol(argv[2], NULL, 16);
		printf("Polynomial multiplication in GF(2^8):\n\t {%x} * {%x} = {%x}\n", x, y, gfmul(x,y)); 
	}
 */
    //printf("%x\n", gfmul(0x57, 0x83));
    //printf("%x", xtime(xtime(0x57)));
    return 0;
}
