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
#elif defined(TX)
#elif defined(FX)
#elif defined(EX)
#endif

#define match(b1, b2) (((b1)+(b2)) == 3 ? 1 : 0)
#define max_score(s1, s2) ((s1 >= s2) ? s1 : s2)


#define TABLE_OFFSET 0
#define SEQ_OFFSET N * N

void nussinov_trace(double* table, double* seq) {

	int i, j, k;

	for (i = N - 1; i >= 0; i--) {
		for (j=i+1; j < N; j++) {
			if (j-1>=0) {
				table[i * N + j] = max_score(table[i * N + j], table[i * N + j-1]);
				if (table[i * N + j] > table[i * N + j-1]) {

				}
				else {

				}
			}
			if (i+1 < N) {
				table[i * N +j] = max_score(table[i * N + j], table[(i+1) * N + j]);
				if (table[i * N + j] >= table[(i+1) * N + j]) {

				} else {

				}
			}
			if (j-1>=0 && i+1 < N) {
				/* don't allow adjacent elements to bond */
				if (i<j-1) {
					table[i * N + j] = max_score(table[i * N + j], table[(i+1) * N + j-1]+match(seq[i], seq[j]));
					if (table[i * N + j] >= table[(i+1) * N + j-1]+match(seq[i], seq[j])) {
					} else {
					}
				} else {
					table[i * N + j] = max_score(table[i * N + j], table[(i+1) * N + j-1]);
					if (table[i * N + j] >= table[(i+1) * N + j-1]) {
					} else {
					}
				}
			}
			for (k=i+1; k<j; k++) {
				table[i * N + j] = max_score(table[i * N + j], table[i * N + k] + table[(k+1) * N + j]);
				if (table[i * N + j] >= table[i * N + k] + table[(k+1) * N + j]) {
				} else {
				}
			}
		}
	}
}

int main() {

	double* table = (double *)malloc(N * N * sizeof(double));
	double* seq = (double *)malloc(N * sizeof(double));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			table[i * N + j] = (i * N + j) % 128;
		}
		seq[i] = i % 64;
	}

#ifdef RD
    InitRD();
#endif
    
	nussinov_trace(table, seq);

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

