#ifndef SOLVER_H
#define SOLVER_H

/***************************************************************
 * File:   solver.h
 * Author: Joshua Wilson
 * Date:   3/15/2010
 * MAIL:	pdelab-discuss@googlegroups.com
 *
 * This file is protected by the
 * GNU General License
 *
 * Description: Class used to solve Examples in various ways.
 * Any new Solvers are expected to call methods found in Example.h
 *
 * The easiest way to explain what this class does is it utilizes the
 * vast number of methods provided by Example.h in order to solve,
 * display, analyze, or whatever.  An Example, which must extend
 * Example.h, contains all of the base code for the solution to a
 * PDE.  It is the job of the Solver to use that base code in 
 * an efficient, creative, and/or purposeful manner.  
 * 
 * Another way of explaining it is that although an Example defines
 * the solution to a PDE, it can't generate solutions by itself. 
 * Every Example must be solved by a Solver.
 *
 * For more advanced users:  The various functionality that Example.h
 * provides can be extended without much modification to the Example
 * or to the Solver through the use of Instructions.  Instruction.h
 * provides a way to insert snippets of code into the Solver in a 
 * highly modular way.  See Instruction.h for more details.
 *
 **************************************************************/

// SRC INCLUDES
#include "example.h"
#include "instruction.h"
#include "System_Manager.h"

// STD INCLUDES
#include <string>
#include <vector>
using std::string;
using std::vector;


class Solver {
public:
	Solver();
	Solver(string& type);
	Solver(string& type, InstructionMap& o_map);
	virtual ~Solver();
	bool exampleDefined();
	bool instructionDefined(); 
	
	// Every child of Solver must override this functions
	virtual void invoke()=0;
	
protected:
	Example* e;
	System_Manager sm;
	vector<pInstruction> stepper;
	vector<pInstruction> ender;
	vector<pInstruction> beginner;
	vector<pInstruction> initializer;
	
	
private:
	bool _defined;
	bool _defined_instruction;
	void parseInstructionMap(InstructionMap& o_map);
	
	// Every new Example must be added to this function
	// See Solver.cpp for clarity
	//
	// Furthermore, the new Example files must be included
	// at the top of Solver.cpp
	void setExample(string& type);
	
	
};

// Solves Examples on a single core, single thread
// Records the results
class SimSolver : public Solver {
public:
	SimSolver();
	virtual ~SimSolver();
	SimSolver(string& type,int maxT, bool record_sim);
	SimSolver(string& type,int maxT, bool record_sim, InstructionMap& o_map);
	void invoke();
	
private:
	unsigned int currentTime;
	unsigned int maxTime;
	bool Record;
	void init(int& maxT, bool& record_sim);
	bool done0, done20,done40,done60,done80;
};

// Calls the Examples gnuplot scripting routines
// Scripts are then saved to pdelab/gp/
class Scripter : public Solver {
public:
	Scripter();
	virtual ~Scripter();
	Scripter(string& type,InstructionMap& o_map,int start,int stop,int skip,int save);
	void invoke();
};

// Calls the Examples gnuplot scripting routines (for two fields)
// Scripts are then saved to pdelab/gp/
class Scripter_2VARS : public Solver {
public:
	Scripter_2VARS();
	virtual ~Scripter_2VARS();
	Scripter_2VARS(string& type,InstructionMap& o_map,int start,int stop,int skip,int save);
	void invoke();
};


#endif	// SOLVER_H
