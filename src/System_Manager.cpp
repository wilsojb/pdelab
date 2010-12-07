
// SRC INCLUDES
#include "System_Manager.h"


System_Manager::System_Manager() {
	pde_path = "pde/";
	pde_suffix = ".pde";
	dat_path = "dat/";
	dat_suffix = ".dat";
	gp_path = "gp/";
	gp_suffix = ".gp";
}

System_Manager::~System_Manager() {}

void System_Manager::message(std::string message) {
	std::cout << ALIGN << message << std::endl;
}

void System_Manager::warning(std::string message) {
	std::cout << ALIGN << "Warning: " << message << std::endl;
}

void System_Manager::error(std::string message) {
	std::cout << ALIGN << "Error: " << message << std::endl;
}

void System_Manager::format(std::string message) {
	std::cout << ALIGN << "Format: " << message << std::endl;
}

void System_Manager::file(std::string message) {
	std::cout << ALIGN << "File: " << message << std::endl;
}

void System_Manager::loading(std::string message) {
	std::cout << ALIGN << "Loading: " << message << std::endl;
}

// dat/ must be included in the path before this method is called
bool System_Manager::createDirectory(std::string token) {
	CSentence cs (token);
	std::string delim = "/";
	cs.RemDelim();
	cs.AddDelim(delim.c_str()[0]);
	bool ret = false;
	
	struct stat FileInfo;
	std::string complete = "";
	for (unsigned k=0;k < cs.NumFrags();++k) {
		complete.append(cs.Fragment(k)+"/");
		if (stat(complete.c_str(),&FileInfo)) {
			ret = true; 
			std::string output = "mkdir " + complete;
			bool sysr = system(&output[0]); sysr = 0; // prevent warnings
			warning(complete + " created.");
		}
	}
	
	return ret;
}

// dat/ must be included in the path before this method is called
void System_Manager::removeContents(std::string token) {
	struct stat FileInfo;
	if (!stat(token.c_str(),&FileInfo)) {
		std::string output = "rm -rf " + token + "/*" + dat_suffix;
		bool sysr = system(&output[0]); sysr = 0;	// prevent warnings
		warning("Contents of " + token + " were deleted.");
	}
}







