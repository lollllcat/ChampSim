#include <cstdlib>
#ifdef PROFILE_RT
	#include "trace_log.h"
#endif

#ifdef RD
	#include "rd_simple.h"
#endif

#ifdef ORG
	#define N 1024
#elif defined(TX)
#elif defined(FX)
#elif defined(EX)
#endif

#define Y_OFFSET 0
#define R_OFFSET N
#define Z_OFFSET N + N

void durbin_trace(double *y, double* r, double* z) {

	int k, i;
	double alpha, beta, sum;

/*
	y[0] = -r[0];
	beta = 1.0;
	alpha = -r[0];
*/	
	for (k = 1; k < N; k++) {
		beta = (1-alpha*alpha)*beta;
		sum = 0.0;
		for (i=0; i<k; i++) {
			sum += r[k-i-1]*y[i];
		}
		alpha = - (r[k] + sum)/beta;

		for (i=0; i<k; i++) {
			z[i] = y[i] + alpha*y[k-i-1];
		}
		for (i=0; i<k; i++) {
			y[i] = z[i];
		}
		y[k] = alpha;
	}	

}

int main() {

	double * y = (double *) malloc(N * sizeof(double));
	double * r = (double *) malloc(N * sizeof(double));
	double * z = (double *) malloc(N * sizeof(double));

#ifdef RD
    InitRD();
#endif
    
	durbin_trace(y, r, z);

#ifdef PROFILE_RT
    dumpRtTmp();
    RTtoMR_AET();
    dumpMR();
#endif
    
#ifdef RD
    FiniRD();
#endif

	return 0;
}


