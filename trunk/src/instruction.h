#ifndef INSTRUCTION_H
#define INSTRUCTION_H


/***************************************************************
 * File:   instruction.h
 * Author: Joshua Wilson
 * Date:   3/15/2010
 * MAIL:	pdelab-discuss@googlegroups.com
 *
 * This file is protected by the
 * GNU General License
 *
 *
 * Description: Instructions observe/manipulate simulations 
 * taking place. They collect/alter data at various stages of a simulation 
 * (0001, 0010, 0100, or 1000) or any combination
 *
 * 0001: Instruct after simulation is complete
 * 0010: Instruct during a simulation
 * 0100: Instruct after dynamic creation but before the simulation starts
 * 1000: Instruct after static creation and before dynamic creation
 * 1010: combination of 1000 and 0010
 *
 * Nothing exsits before static creation so there is no reason 
 * to observe/manipulate before then. 
 *
 *
 **************************************************************/


// SRC INCLUDES
#include "example.h"
#include "System_Manager.h"
#include "stringqueue.h"

// STD LIBRARY
#include <map>
#include <vector>
#include <string>
using std::vector;
using std::string;


class Instruction {
public:
	Instruction(string sim_name,StringQueue vars);
	virtual ~Instruction();
	bool * getType() const;
	string getSim() const;
	virtual void run(int timestamp,Example* e);
	
protected:
	// position stores the location (1000,0100,0010,0001)
	bool*				position;
	// every observer is tied to a simulation
	string				sim_name;
	System_Manager		sm;
	StringQueue			vars;
	string				path;
	string				filename;
	
};

// An ObserverMap is used by eventhandler to store all of the
// currently set observers
typedef Instruction*						pInstruction;
typedef std::multimap<std::string,pInstruction> InstructionMap;


// see .cpp file for an example setup
class Test : public Instruction {
public:
	Test(string sim_name,StringQueue vars);
	virtual ~Test();
	void run(int timestamp, Example* e);
};

class Norm : public Instruction {
public:
	Norm(string sim_name,StringQueue vars);
	virtual ~Norm();
	void run(int timestamp,Example* e);
	
private:
	unsigned nx;
	vector<double> v;
	double dx;
	
	double pnorm;
	double norm;
};

class Diffnorm : public Instruction {
public:
	Diffnorm(string sim_name,StringQueue vars);
	virtual ~Diffnorm();
	void run(int timestamp,Example* e);
	
private:
	unsigned nx;
	vector<double> v1;
	vector<double> v2;
	double dx;
	double dt;
	
	double pnorm;
	double norm;
};

class Filename : public Instruction {
public:
	Filename(string sim_name,StringQueue vars);
	virtual ~Filename();
	void run(int timestamp,Example* e);
};


class Output : public Instruction {
public:
	Output(string sim_name,StringQueue vars);
	virtual ~Output();
	void run(int timestamp,Example* e);
};



#endif	// OBSERVER_H
