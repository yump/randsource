#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include <openssl/rand.h>
#include <time.h>

/*
 * Weak pseudorandom data source
 */

#define BUFSIZE 1024

/*
 * Linear congurential PRNG, constants specified by Donald Knuth
 */
void mmix(uint64_t *buf, size_t len) {
	static const uint64_t mult = 6364136223846793005U;
	static const uint64_t inc  = 1442695040888963407U;
	buf[0] = buf[len-1];
	for (size_t i=1; i<len; ++i) {
		buf[i] = buf[i-1] * mult + inc;
	}
}


int main(int argc, char *argv[]) {	
	uint64_t randbuf[BUFSIZE];
	randbuf[BUFSIZE-1] = time(NULL); //seed
	while(true) {
		mmix(randbuf, BUFSIZE);
		fwrite(randbuf, sizeof(uint64_t), BUFSIZE, stdout);
	}
	return 0;
}

