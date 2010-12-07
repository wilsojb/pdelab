#ifndef TERMINAL_H
#define TERMINAL_H

/***************************************************************
 * File:   terminal.h
 * Author: Joshua Wilson
 * Date:   3/15/2010
 * MAIL:	pdelab-discuss@googlegroups.com
 *
 * This file is protected by the
 * GNU General License
 *
 * Description: Class that contains main(). Reads input from user
 * and calls appropriate functions in EventHandler
 *
 **************************************************************/

// SRC INCLUDES
#include "eventhandler.h"
#include "stringqueue.h"
#include "System_Manager.h"

// STD LIBRARY
#include <string>
#include <map>
#include <iostream>
using std::string;
using std::map;


class Terminal {
public:
	~Terminal();
	Terminal();
	void start();
	void readFile(string file);
	
	
private:
	typedef bool (EventHandler::*EH_Func) (StringQueue&);
	
	// The EventMap is used to map the first command in each line
	// of user input to a pointer to a function found in EventHandler
	//
	// e.g. "quit" gets mapped to &EventHandler::exit
	typedef map<string,EH_Func> EventMap;
	
	string			token;
	StringQueue		cmds;
	bool			quit;
	EventMap		handler_map;
	EventHandler	eh;
	
	string			file;
	bool			file_loaded;
};

#endif //TERMINAL_H