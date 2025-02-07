// #include <cstdlib>
#ifdef PROFILE_RT
	#include "trace_log.h"
#endif

#ifdef RD
	#include "rd_simple.h"
#endif

#include<math.h>

#ifdef ORG
	#define W 1024
	#define H 1024
#elif defined(TX)
#elif defined(FX)
#elif defined(EX)
#endif

#define EXP_FUN(x) exp(x)
#define POW_FUN(x,y) pow(x,y)

#define Y1_OFFSET 0
#define IMGIN_OFFSET W * H
#define Y2_OFFSET W * H + W * H
#define IMGOUT_OFFSET W * H + W * H + W * H

void deriche_trace(double* y1, double* imgIn, double* y2, double* imgOut, double alpha) {

	double k, a1, a2, a3, a4, b1, b2, c1, c2;

	double a5, a6, a7, a8;

	double ym1, ym2, xm1, yp1, yp2, xp1, xp2;

	double tm1;

	double tp1, tp2;

	int i, j;

	k = (1.0 - EXP_FUN(-alpha))*(1.0-EXP_FUN(-alpha))/(1.0+2.0*alpha*EXP_FUN(-alpha)-EXP_FUN(2.0*alpha));
	a1 = a5 = k;
	a2 = a6 = k*EXP_FUN(-alpha)*(alpha-1.0);
	a3 = a7 = k*EXP_FUN(-alpha)*(alpha+1.0);
	a4 = a8 = -k*EXP_FUN(-2.0*alpha);
	b1 =  POW_FUN(2.0,-alpha);
	b2 = -EXP_FUN(-2.0*alpha);
	c1 = c2 = 1;

	for (i=0; i < W; i++) {
		ym1 = 0.0;
		ym2 = 0.0;
		xm1 = 0.0;
		for (j=0; j < H; j++) {
			y1[i * H + j] = a1*imgIn[i * H + j] + a2*xm1 + b1*ym1 + b2*ym2;
			xm1 = imgIn[i * H + j];
			ym2 = ym1;
			ym1 = y1[i * H + j];
		}
	}

	for (i=0; i < W; i++) {
		yp1 = 0.0;
		yp2 = 0.0;
		xp1 = 0.0;
		xp2 = 0.0;
		for (j = H-1; j >= 0; j--) {
			y2[i * H + j] = a3*xp1 + a4*xp2 + b1*yp1 + b2*yp2;
			xp2 = xp1;
			xp1 = imgIn[i * H + j];
			yp2 = yp1;
			yp1 = y2[i * H + j];
		}
	}

	for (i=0; i < W; i++)
		for (j=0; j < H; j++) {
			imgOut[i * H + j] = c1 * (y1[i * H + j] + y2[i * H + j]);
		}

	for (j=0; j < H; j++) {
		tm1 = 0.0;
		ym1 = 0.0;
		ym2 = 0.0;
		for (i=0; i < W; i++) {
			y1[i * H + j] = a5*imgOut[i * H + j] + a6*tm1 + b1*ym1 + b2*ym2;
			tm1 = imgOut[i * H + j];
			ym2 = ym1;
			ym1 = y1 [i * H + j];
		}
	}

	for (j=0; j < H; j++) {
		tp1 = 0.0;
		tp2 = 0.0;
		yp1 = 0.0;
		yp2 = 0.0;
		for (i = W-1; i>=0; i--) {
			y2[i * H + j] = a7*tp1 + a8*tp2 + b1*yp1 + b2*yp2;
			tp2 = tp1;
			tp1 = imgOut[i * H + j];
			yp2 = yp1;
			yp1 = y2[i * H + j];
		}
	}

	for (i=0; i < W; i++)
		for (j=0; j < H; j++) {
			imgOut[i * H + j] = c2*(y1[i * H + j] + y2[i * H + j]);
		}
}

int main() {

	double* y1 = (double *)malloc(W * H * sizeof(double));
	double* imgIn = (double *)malloc(W * H * sizeof(double));
	double* y2 = (double *)malloc(W * H * sizeof(double));
	double* imgOut = (double *)malloc(W * H * sizeof(double));
	double alpha = 0.5;

#ifdef RD
    InitRD();
#endif
    
	deriche_trace(y1, imgIn, y2, imgOut, alpha);

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
