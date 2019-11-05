#include <cstdlib>
#ifdef PROFILE_RT
    #include "trace_log.h"
#endif

#ifdef RD
    #include "rd_simple.h"
#endif

#ifdef ORG
	#define NX 1024
	#define NY 1024
#elif defined(TX)
	#define NX 1024
	#define NY 2048
#elif defined(FX)
	#define NX 1024
	#define NY 4096
#elif defined(EX)
	#define NX 1024
	#define NY 8192
#endif

#define A_OFFSET 0
#define X_OFFSET NX * NY
#define Y_OFFSET NX * NY + NY
#define TMP_OFFSET NX * NY + NY + NY


void atax_cpu_trace(double* A, double* x, double* y, double* tmp, unsigned int dim_size_x, unsigned int dim_size_y) {
    
	int i,j;

    for (i= 0; i < NY; i++)
    {
        y[i] = 0;
	}

    for (i = 0; i < NX; i++)
    {
            tmp[i] = 0;

            for (j = 0; j < NY; j++)
            {
                tmp[i] = tmp[i] + A[i * NY + j] * x[j];
			}

            for (j = 0; j < NY; j++)
            {
                y[j] = y[j] + A[i * NY + j] * tmp[i];
			}
    }


	return;
}



int main() {

    double* A = (double*)malloc( (NX * NY) * sizeof(double) );
    double* x = (double*)malloc( NX * sizeof(double) );
    double* y = (double*)malloc( NY * sizeof(double) );
    double* tmp = (double*)malloc( NX * sizeof(double) );

    for (int i = 0; i < (NX * NY); i++) {
        A[i] = i % 256;
    }

    for (int i = 0; i < NX; i++) {
        x[i] = i % 256;
    }

#ifdef RD
    InitRD();
#endif
    
    atax_cpu_trace(A, x, y, tmp, NX, NY);
    
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

