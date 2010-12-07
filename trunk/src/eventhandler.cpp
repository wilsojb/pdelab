
// SRC INCLUDES
#include "sentence.h"
#include "stringqueue.h"
#include "eventhandler.h"
#include "terminal.h"
#include "solver.h"
#include "instruction.h"
using namespace Sentence;


// STD LIBRARY
#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
#include <sstream>
#include <vector>
#include <cmath>
using std::endl;
using std::cout;
using std::string;
using std::ifstream;
using std::ofstream;
using std::stringstream;
using std::vector;
using std::pow;


EventHandler::EventHandler() {
	// Used by EventHandler::resim()
	SIMVAR_bool = true;
	SIMVAR_string = "";
	SIMVAR_time = 0;
	SIMVAR_copy = false;
}

EventHandler::~EventHandler() {
	// This unsets all the Instructions before 
	// exiting pdelab thus preventing wild pointers
	StringQueue erase;
	erase.push("all");
	unset(erase);
}


bool EventHandler::exit(StringQueue& cmds) {
	cmds.peek();	// prevents warning
	return true;
}
	
bool EventHandler::comment(StringQueue& cmds) {
	cmds.peek();	// prevents warning
	return false;
}

bool EventHandler::view(StringQueue& cmds) {
	if (!cmds.isEmpty()) {
		string cmd2 = cmds.pop();
			
		// Prints out all currently set Instructions
		if ( cmd2 == "setlist" ) {
			InstructionMap::iterator iter = o_map.begin();
			cout << ALIGN;
			for (; iter != o_map.end(); ++iter) {
				cout << iter->first << " ";
			}
			cout << endl;
			
		} else {
			// cmd2 == [filename]
			// Prints out contents of [filename]
			sm.file(sm.pde_path + cmd2 + sm.pde_suffix);
			ifstream infile (&cmd2[0]);
			if (!infile) {
				sm.error(cmd2 + " not found."); 
			} else {
				string line;
				while (!infile.eof()) {
					getline (infile, line);
					cout << ALIGN <<line << endl;
				}
				infile.close();
			}
		}
		
	} else{
		sm.format("view [filename] || [setlist]");
	}
	
	return false;
}

	
bool EventHandler::load(StringQueue& cmds) {
	if (cmds.size() >= 1) {
		
		// Loads [filename] and executes in pdelab environment
		string cmd2 = sm.pde_path + cmds.pop() + sm.pde_suffix;
		sm.loading(cmd2);
		ifstream infile (&cmd2[0]);
		if (!infile) {
			sm.error(cmd2 + " not found.");
		} else {
			Terminal t;
			t.readFile(cmd2);
			t.start();
		}
		infile.close();
		
	} else {
		sm.format("load [filename]"); 
	}
	
	return false;
}
	
bool EventHandler::sim(StringQueue& cmds) {
	if (!cmds.isEmpty()) {
		SIMVAR_copy = true;
		
		// Initializes a SimSolver object
		// See solver.h and solver.cpp for more info
		SIMVAR_string = cmds.pop();	
		std::vector<int> vars(10);
		vars[1] = 1;
		for (int i=0; !cmds.isEmpty();++i) {
			vars[i] = atoi(&cmds.pop()[0]);
		}
	
		clock_t to = clock();
		
		SIMVAR_time = vars[0];
		SIMVAR_bool = bool(vars[1]);
		SimSolver ss( SIMVAR_string , SIMVAR_time , SIMVAR_bool,o_map);
		ss.invoke();
		
		double time = (clock()-to)/(double)CLOCKS_PER_SEC;
		cout<< ALIGN << "sim time = " << time << " secs" << endl;
		
	} else {
		sm.format("sim [sim name] {max time} {record sim}" );
	}
	return false;
}
	
bool EventHandler::resim(StringQueue& cmds) {
	cmds.peek();	// prevents warning
	
	if (SIMVAR_copy) {
		clock_t to = clock();
		SimSolver ss( SIMVAR_string , SIMVAR_time , SIMVAR_bool,o_map);
		ss.invoke();
		cout<< ALIGN << "sim time = "<<(clock()-to)/(double)CLOCKS_PER_SEC<<endl;
	} else {
		sm.error("sim must be called before resim.");
	}
	return false;
}
	
bool EventHandler::script(StringQueue& cmds) {
	if (!cmds.isEmpty()) {
		
		// Initializes a Scripter object
		// See solver.h and solver.cpp for more info
		string cmd2 = cmds.pop();
		vector<int> vars(10);
		for (int i=0; !cmds.isEmpty();++i) {
			vars[i] = atoi(&cmds.pop()[0]);
		}
	
		Scripter s(cmd2,o_map, vars[1],							// start
				   (vars[2] == 0) ? SIMVAR_time : vars[2],		// stop
				   (vars[0] == 0) ? 1 : vars[0],				// skip
				   vars[3]);									// save
		s.invoke();
		
	} else {
		sm.format("script [sim name] {skip #frames} {start #frame} {final #frame} {save}");
	}
	
	return false;
}

bool EventHandler::script2(StringQueue& cmds) {
	if (!cmds.isEmpty()) {
		
		// Initializes a Scripter object
		// See solver.h and solver.cpp for more info
		string cmd2 = cmds.pop();
		vector<int> vars(10);
		for (int i=0; !cmds.isEmpty();++i) {
			vars[i] = atoi(&cmds.pop()[0]);
		}
		
		Scripter_2VARS s(cmd2,o_map, vars[1],					// start
				   (vars[2] == 0) ? SIMVAR_time : vars[2],		// stop
				   (vars[0] == 0) ? 1 : vars[0],				// skip
				   vars[3]);									// save
		s.invoke();
		
	} else {
		sm.format("script [sim name] {skip #frames} {start #frame} {final #frame} {save}");
	}
	
	return false;
}
	

bool EventHandler::set(StringQueue& cmds) {
	if (cmds.size() >= 2) {
		
		// Sets an Instruction. Use view setlist in order to view 
		// currently set Instructions.  
		// o_map gets passed to SimSolver during initialization
		string cmd2 = cmds.pop();
		string cmd3 = cmds.pop();	
		if (cmd2 == "norm") {
			o_map.insert( std::pair<std::string,pInstruction>(cmd2,new Norm(cmd3,cmds)) );
			
		} else if (cmd2 == "diffnorm") {
			o_map.insert( std::pair<std::string,pInstruction>(cmd2,new Diffnorm(cmd3,cmds)) );
			
		} else if (cmd2 == "test") {
			o_map.insert( std::pair<std::string,pInstruction>(cmd2,new Test(cmd3,cmds)) );
			
		} else if (cmd2 == "output") {
			o_map.insert( std::pair<std::string,pInstruction>(cmd2,new Output(cmd3,cmds)) );
			
		} else if (cmd2 == "filename") {
			o_map.insert( std::pair<std::string,pInstruction>(cmd2,new Filename(cmd3,cmds)) );
			
		} else{
			sm.error("Instruction not defined in EventHandler.");
		}
		
	} else {
		sm.format("set [instruction] [sim name]");
	}
	
	return false;
}

bool EventHandler::unset(StringQueue& cmds) {
	if (cmds.size() >= 1) {
		string cmd2 = cmds.pop();
		InstructionMap::iterator iter = o_map.begin();
		if (cmd2 == "all") {
			for ( ; iter != o_map.end(); ++iter) {
				delete iter->second;
				o_map.erase(iter);
			}
			
		} else {
			for ( ; iter != o_map.end(); ++iter) {
				if (cmd2 == iter->first) {
					delete iter->second;
					o_map.erase(iter);
				}
			}
		}
		
	} else {
		sm.format("unset [all] || [Instruction]");
	}
	
	return false;
}
	

