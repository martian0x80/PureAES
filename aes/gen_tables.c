#include "gen_table.h"

uint8_t gfaddTable[0xff][0xff];
uint8_t gfmulTable[0xff][0xff];

void print_table(uint8_t arr[][0xff]);
void write_table(uint8_t arr[][0xff], FILE* fstream_s);

int gentable(void) {
	for (int i = 0; i < 0xff; i++) {
		for (int j = 0; j < 0xff; j++) {
			gfaddTable[i][j] = gfadd((uint8_t)i, (uint8_t)j);
		}
	}
	for (int i = 0; i < 0xff; i++) {
		for (int j = 0; j < 0xff; j++) {
			gfmulTable[i][j] = gfmul((uint8_t)i, (uint8_t)j);
		}
	}
	//print_table(gfaddTable);
	// File to write the table to.
	FILE* fstream = fopen("table.txt", "w");
	write_table(gfaddTable, fstream);
	fclose(fstream);
	return 0;
}

void write_table(uint8_t arr[][0xff], FILE* fstream_s) {
	for (int i = 0; i < 0xff; i++) {
		for (int j = 0; j < 0xff; j++) {
			fprintf(fstream_s, "%x, ", arr[i][j]);
		}
		fprintf(fstream_s, "\n");
	}
}

void print_table(uint8_t arr[][0xff]) {
	for (int i = 0; i < 0xff; i++) {
		for (int j = 0; j < 0xff; j++) {
			printf("%x, ", arr[i][j]);
		}
		printf("\n");
	}
}