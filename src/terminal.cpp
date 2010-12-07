
// SRC INCLUDES
#include "terminal.h"
#include "eventhandler.h"
#include "stringqueue.h"
#include "sentence.h"
using namespace Sentence;

// STD LIBRARY
#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
using std::string;
using std::stringstream;
using std::map;
using std::cin;
using std::cout;
using std::endl;
using std::ifstream;


Terminal::~Terminal() {}
	
Terminal::Terminal() {
	quit = false;
	token = "";
	file_loaded = false;
	file = "";
		
	handler_map["quit"] = &EventHandler::exit;
	handler_map["exit"] = &EventHandler::exit;
	handler_map["#"]    = &EventHandler::comment;
	handler_map["view"] = &EventHandler::view;
	handler_map["load"] = &EventHandler::load;
	
	handler_map["sim"] = &EventHandler::sim;
	handler_map["resim"] = &EventHandler::resim;
	handler_map["script"] = &EventHandler::script;
	handler_map["script2"] = &EventHandler::script2;
	handler_map["set"] = &EventHandler::set;
	handler_map["unset"] = &EventHandler::unset;
}
	
void Terminal::start() {
		
	ifstream inf;
	if (file_loaded) {
		inf.open(&file[0]);
	} 
	
	while (!quit) {
		cmds.clear();
		cout << "pdelab > ";
		
		if (file_loaded) {
			getline(inf,token);
			cout << token << endl;
		} else {
			getline (cin,token);
		}
		
		string::size_type firstpos = token.find_first_not_of(" ");
		token = ( firstpos >= token.size() ) ? "" : token.substr(firstpos);
		if (token != "") {
			CSentence cs (token);
			for (unsigned k=0;k < cs.NumFrags();++k) {
				cmds.push( cs.Fragment(k) );
			}
			
			if (handler_map.count(cmds.peek())) {
				quit = (eh.*handler_map[cmds.pop()]) (cmds);
			} else {
				bool sysr = system(&token[0]); 
				
				// to prevent warnings
				sysr = 0; 
			}
		}
		
		if (file_loaded && inf.eof()) {
			quit = true;
		}
	}
	
	inf.close();
}

void Terminal::readFile(string file) {
	file_loaded = true;
	this->file = file;
}


int main(int argc, char* argv[]) {
	Terminal t;
	
	// Zero or one argument can be given
	// This argument should be a .pde file
	if (argc > 1) {
		stringstream ss;
		ss << argv[1];
		ifstream infile (&ss.str()[0]);
		if (!infile) {
			cout << ss.str() << " not found." << endl;
		} else {
			t.readFile(ss.str());
		}
		infile.close();
	}
	
	t.start();
	return 0;
}



