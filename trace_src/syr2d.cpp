#include <cstdlib>
#ifdef PROFILE_RT
	#include "trace_log.h"
#endif

#ifdef RD
	#include "rd_simple.h"
#endif

#ifdef ORG
	#define N 1024
	#define M 1024
#elif defined(TX)
#elif defined(FX)
#elif defined(EX)
#endif

#define A_OFFSET 0
#define B_OFFSET M * M
#define C_OFFSET M * M + N * M

void syr2k_trace(double* A, double* B, double* C, double alpha, double beta) {

	int i, j, k;

	for (i = 0; i < N; i++) {
		for (j = 0; j <= i; j++) {
			C[i * N + j] *= beta;
		}
		for (k = 0; k < M; k++) {
			for (j = 0; j <= i; j++) {
				C[i * N + j] += A[j * M + k]*alpha*B[i * M + k] + B[j * M + k]*alpha*A[i * N + k];
			}
		}
	}
}

int main() {

	double* A = (double *)malloc(M * M * sizeof(double));
	double* B = (double *)malloc(N * M * sizeof(double));
	double* C = (double *)malloc(N * N * sizeof(double));
	double alpha = 0.2;
	double beta = 0.8;

#ifdef RD
    InitRD();
#endif
    
	syr2k_trace(A, B, C, alpha, beta);

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

