#include <iostream>
#ifndef DS
	#define DS 8
#endif

#ifndef CLS
	#define CLS	64
#endif

using namespace std;
vector<uint64_t> stack;
map<uint64_t, uint64_t> rdHist;

void rtTmpAccess(uint64_t addr) {
	addr = addr * DS / CLS;
	printf("%lld\n", addr);
	return
}

void rtTmpAccess(uint64_t addr, uint64_t ref_id, uint64_t array_id) {
	printf("%lld %lld %lld\n", ref_id, array_id, addr);
}

void dumpRtTmp() {

}

void RTtoMR_AET() {
}

void dumpMR() {
	
}