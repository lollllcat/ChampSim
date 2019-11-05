#include <cstdlib>
#ifdef PROFILE_RT
	#include "trace_log.h"
#endif

#ifdef RD
	#include "rd_simple.h"
#endif

#ifdef ORG
	#define NR 256
	#define NQ 256
	#define NP 256
#elif defined(TX)
#elif defined(FX)
#elif defined(EX)
#endif

#define SUM_OFFSET 0
#define A_OFFSET NP
#define C4_OFFSET NP + NR * NQ * NP

void doitgen_trace(double* sum, double* A, double* C4) {

	int r, q, p, s;

	for (r = 0; r < NR; r++) {
		for (q = 0; q < NQ; q++)  {
			for (p = 0; p < NP; p++)  {
				sum[p] = 0.0;
				for (s = 0; s < NP; s++) {
					sum[p] += A[r * NQ * NP + q * NP + s] * C4[s * NP + p];
				}
			}
			for (p = 0; p < NP; p++) {
				A[r * NQ * NP + q * NP + p] = sum[p];
			}
    	}
	}

}

int main() {
	
	double * sum = (double *) malloc(NP * sizeof(double));
	double * A = (double *) malloc(NR * NQ * NP * sizeof(double));
	double * C4 = (double *) malloc(NP * NP);
	
#ifdef RD
    InitRD();
#endif
    
	doitgen_trace(sum, A, C4);

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



