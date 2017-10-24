#include <stdio.h>
#include <stdint.h>
int main() {
	volatile uint64_t s = 0xd;
	volatile uint64_t r;
	for (uint64_t i = 0; i < 1048576*1000; ++i) {
		uint64_t z = s;
		uint64_t y = 0xd;
		uint64_t x = 0xd;				
		x *= y; x *= y; x *= y; x *= y; x *= y; x *= y; x *= y; x *= y;
		x *= y; x *= y; x *= y; x *= y; x *= y; x *= y; x *= y; x *= y;
		x = z;
		x *= y; x *= y; x *= y; x *= y; x *= y; x *= y; x *= y; x *= y;
		x *= y; x *= y; x *= y; x *= y; x *= y; x *= y; x *= y; x *= y;
		x = z;
		x *= y; x *= y; x *= y; x *= y; x *= y; x *= y; x *= y; x *= y;
		x *= y; x *= y; x *= y; x *= y; x *= y; x *= y; x *= y; x *= y;
		x = z;
		x *= y; x *= y; x *= y; x *= y; x *= y; x *= y; x *= y; x *= y;
		x *= y; x *= y; x *= y; x *= y; x *= y; x *= y; x *= y; x *= y;
		x = z;
		x *= y; x *= y; x *= y; x *= y; x *= y; x *= y; x *= y; x *= y;
		x *= y; x *= y; x *= y; x *= y; x *= y; x *= y; x *= y; x *= y;
		x = z;
		x *= y; x *= y; x *= y; x *= y; x *= y; x *= y; x *= y; x *= y;
		x *= y; x *= y; x *= y; x *= y; x *= y; x *= y; x *= y; x *= y;
		x = z;
		x *= y; x *= y; x *= y; x *= y; x *= y; x *= y; x *= y; x *= y;
		x *= y; x *= y; x *= y; x *= y; x *= y; x *= y; x *= y; x *= y;
		x = z;
		x *= y; x *= y; x *= y; x *= y; x *= y; x *= y; x *= y; x *= y;
		x *= y; x *= y; x *= y; x *= y; x *= y; x *= y; x *= y; x *= y;
		r = x;
	}
	printf(r == 0x780c7372621bd74d ? "success\n\n" : "failure\n");
}
