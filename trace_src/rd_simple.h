#include<vector>
#include<map>
#include <algorithm>
#include<iostream>

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

	if (find(stack.begin(), stack.end(), addr) != stack.end()) {
		vector<uint64_t>::iterator it = std::find(stack.begin(), stack.end(), addr);
		uint64_t rd = std::distance(it, stack.end());
		if (rdHist.find(rd) != rdHist.end()) {
			rdHist[rd] += 1;
		} else {
			rdHist[rd] = 1;
		}
		stack.erase(find(stack.begin(), stack.end(), addr));
		stack.push_back(addr);
	} else {
		stack.push_back(addr);
	}
	return;
}

void InitRD() {
	return;
}

void FiniRD() {
	uint64_t total_cnt = 0;
	for (map<uint64_t, uint64_t>::iterator it = rdHist.begin(), eit = rdHist.end(); it != eit; ++it) {
		cout << "RD " << it->first << " " << it->second << endl;
		total_cnt += it->second;
	}
	uint64_t acc_cnt = 0;
	cout << "CLS " << 0 << " " << 1 << endl;
	for (map<uint64_t, uint64_t>::iterator it = rdHist.begin(), eit = rdHist.end(); it != eit; ++it) {
		acc_cnt += it->second;
		cout << "CLS " << it->first << " " << 1 - (double (acc_cnt) / total_cnt) << endl;
	}
	return;
}

