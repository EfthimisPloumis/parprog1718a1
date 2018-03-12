#include <stdio.h> 
#include <stdlib.h> 
#include <sys/time.h>

// compile like: gcc -Wall -O2 -DNROWS=10000 matrix2.c -o matrix2

#define NCOLS 100

void get_walltime(double *wct) {
	struct timeval tp; 
	gettimeofday(&tp,NULL);
	*wct = (double)(tp.tv_sec+tp.tv_usec/1000000.0);
}


int main() { 
	unsigned int i,j; 
	double sum; 
	double *table; 
	double ts,te,aps;


	table = (double *)malloc(NROWS*NCOLS*sizeof(double)); 
	if (table==NULL) {
		printf("alloc error!\n"); 
		exit(1);
	}

	// warmup
	for (i=0;i<NROWS*NCOLS;i++) {
		table[i] = 1.0;
	}

	// get starting time (double, seconds) 
	get_walltime(&ts);

	// workload 
	sum = 0.0;
	for (j=0;j<NCOLS;j++) { 
		for (i=0;i<NROWS;i++) {
			sum += table[i*NCOLS+j];
		}
	}
 
	// get ending time 
	get_walltime(&te);
	printf("sum = %f\n",sum);

    // print time elapsed and/or Maccesses/sec
	aps = ((double)NROWS*NCOLS)/((te-ts)*1e6);

	printf("avg array element Maccesses/sec = %f\n",aps); 
	free(table);
	return 0;
}
