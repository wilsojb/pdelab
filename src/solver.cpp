
// SRC INCLUDES
#include "solver.h"
#include "instruction.h"

// STD INCLUDES
#include <string>
#include <iostream>
#include <iomanip>
using std::string;
using std::cout;
using std::endl;
using std::flush;

// EXAMPLES
#include "advec.h"
//#include "lin_boussinesq.h"
//#include "lin_sw.h"
//#include "boussinesq.h"
//#include "exact.h"
//#include "lin_xy.h"
//#include "advec_fvm.h"
//#include "xyf.h"


// Solver ---------------------------------------------------------------
Solver::Solver() 
: _defined(false), _defined_instruction(false) {}

Solver::~Solver() {
	delete e;
}

Solver::Solver(string& type) 
: _defined(true), _defined_instruction(false) {
	setExample(type);
}

Solver::Solver(string& type,InstructionMap& o_map) 
: _defined(true), _defined_instruction(false) {
	setExample(type);
	if (_defined && !o_map.empty() ) {
		_defined_instruction = true;
		parseInstructionMap(o_map);
	}
}

bool Solver::exampleDefined() {
	return _defined;
}

bool Solver::instructionDefined() {
	return _defined_instruction;
}


void Solver::setExample(string& type) {
	if (type == "advec") {
		e = new advec();
	} else if (type == "lin_boussinesq") {
	//	e = new lin_boussinesq();
	} else if (type == "lin_sw") {
	//	e = new lin_sw();
	} else if (type == "boussinesq") {
	//	e = new boussinesq();
	} else if (type == "exact") {
	//	e = new exact();
	} else if (type == "lin_xy") {
	//	e = new lin_xy();
	} else if (type == "advec_fvm") {
	//	e = new advec_fvm();
	} else if (type == "xyf") {
		//e = new xyf();
	} else if (type == "example") {
		e = new Example();
	} else {
		_defined = false;
		e = NULL;
		sm.message("Equation type does not match any example.");
	}
}

void Solver::parseInstructionMap(InstructionMap& o_map) {
	InstructionMap::iterator iter = o_map.begin();
	
	for ( ; iter != o_map.end(); ++iter) {
		bool *const p = iter->second->getType();
		
		for (unsigned i=0;i<4;i++) {
			if ( p[i] && i==0 ) {
				initializer.push_back(iter->second);
			} else if ( p[i] && i==1 ) {
				beginner.push_back(iter->second);
			} else if ( p[i] && i==2 ) {
				stepper.push_back(iter->second);
			} else if ( p[i] && i==3) {
				ender.push_back(iter->second);
			} else {
			}
		}
	}
}


// SimSolver ----------------------------------------------------------------

SimSolver::SimSolver() : Solver() {}

SimSolver::~SimSolver() {}

SimSolver::SimSolver(string& type, int maxT, bool record_last_only) 
: Solver(type) {
	init(maxT,record_last_only);
}

SimSolver::SimSolver(string& type, int maxT, bool record_last_only, InstructionMap& o_map) 
: Solver(type,o_map) {
	init(maxT,record_last_only);
}

void SimSolver::init(int& maxT, bool& record_sim) {
	if (exampleDefined()) {
		done0 = done20 = done40 = done60 = done80 = 0;
		currentTime = 0;
		Record = record_sim;
		e->createStaticVars();
		
		// Instruction initializer
		for (unsigned p=0; p < initializer.size(); ++p) {
			initializer[p]->run((signed)currentTime,e);
		}
		
		if (Record) {
			if (!sm.createDirectory(e->getPath())) {
				sm.removeContents(e->getPath());
			}
		}
		
		e->createDerivedVars();
		e->createDynamicVars();
		e->createInitialData(Record);
		maxTime = (maxT == 0) ? e->getMaxTime() : maxT;
		e->setMaxTime(maxTime);
	} 
}


void SimSolver::invoke() {
	if (exampleDefined()) {
	
		// Instruction beginner
		for (unsigned p=0; p < beginner.size(); ++p) {
			beginner[p]->run((signed)currentTime,e);
		}
		
		while (currentTime<maxTime) {
			e->run(currentTime);
			
			// Instruction stepper
			for (unsigned p=0; p < stepper.size(); ++p) {
				stepper[p]->run((signed)currentTime,e);
			}
			
			if (Record) {e->record((signed)currentTime);}
			currentTime++;
			
			///////////////////////
			// Completion Status //
			///////////////////////
			switch ((int)(100*currentTime/maxTime)) {
					
				case 20:
					if (!done20) cout<<"20%..."<<flush;
					done20 = 1;
					break;
				case 40:
					if (!done40) cout<<"40%..."<<flush;
					done40 = 1;
					break;
				case 60:
					if (!done60) cout<<"60%..."<<flush;
					done60 = 1;
					break;
				case 80:
					if (!done80) cout<<"80%..."<<endl;
					done80 = 1;
					break;
				case 0:
					if (!done0) cout << ALIGN << "Completion Status: " << flush;
					done0 = 1;
					break;
				default:
					break;
			}
		}
		
		// Instruction ender
		for (unsigned p=0;p < ender.size(); p++) {
			ender[p]->run((signed)currentTime,e);
		}
		sm.message("SimSolver::invoke() Successful.");
	}
}


// Scripter ----------------------------------------------------------------

Scripter::Scripter() : Solver() {}

Scripter::~Scripter() {}

Scripter::Scripter(string& type,InstructionMap& o_map,int start,int stop,int skip,int save) 
: Solver(type,o_map) {
	if (exampleDefined()) {
		e->createStaticVars();
		// Instruction initializer
		for (unsigned p=0; p < initializer.size(); ++p) {
			initializer[p]->run(0,e);
		}
		e->createDerivedVars();
		e->definePlotVars(start,(stop == 0) ? e->getMaxTime() : stop,skip,save);
	} 
}

void Scripter::invoke() {
	if (exampleDefined()) {
		e->genGnuplotScript();
		sm.message("Scripter::invoke() Successful.");
	}
}


// Scripter_2VARS ----------------------------------------------------------------

Scripter_2VARS::Scripter_2VARS() : Solver() {}

Scripter_2VARS::~Scripter_2VARS() {}

Scripter_2VARS::Scripter_2VARS(string& type,InstructionMap& o_map,int start,int stop,int skip,int save) 
: Solver(type,o_map) {
	if (exampleDefined()) {
		e->createStaticVars();
		// Instruction initializer
		for (unsigned p=0; p < initializer.size(); ++p) {
			initializer[p]->run(0,e);
		}
		e->createDerivedVars();
		e->definePlotVars(start,(stop == 0) ? e->getMaxTime() : stop,skip,save);
	} 
}

void Scripter_2VARS::invoke() {
	if (exampleDefined()) {
		e->genGnuplotScript_2VARS();
		sm.message("Scripter_2VARS::invoke() Successful.");
	}
}

