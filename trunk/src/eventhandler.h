#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H


/***************************************************************
 * File:   eventhandler.h
 * Author: Joshua Wilson
 * Date:   3/15/2010
 * MAIL:	pdelab-discuss@googlegroups.com
 *
 * This file is protected by the
 * GNU General License
 *
 *
 * Description: Class that handles all commands from Terminal
 * See below for a short description of each command
 *
 **************************************************************/


// SRC INCLUDES
#include "stringqueue.h"
#include "instruction.h"
#include "System_Manager.h"

// STD LIBRARY
#include <string>
using std::string;


class EventHandler {
private:
	friend class Terminal;
	
	// CONSTRUCTORS
	EventHandler();
	~EventHandler();
	
	// COMMANDS
	bool exit(StringQueue& cmds);		// exits pdelab
	bool comment(StringQueue& cmds);	// # comment token
	bool view(StringQueue& cmds);		// view [filename] || [setlist]
	bool load(StringQueue& cmds);		// load [filename]
	bool sim(StringQueue& cmds);		// sim [sim name] {max time} {record last only}
	bool resim(StringQueue& cmds);		// call sim with same parameters
	bool script(StringQueue& cmds);		// script [sim name] {skip #frames} {start #frame} {final #frame} {save}
	bool script2(StringQueue& cmds);
	bool set(StringQueue& cmds);		// set [Instruction] [sim name]
	bool unset(StringQueue& cmds);		// unsets an Instruction or all
	
	
	InstructionMap		o_map;
	System_Manager		sm;
	
	// used by resim
	int					SIMVAR_time;
	bool				SIMVAR_bool;
	bool				SIMVAR_copy;
	string				SIMVAR_string;
};

#endif //EVENTHANDLER_H

