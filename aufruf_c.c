#include <stdio.h>
#include <stdlib.h>

struct timeval t1;
int main(int argc, char** argv)
{
	gettimeofday(&t1,NULL);
	unsigned long time_in_micros = 1000000 * t1.tv_sec+ t1.tv_usec;
	printf("%lu\n", time_in_micros);
}