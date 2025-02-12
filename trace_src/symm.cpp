#include <cstdlib>
#ifdef PROFILE_RT
	#include "trace_log.h"
#endif

#ifdef RD
	#include "rd_simple.h"
#endif

#ifdef ORG
	#define M 1024
	#define N 1024
#elif defined(TX)
#elif defined(FX)
#elif defined(EX)
#endif

#define A_OFFSET 0
#define B_OFFSET M * M
#define C_OFFSET M * M + M * N

void symm_trace(double* A, double* B, double* C, double alpha, double beta) {
	
	int i, j, k;	
	double temp2;

	for (i = 0; i < M; i++) {
		for (j = 0; j < N; j++ ) {
			temp2 = 0;
			for (k = 0; k < i; k++) {
				C[k * N + j] += alpha*B[i * N + j] * A[i * M + k];
				temp2 += B[k * N + j] * A[i * M + k];
			}
			C[i * N + j] = beta * C[i * N + j] + alpha*B[i * N + j] * A[i * M + i] + alpha * temp2;
		}
	}
	return;
}

int main() {

	double* A = (double *)malloc(M * M * sizeof(double));
	double* B = (double *)malloc(M * N * sizeof(double));
	double* C = (double *)malloc(M * N * sizeof(double));
	double alpha = 0.2;
	double beta = 0.8;

#ifdef RD
    InitRD();
#endif
    
	symm_trace(A, B, C, alpha, beta);

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

