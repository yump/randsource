/*
 *  Randsource: Weak pseudorandom data source
 *  
 *  Copyright 2014 Russell Haley
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>


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

