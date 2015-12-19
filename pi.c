#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include <stdlib.h>

int pi( int n, char *buff);
int writeData(char *buff);
int MAX_BUF = 20000;
int DIGITS = 20000;
int RUNS = 10;
int IO = 0;


int main(int argc, char** argv)
{
	if (argc < 3 || argc > 4){
		printf("Usage: pi Digits Runs [IO burst if given]\n");
		return 1;
	}
	else{
		sscanf(argv[1], "%i", &DIGITS);
		MAX_BUF = DIGITS;
		sscanf(argv[2], "%i", &RUNS);
		if (argc == 4){
			IO = 1;
		}
	}
	int deltasum=0;
	int deltasumIO=0;
	//Charbuffer for storing the pi
	int i;
	for (i=0; i < RUNS; i++){
		char* buff = malloc(MAX_BUF);
		struct timeval t1, t2;
		long deltausec, deltasec;
		//Take System time
		gettimeofday(&t1, NULL);
		//calculate pi
		pi(DIGITS / 4 * 14, buff);
		//Take System time and calc delta
		gettimeofday(&t2, NULL);
		deltausec = t2.tv_usec - t1.tv_usec;
		deltasec = t2.tv_sec - t1.tv_sec;
		if (deltausec < 0) {
			deltausec += 1000000;
			deltasec--;
		}
		deltasum += deltausec + deltasec * 1000000;
		printf("\nLaufzeit für %d Stellen: %ld s %ld µs", DIGITS, deltasec, deltausec);
		if (IO){
			deltasumIO += writeData(buff);
		}
		free(buff);
		
	}
	printf("\nDurchschnittliche Laufzeit (%d Durchläufe): %d s %d µs\n", RUNS, deltasum / RUNS / 1000000,deltasum/RUNS%1000000);
	if (IO){
		printf("Durchschnittliche Schreibzeit (%d Durchläufe): %d s %d µs\n", RUNS, deltasumIO / RUNS / 1000000, deltasumIO / RUNS % 1000000);
	}
    return 0;
}

int writeData(char *buff){
	FILE *f;
	struct timeval t1, t2;
	long deltausec, deltasec;
	//Start measuring here---------------
	gettimeofday(&t1, NULL);
	f = fopen("pi.txt", "w");
	int i;
	for (i=0; i < 10000; i++){
		fprintf(f, "%s\n", buff);
	}
	fclose(f);
	gettimeofday(&t2, NULL);
	//Stop measuring here----------------
	deltausec = t2.tv_usec - t1.tv_usec;
	deltasec = t2.tv_sec - t1.tv_sec;
	if (deltausec < 0) {
		deltausec += 1000000;
		deltasec--;
	}
	printf("\nSchreibzeit für 10000*%d Stellen: %ld s %ld µs", DIGITS, deltasec, deltausec);
	remove("pi.txt"); //delete file to recreate start conditions
	return deltausec + deltasec * 1000000;
}

int pi(int n, char *buff)
{
    //das ist alles nur geklaut eeeooeeeo
    //berechnet die stellen von pi einzeln
    int length =0;
    int r[n + 1];
    int i, k;
    int b, d;
    int c = 0;
    
    for (i = 0; i < n; i++) {
        r[i] = 2000;
    }
    
    for (k = n; k > 0; k -= 14) {
        d = 0;
        
        i = k;
        for (;;) {
            d += r[i] * 10000;
            b = 2 * i - 1;
            
            r[i] = d % b;
            d /= b;
            i--;
            if (i == 0) break;
            d *= i;
        }
        length += snprintf(buff+length, MAX_BUF-length, "%.4d",c+d/10000);
        c = d % 10000;
    }
    
    return 0;
}
