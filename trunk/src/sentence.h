/*////////////////////////////////////////////////////////////
//                                                          //
// File: sentence.h                                         //
// Version 1.0                                              //
// Author: Ed Santilli                                      //
// Date: Jun 17, 2004                                       //
//                                                          //
// Legal info: This file may be used or modified in any way //
//  if and only if it is integrated into projects that will //
//  be distributed free of charge.                          //
//                                                          //
////////////////////////////////////////////////////////////*/


#ifndef _SENTENCE_H__INCLUDED_
#define _SENTENCE_H__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif /* _MSC_VER > 1000 */


/* Prerequisites */
#include <string>
#include <list>
#include <map>

#define SENTENCE_DEFAULT_MAXLENGTH 250
#define SENTENCE_DEFAULT_VARIABLE_SIG '$'
#define SENTENCE_DEFAULT_DELIMITER ' '

typedef unsigned int UINT;
typedef std::string (* pVarFunc)(void);


/* Associated namespace declaration */
namespace Sentence
{
	std::string VarSigChar();
	std::string DateTime();
}


/*////////////////////////////////////////////////////////////
// The CSentence class declaration                          //
/////////////////////////////////////////////////////////////*/
class CSentence  
{
public:
	/* Construction/Destruction */
	CSentence();
	CSentence(const std::string&);
	CSentence(const CSentence&);
	~CSentence();

	/* Member functions */
	void String(const std::string&);
	const std::string& String() const;

	std::string SubstString();
	void Show();
	
	const UINT& MaxLength() const;
	void MaxLength(const UINT&);
	
	const char& VarSig() const;
	void VarSig(const char&);
	void AddVar(const std::string&, pVarFunc);
	void RemVar();
	void RemVar(const std::string&);
	
	void AddDelim(const char&);
	void RemDelim();
	void RemDelim(const char&);

	/* Access a member of m_Fragment using at iterator */ 
	const std::string& Fragment(const UINT&) const;
	
	UINT NumDelims() const;
	UINT NumFrags() const;

private:
	/* Member variables */
	UINT m_MaxLength;
	std::string m_String;
	char m_Variable_Sig;
	std::map<std::string, pVarFunc> m_Variable;
	std::list<char> m_Delimiter;
	std::list<std::string> m_Fragment;

	/* Member functions */
	std::string m_Substitute();
	void m_Update();
};


#endif /* _SENTENCE_H__INCLUDED_ */
