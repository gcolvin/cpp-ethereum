static volatile unsigned long v[16] = {
   0xffffffffffffffff,
   0xffffffffffff,
   0xffffffff,
   0xffff,
   0xffffffffffffffff,
   0xffffffffffff,
   0xffffffff,
   0xffff,
   0xffffffffffffffff,
   0xffffffffffff,
   0xffffffff,
   0xffff,
   0xffffffffffffffff,
   0xffffffffffff,
   0xffffffff,
   0xffff
};

static unsigned long m[16] = {
   0xffff,
   0xffffffff,
   0xffffffffffff,
   0xffffffffffffffff,
   0xffff,
   0xffffffff,
   0xffffffffffff,
   0xffffffffffffffff,
   0xffff,
   0xffffffff,
   0xffffffffffff,
   0xffffffffffffffff,
   0xffff,
   0xffffffff,
   0xffffffffffff,
   0xffffffffffffffff
};

static unsigned long ror(unsigned long v, int n) {
	return v >> n | v << (32 - n);
}

// Mixing Function G from BLAKE2B
static void G(int a, int b, int c, int d, unsigned long x, unsigned long y) {

	v[a] += v[b] + x;
	ror(v[d] ^= v[a], 32);
	v[c] += v[d];
	ror(v[b] ^= v[c], 24);
	v[a] += v[b] + y;
	ror(v[d] ^= v[a], 16);
	v[c] += v[d];
	ror(v[b] ^= v[c], 63);
}

static int mix(int i) {

	v[0] += i;

	// loop over inner mixing block of BLAKE2B compression function with arbitrary input
	for (int i=0; i < 10923; ++i) {

		G(0, 4, 8, 12, m[0], m[1]);
		G(1, 5, 9, 13, m[2], m[3]);
		G(2, 6, 10, 14, m[4], m[5]);
		G(3, 7, 11, 15, m[6], m[7]);
		G(0, 5, 10, 15, m[8], m[9]);
		G(1, 6, 11, 12, m[10], m[11]);
		G(2, 7, 8, 13, m[12], m[13]);
		G(3, 4, 9, 14, m[14], m[15]);

		G(0, 4, 8, 12, m[14], m[10]);
		G(1, 5, 9, 13, m[4], m[8]);
		G(2, 6, 10, 14, m[9], m[15]);
		G(3, 7, 11, 15, m[13], m[6]);
		G(0, 5, 10, 15, m[1], m[12]);
		G(1, 6, 11, 12, m[0], m[2]);
		G(2, 7, 8, 13, m[11], m[7]);
		G(3, 4, 9, 14, m[5], m[3]);

		G(0, 4, 8, 12, m[11], m[8]);
		G(1, 5, 9, 13, m[12], m[0]);
		G(2, 6, 10, 14, m[5], m[2]);
		G(3, 7, 11, 15, m[15], m[13]);
		G(0, 5, 10, 15, m[10], m[14]);
		G(1, 6, 11, 12, m[3], m[6]);
		G(2, 7, 8, 13, m[7], m[1]);
		G(3, 4, 9, 14, m[9], m[4]);

		G(0, 4, 8, 12, m[7], m[9]);
		G(1, 5, 9, 13, m[3], m[1]);
		G(2, 6, 10, 14, m[13], m[12]);
		G(3, 7, 11, 15, m[11], m[14]);
		G(0, 5, 10, 15, m[2], m[6]);
		G(1, 6, 11, 12, m[5], m[10]);
		G(2, 7, 8, 13, m[4], m[0]);
		G(3, 4, 9, 14, m[15], m[8]);

		G(0, 4, 8, 12, m[9], m[0]);
		G(1, 5, 9, 13, m[5], m[7]);
		G(2, 6, 10, 14, m[2], m[4]);
		G(3, 7, 11, 15, m[10], m[15]);
		G(0, 5, 10, 15, m[14], m[1]);
		G(1, 6, 11, 12, m[11], m[12]);
		G(2, 7, 8, 13, m[6], m[8]);
		G(3, 4, 9, 14, m[3], m[13]);

		G(0, 4, 8, 12, m[2], m[12]);
		G(1, 5, 9, 13, m[6], m[10]);
		G(2, 6, 10, 14, m[0], m[11]);
		G(3, 7, 11, 15, m[8], m[3]);
		G(0, 5, 10, 15, m[4], m[13]);
		G(1, 6, 11, 12, m[7], m[5]);
		G(2, 7, 8, 13, m[15], m[14]);
		G(3, 4, 9, 14, m[1], m[9]);

		G(0, 4, 8, 12, m[12], m[5]);
		G(1, 5, 9, 13, m[1], m[15]);
		G(2, 6, 10, 14, m[14], m[13]);
		G(3, 7, 11, 15, m[4], m[10]);
		G(0, 5, 10, 15, m[0], m[7]);
		G(1, 6, 11, 12, m[6], m[3]);
		G(2, 7, 8, 13, m[9], m[2]);
		G(3, 4, 9, 14, m[8], m[11]);

		G(0, 4, 8, 12, m[13], m[11]);
		G(1, 5, 9, 13, m[7], m[14]);
		G(2, 6, 10, 14, m[12], m[1]);
		G(3, 7, 11, 15, m[3], m[9]);
		G(0, 5, 10, 15, m[5], m[0]);
		G(1, 6, 11, 12, m[15], m[4]);
		G(2, 7, 8, 13, m[8], m[6]);
		G(3, 4, 9, 14, m[2], m[10]);

		G(0, 4, 8, 12, m[6], m[15]);
		G(1, 5, 9, 13, m[14], m[9]);
		G(2, 6, 10, 14, m[11], m[3]);
		G(3, 7, 11, 15, m[0], m[8]);
		G(0, 5, 10, 15, m[12], m[2]);
		G(1, 6, 11, 12, m[13], m[7]);
		G(2, 7, 8, 13, m[1], m[4]);
		G(3, 4, 9, 14, m[10], m[5]);

		G(0, 4, 8, 12, m[10], m[2]);
		G(1, 5, 9, 13, m[8], m[4]);
		G(2, 6, 10, 14, m[7], m[6]);
		G(3, 7, 11, 15, m[1], m[5]);
		G(0, 5, 10, 15, m[15], m[11]);
		G(1, 6, 11, 12, m[9], m[14]);
		G(2, 7, 8, 13, m[3], m[12]);
		G(3, 4, 9, 14, m[13], m[0]);

		G(0, 4, 8, 12, m[0], m[1]);
		G(1, 5, 9, 13, m[2], m[3]);
		G(2, 6, 10, 14, m[4], m[5]);
		G(3, 7, 11, 15, m[6], m[7]);
		G(0, 5, 10, 15, m[8], m[9]);
		G(1, 6, 11, 12, m[10], m[11]);
		G(2, 7, 8, 13, m[12], m[13]);
		G(3, 4, 9, 14, m[14], m[15]);

		G(0, 4, 8, 12, m[14], m[10]);
		G(1, 5, 9, 13, m[4], m[8]);
		G(2, 6, 10, 14, m[9], m[15]);
		G(3, 7, 11, 15, m[13], m[6]);
		G(0, 5, 10, 15, m[1], m[12]);
		G(1, 6, 11, 12, m[0], m[2]);
		G(2, 7, 8, 13, m[11], m[7]);
		G(3, 4, 9, 14, m[5], m[3]);
	}
	return v[4];
}

int main(int argc, char** argv) {
	return !mix(argc);
}
