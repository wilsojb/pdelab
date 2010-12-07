#ifndef SYSTEM_MANAGER_H
#define SYSTEM_MANAGER_H

/***************************************************************
 * File:   System_Manager.h
 * Author: Joshua Wilson
 * Date:   7-26-10
 * MAIL:  pdelab-discuss@googlegroups.com
 *
 * This file is protected by the GNU General License.
 *
 * Description: File containing macros for debugging and the
 *				System_Manager class which handles file 
 *				management and output.
 **************************************************************/


// SRC INCLUDES
#include "sentence.h"

// STL INCLUDES
#include <string>
#include <iostream>
#include <sys/stat.h>
#include <assert.h>
#include <stdio.h>
#include <cstdlib>

#define ALIGN "         "

#ifndef NDEBUG
#	define _DEBUG_
#endif


#ifdef _DEBUG_

#	define PRINT	std::cout

// Puts a checkpoint into pout.*
#	define CHECKPOINT()												\
PRINT << "CHECK: " << __FILE__ << ": " << __LINE__ << std::endl

// Wrapper for debug-only code.
#	define DEBUG_CODE(x) { x }

#else // DEBUG
#	define CHECKPOINT()
#	define DEBUG_CODE(_x)
#endif // DEBUG


class System_Manager {
public:
	System_Manager();
	~System_Manager();
	
	void message(std::string message);
	void warning(std::string message);
	void error(std::string message);
	void format(std::string message);
	void loading(std::string message);
	void file(std::string message);
	bool createDirectory(std::string token);
	void removeContents(std::string token);
	
	// path and suffices
	std::string		dat_path;
	std::string		dat_suffix;
	std::string		pde_path;
	std::string		pde_suffix;
	std::string		gp_path;
	std::string		gp_suffix;
	
};


#endif	// SYSTEM_MANAGER_H




