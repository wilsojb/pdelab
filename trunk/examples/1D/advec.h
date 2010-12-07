#ifndef ADVEC_H
#define ADVEC_H

#include "example.h"
#include <string>

class advec : public Example {
public:
	advec();
	virtual ~advec();
	
	// simulating
	void deleteDynamicVars();
	void createDynamicVars();
	void createStaticVars();
	void createDerivedVars();
	void createInitialData(bool store);
	void run(int t);
	void record(int t);
	
	// plotting
	void genGnuplotScript();
	void definePlotVars(int start,int stop,int skip,int save);
	
	
protected:
	vector<double> *_U,*_U1;
};

#endif
