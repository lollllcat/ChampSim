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

#define X_OFFSET 0
#define B_OFFSET N
#define L_OFFSET N + N

void trisolv_trace(double* x, double* b, double* L) {

	int i, j;

	for (i = 0; i < N; i++) {
		x[i] = b[i];
		for (j = 0; j <i; j++) {
			x[i] -= L[i * N + j] * x[j];
		}
		x[i] = x[i] / L[i * N + i];
	}

}

int main() {

	double* x = (double *)malloc(N * sizeof(double));
	double* b = (double *)malloc(N * sizeof(double));
	double* L = (double *)malloc(N * N * sizeof(double));

#ifdef RD
    InitRD();
#endif
    
	trisolv_trace(x, b, L);

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


