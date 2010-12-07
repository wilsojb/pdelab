
#ifndef STRINGQUEUE_H
#define STRINGQUEUE_H

/***************************************************************
 * File:   stringqueue.h
 * Author: Joshua Wilson
 * Date:   3/15/2010
 * MAIL:	pdelab-discuss@googlegroups.com
 *
 * This file is protected by the
 * GNU General License
 *
 *
 * Description: Simple implementation of a queue for strings.
 * More customizable than std::queue<std::string>.
 *
 **************************************************************/

// SRC INCLUDES
#include "System_Manager.h"

#include <list>
#include <string>
using std::list;
using std::string;

 
class StringQueue {
public:
	StringQueue() {
		pops = 0;
	}
	
	~StringQueue() {}
	
	string pop() {
		pops++;
		string ret = l.back();
		l.pop_back();
		return ret;
	}
	
	void erase(string& element) {
		std::list<string>::iterator iter = l.begin();
		while ( iter != l.end() ) {
			if (*iter == element) l.erase(iter);
			iter++;
		}
	}
	
	std::string peek() {
		if (!isEmpty()) {
			return l.back();
		}
		return "STRINGQUEUE IS EMPTY";
	}
	
	bool isEmpty() {return !l.size();}
	void push(string s)  {l.push_front(s);}
	int size() {return l.size();}
	void clear() {l.clear();}
	int numPops() {return pops;}
	
private:
	list<string> l;
	int			 pops;
};


#endif //STRINGQUEUE_H