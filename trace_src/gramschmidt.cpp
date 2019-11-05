#include <cstdlib>
#ifdef PROFILE_RT
	#include "trace_log.h"
#endif

#ifdef RD
	#include "rd_simple.h"
#endif

#include <math.h>

#ifdef ORG
	#define N 1024
	#define M 1024
#elif defined(TX)
#elif defined(FX)
#elif defined(EX)
#endif

#define A_OFFSET 0
#define R_OFFSET N * M
#define Q_OFFSET N * M + N * N

void gramschmidt_trace(double* A, double* R, double* Q) {

	int k, i, j;
	double nrm;

	for (k = 0; k < N; k++) {
		nrm = 0.0;
		for (i = 0; i < M; i++) {
			nrm += A[i * N + k] * A[i * N + k];
		}
		R[k * N + k] = sqrt(nrm);
		for (i = 0; i < M; i++) {
			Q[i * N + k] = A[i * N + k] / R[k * N + k];
		}
		for (j = k + 1; j < N; j++) {
			R[k * N + j] = 0.0;
			for (i = 0; i < M; i++) {
				R[k * N + j] += Q[i * N + k] * A[i * N + j];
			}
			for (i = 0; i < M; i++) {
        		A[i * N + j] = A[i * N + j] - Q[i * N + k] * R[k * N + j];
			}
		}
    }
}

int main() {

	double * A = (double *)malloc(N * M * sizeof(double));
	double * R = (double *)malloc(N * N * sizeof(double));
	double * Q = (double *)malloc(M * N * sizeof(double));

#ifdef RD
    InitRD();
#endif
    
	gramschmidt_trace(A, R, Q);
	
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

