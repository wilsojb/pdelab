
// SRC INCLUDES
#include "instruction.h"
#include "example.h"

// STD LIBRARY
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <sstream>
#include <iomanip>
using std::cout;
using std::endl;
using std::ofstream;
using std::string;
using std::pow;
using std::string;
using std::log;

// Instruction ----------------------------------------------------------
Instruction::Instruction(string sim_name,StringQueue vars) {
	this->sim_name = sim_name;
	this->vars = vars;
	position = new bool[4];
	position[0] = 0;
	position[1] = 0;
	position[2] = 0;
	position[3] = 0;
}

Instruction::~Instruction() {
	delete position;
}

void Instruction::run(int timestamp, Example* e) {
	e = NULL; timestamp = 0;
	sm.message("Instruction::run() called");
}

bool * Instruction::getType() const {
	return (bool *)position;
}

string Instruction::getSim() const {
	return sim_name;
}


// Test --------------------------------------------------
Test::Test(string sim_name,StringQueue vars) : Instruction(sim_name,vars) {
	position[0] = 1;
	// initialize the position and any other
	// local variables
	
	path = sm.dat_path + "Test.run/";
	filename = path + getSim() + sm.dat_suffix;
}

Test::~Test() {}

void Test::run(int timestamp, Example * e) {
	timestamp = 0;
	if (e->getType() == getSim()) {
		
		// write the instructions that will perform 
		// the observation.  make sure to include
		// the e->getType == getSim() if statement
		sm.message("Test::run() called.");
	}
}

// Diffnorm ----------------------------------------------
Diffnorm::Diffnorm(string sim_name,StringQueue vars) : Instruction(sim_name,vars) {
	pnorm = 2;
	position[3] = 1;
	norm = 0;
	dx = 0;
	dt = 0;
	nx = 0;
	
	string newpath = (vars.isEmpty()) ? "" : vars.pop();
	path = sm.dat_path + newpath + "/";
	filename = path + getSim() + sm.dat_suffix;
}

Diffnorm::~Diffnorm() {}

void Diffnorm::run(int timestamp, Example* e) {
	if (e->getType() == getSim()) {
		nx = e->getNX();
		v1 = *(e->VAR1_VECT);
		v2 = *(e->VAR2_VECT);
		dx = e->getDX();
		dt = e->getDT();
		
		// Calculating norm
		for (unsigned i=0; i<nx; ++i) {
			v1[i] = v2[i] - v1[i];
			if (v1[i] < 0) v1[i] = -v1[i];
		}
		
		for (unsigned i=0; i<nx; ++i) {
			norm += pow(v1[i],pnorm);
		}
		norm = pow(norm*dx,(1/pnorm));
		
		// Building directory
		if (!sm.createDirectory(path)) {
			//string tmp = "rm -rf " + filename;
			//bool sysr = system(&tmp[0]); sysr = 0; // prevent warnings
		}
		
		// Storing data
		ofstream o(filename.c_str(),std::fstream::app);
		o << dx << "\t" << norm << endl;
		o.close();
			
	}
}


// Norm --------------------------------------------------
Norm::Norm(string sim_name,StringQueue vars) : Instruction(sim_name,vars) {
	pnorm = 2;
	position[2] = 1;
	norm = 0;
	dx = 0;
	nx = 0;
	
	string newpath = (vars.isEmpty()) ? "" : vars.pop();
	path = sm.dat_path + newpath + "/";
	filename = path + getSim() + sm.dat_suffix;
}

Norm::~Norm()  {}

void Norm::run(int timestamp, Example* e) {
	if (e->getType() == getSim()) {
		nx = e->getNX();
		v = *(e->VAR1_VECT);
		dx = e->getDX();
		
		// Calculating norm
		for (unsigned i=0; i<nx; ++i) {
			if (v[i] < 0) v[i] = -v[i];
		}
		
		for (unsigned i=0; i<nx; ++i) {
			norm += pow(v[i],pnorm);
		}
		norm = pow(norm*dx,(1/pnorm));
	 
		//norm = v[int(nx/2)];
		
		// Building directory
		if (timestamp==0) {
			if (!sm.createDirectory(path)) {
				string tmp = "rm -rf " + filename;
			 	bool sysr = system(&tmp[0]); sysr = 0; // prevent warnings
			}
		}
		
		// Storing data
		ofstream o(filename.c_str(),std::fstream::app);
		o << timestamp << "\t" << norm << endl;
		o.close();
	}
}

// Filename -------------------------------------------------
Filename::Filename(string sim_name,StringQueue vars) : Instruction(sim_name,vars) {
	position[0] = 1;
}

Filename::~Filename() {}

void Filename::run(int timestamp,Example* e) {
	timestamp = 0;	// prevent warnings
	if (e->getType() == getSim()) {
		string filename = !vars.isEmpty() ? vars.peek() : e->getFileName();
		e->setFileName(filename);
	}
}


// Output -------------------------------------------------
Output::Output(string sim_name,StringQueue vars) : Instruction(sim_name,vars) {
	position[0] = 1;
}

Output::~Output() {}

void Output::run(int timestamp,Example* e) {
	timestamp = 0;	// prevent warnings
	if (e->getType() == getSim()) {
		string dir = sm.dat_path;
		dir = !vars.isEmpty() ? dir+ vars.peek() + "/" : dir;
		sm.createDirectory(dir);
		e->setPath(dir);
	}
}
