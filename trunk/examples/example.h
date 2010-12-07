#ifndef EXAMPLE_H
#define EXAMPLE_H

/***************************************************************
 * File:   example.h
 * Author: Joshua Wilson
 * Date:   3/15/2010
 * MAIL:	pdelab-discuss@googlegroups.com
 *
 * This file is protected by the
 * GNU General License
 *
 *
 * Description: Class used by Solver.h and Instruction.h.  All examples
 * are expected to extend this class and override its virtual methods
 *
 **************************************************************/

#define ALIGN "         "

// STD LIBRARY
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <vector>
using std::endl;
using std::string;
using std::ofstream;
using std::cout;
using std::vector;

class Example {
	public:
	// Constructors / destructor
	Example();
	~Example();
	
	// Methods used to build Solver::invoke()
	// In order for a example to be useful, it will need to override
	// several of the following methods.
	//
	// In order to make an example valid, it will need to override
	// all of the protected methods (see below).
	
	virtual void createStaticVars();
	virtual void createDerivedVars();
	virtual void createDynamicVars();
	virtual void createInitialData(bool store);
	virtual void deleteDynamicVars();

	virtual void run(int t);
	virtual void record(int t);
	virtual void genGnuplotScript();
	virtual void genGnuplotScript_2VARS();
	virtual void definePlotVars(int start,int stop,int skip,int save);
	
	
	// Accessors
	// One per global variable
	double getLength() {return LENGTH;}
	double getWidth() {return WIDTH;}
	unsigned getNX() {return NX;}
	unsigned getNY() {return NY;}
	unsigned getMaxTime() {return MAX_TIME;}
	double getHeight() {return HEIGHT;}
	double getDX() {return DX;}
	double getDY() {return DY;}
	double getDT() {return DT;}
	double getAmp() {return AMP;}
	double getStartX() {return START_X;}
	double getStartY() {return START_Y;}
	string getType() {return EQUATION;}
	string getPath() {return PATH;}
	string getFileName() {return FILENAME;}
	string getTitle() {return TITLE;}
	
	// Setters
	// One per global variable
	void setLength(unsigned int l) {LENGTH = l;}
	void setWidth(unsigned int w) {WIDTH = w;}
	void setNX(unsigned int nx) {NX = nx;}
	void setNY(unsigned int ny) {NY = ny;}
	void setMaxTime(unsigned int t) {MAX_TIME = t;}
	void setHeight(double h) {HEIGHT = h;}
	void setDX(double h) {DX = h;}
	void setDY(double h) {DY = h;}
	void setDT(double h) {DT = h;}
	void setAmp(double amp) {AMP = amp;}
	void setStartX(double x) {START_X = x;}
	void setStartY(double y) {START_Y = y;}
	void setType(string t) {EQUATION = t;}
	void setPath(string t) {PATH = t;}
	void setFileName(string t) {FILENAME = t;}
	void setTitle(string t) {TITLE = t;}
	
	
	
	// PUBLIC ACCESS:  Pointers used by observer.cpp
	unsigned *VAR1_UINT, *VAR2_UINT, *VAR3_UINT;
	double *VAR1_D, *VAR2_D, *VAR3_D;
	bool *VAR1_B, *VAR2_B, *VAR3_B;
	string *VAR1_STR, *VAR2_STR, *VAR3_STR;
	const vector<double> * VAR1_VECT, *VAR2_VECT, *VAR3_VECT;
	
	
	protected:
	
	// 1D Global Variables
	unsigned NX;
	unsigned MAX_TIME;
	
	double LENGTH;
	double HEIGHT;
	double DX;
	double DT;
	double AMP;
	double START_X;
	double CFL;
	double GRAVITY_CONSTANT;
	double MU;					
	double EPSILON;
	double LAMBDA;
	double K;
	double SIGMA;
	
	unsigned SCRIPT_START;
	unsigned SCRIPT_STOP;
	unsigned SCRIPT_SKIP;
	bool	 SCRIPT_SAVE;
	
	string EQUATION;
	string PATH;
	string FILENAME;
	string TITLE;
	
	
	// Extra 2D Global Variables
	unsigned NY;
	
	double WIDTH;
	double DY;
	double START_Y;
	
	// Exporting results
	ofstream OUTFILE;
};



#endif	// EXAMPLE_H
