#include "example.h"
#include <string>
#include <sstream>
#include <iostream>
using std::endl;
using std::stringstream;
using std::cout;

Example::Example() {
	
	VAR1_UINT = NULL;
	VAR2_UINT = NULL;
	VAR3_UINT = NULL;
	
	VAR1_D = NULL;
	VAR2_D = NULL;
	VAR3_D = NULL;
	
	VAR1_B = NULL;
	VAR2_B = NULL;
	VAR3_B = NULL;
	
	VAR1_STR = NULL;
	VAR2_STR = NULL;
	VAR3_STR = NULL;
	
	VAR1_VECT = NULL;
	VAR2_VECT = NULL;
	VAR3_VECT = NULL;
	
	LENGTH = 0;
	NX = 1;
	MAX_TIME = 1;
	HEIGHT = 0;
	DX = 0;
	DT = 0;
	AMP = 0;
	START_X = 0;
	CFL = 0;
	GRAVITY_CONSTANT = 10;
	MU = 0;
	EPSILON = 0;
	LAMBDA = 0;
	K = 0;
	SIGMA = 0;
	
	SCRIPT_START = 0;
	SCRIPT_STOP = 0;
	SCRIPT_SKIP = 1;
	SCRIPT_SAVE = false;
	
	EQUATION = "";
	PATH = "";
	FILENAME = "";
	TITLE = "";
	
	WIDTH = 0;
	NY = 1;
	DY = 0;
	START_Y = 0;
}

Example::~Example() {}

void Example::createInitialData(bool store) {
	store = false;
	
	cout<< ALIGN <<"createInitialData() subroutine has not been written."<<endl;
}

void Example::createStaticVars() {
	cout<< ALIGN << "createStaticVars() subroutine has not been written."<<endl;
}

void Example::createDerivedVars() {
	cout << ALIGN << "createDerivedVars() subroutine has not been written." << endl;
}

void Example::createDynamicVars() {
	cout<< ALIGN << "createDynamicVars() subroutine has not been written."<<endl;
}

void Example::deleteDynamicVars() {
	cout<< ALIGN << "deleteDynamicVars() subroutine has not been written."<<endl;
}

void Example::run(int t) {
	t = 0;
	cout<< ALIGN << "run() subroutine has not been written."<<endl;
}

void Example::record(int t) {
	t = 0;
	cout<< ALIGN << "record() subroutine has not been written."<<endl;
}

void Example::genGnuplotScript() {
	cout<< ALIGN << "genGnuplotScript() subroutine has not been written."<<endl;
}

void Example::genGnuplotScript_2VARS() {
	cout<< ALIGN << "genGnuplotScript_2VARS() subroutine has not been written."<<endl;
}

void Example::definePlotVars(int start,int stop,int skip,int save) {

	start = stop = skip = save = 0;
	cout<< ALIGN << "definePlotVars() subroutine has not been written."<<endl;
}



