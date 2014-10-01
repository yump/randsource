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

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>


#define BUFSIZE 32768

/*
 * Linear congurential PRNG, constants specified by Donald Knuth
 */
void mmix(uint64_t *buf, size_t len) {
	static const uint64_t mult = 6364136223846793005U;
	static const uint64_t inc  = 1442695040888963407U;
	buf[0] = buf[len-1]; //reuse state
	for (size_t i=1; i<len; ++i) {
		buf[i] = buf[i-1] * mult + inc;
	}
}

/*
 * High-res time as floating point number
 */
double hrtime() {
	struct timespec time_obj;
	clock_gettime(CLOCK_MONOTONIC, &time_obj);
	return (double)time_obj.tv_sec + 1e-9 * (double)time_obj.tv_nsec;
}

/*
 * SI prefix formatter for integers
 */
void si_format(char *str, size_t len, long val) {
	const char * const prefixes[] = {"","k","M","G","T","P","E","Z","Y"};
	int prefix_idx = 0;
	double d_val = (double) val;
	while (fabs(d_val) > 1000 && prefix_idx < 9) {
		d_val /= 1000.0;
		prefix_idx++;
	}
	snprintf(str, len, "%.2f %s", d_val, prefixes[prefix_idx]);
}

/*
 * Updating progress information
 * 
 * bytes is the number of bytes written since the last call to progress()
 */
void progress(size_t bytes) {
	static size_t tot_bytes = 0, period_bytes = 0;
	static double period_start = 0;
	static long speed_bs = 0;
	const double period = 0.2;
	double now;
	char s_speed[32], s_tot_bytes[32]; //for SI formatted numbers
	//Elapsed calc
	//state update
	tot_bytes += bytes;
	period_bytes += bytes;
	//rate limit
	now = hrtime();
	if ( now > (period_start + period) ) {
		speed_bs = (int)(period_bytes / period);
		period_bytes = 0;
		period_start = now;
		//format
		si_format(s_speed, 32, speed_bs);
		si_format(s_tot_bytes, 32, tot_bytes);
		//clear
		fprintf(stderr, "\33[2K\r");
		//print
		fprintf(stderr, "Total: %sB\tSpeed: %sB/s",
		        s_tot_bytes, s_speed);
	}
}

int main(int argc, char *argv[]) {	
	uint64_t randbuf[BUFSIZE];
	size_t written;
	randbuf[BUFSIZE-1] = time(NULL); //seed
	while(true) {
		written = 0;
		//call progress() less often
		for (int i=0; i<100; ++i) {
			mmix(randbuf, BUFSIZE);
			written += fwrite(randbuf, sizeof (randbuf[0]),
			                 BUFSIZE, stdout);
		}
		progress(written * sizeof (randbuf[0]));
	}
	return 0;
}

