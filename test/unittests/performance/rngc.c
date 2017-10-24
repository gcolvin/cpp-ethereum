#include <stdint.h>
#include <stdio.h>

// magic seeds
static uint64_t shub = 0x5641821b9ff55d5d;
static uint64_t blum[5] = { 0xe337647ebb3cc5c3,
					  		0x8e59c4a23cd403a9,
							0xe5467b61748316db,
							0x8df2ed127339c83b,
							0x93b1669be4ff87b1 };

// force memory access
static volatile unsigned char out[5][32];

// 2**20 tests
int main(int argc, char** argv) {

	blum[0] += argc;

	for (int i = 0; i < 32768*1000; ++i) {

		// need 32 bytes of output for each log argument
		for (uint64_t j = 0; j < 32; ++j) {
		
			// harvest low order byte of 5 Blum Blum Shubs for 5-word log output
			for (int l = 0; l < 5; ++l) {		
				uint64_t bbs = blum[l];
				bbs *= bbs;
				bbs %= shub;
				blum[l] = bbs;
				out[l][j] = (bbs & 0x255);
			}
		}
	}
	return out[4][31];
}
