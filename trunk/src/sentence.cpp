/*////////////////////////////////////////////////////////////
//                                                          //
// File: sentence.cpp                                       //
// Version 1.0                                              //
// Author: Ed Santilli                                      //
// Date: Jun 17, 2004                                       //
//                                                          //
// Legal info: This file may be used or modified in any way //
//  if and only if it is integrated into projects that will //
//  be distributed free of charge.                          //
//                                                          //
////////////////////////////////////////////////////////////*/


/* Prerequisites */
#include "sentence.h"
#include <iostream>


/* Associated namespace definition */
std::string Sentence::VarSigChar()
{
	std::string Ret_String = "$";
	return Ret_String;
}


std::string Sentence::DateTime()
{
	time_t Raw_Time;
	time(&Raw_Time);
	tm* Time_Info = localtime(&Raw_Time);
	
	std::string Ret_String = asctime(Time_Info);
	return Ret_String.substr(0, 24);
}


/*////////////////////////////////////////////////////////////
// The CSentence class implementation                       //
////////////////////////////////////////////////////////////*/

/* Constructors */
CSentence::CSentence()
{
	m_MaxLength = SENTENCE_DEFAULT_MAXLENGTH;
	m_Variable_Sig = SENTENCE_DEFAULT_VARIABLE_SIG;
	char Default_Delimiter = SENTENCE_DEFAULT_DELIMITER;
	
	m_String.assign("", 0, m_MaxLength);
	m_Variable[""] = *Sentence::VarSigChar;
	if(Default_Delimiter)
		m_Delimiter.push_front(Default_Delimiter);	
	
	m_Update();
}


CSentence::CSentence(const std::string& StringRef)
{
	
	m_MaxLength = SENTENCE_DEFAULT_MAXLENGTH;
	m_Variable_Sig = SENTENCE_DEFAULT_VARIABLE_SIG;
	char Default_Delimiter = SENTENCE_DEFAULT_DELIMITER;
	
	m_String.assign(StringRef, 0, m_MaxLength);	
	m_Variable[""] = *Sentence::VarSigChar;
	if(Default_Delimiter)
		m_Delimiter.push_front(Default_Delimiter);	
	
	
	m_Update();
}


/* Destructor */
CSentence::~CSentence()
{}


/* Public Member functions */
void CSentence::String(const std::string& StringRef)
{
	m_String.assign(StringRef, 0, m_MaxLength);
	m_Update();
}


const std::string& CSentence::String() const
{
	return m_String;
}


std::string CSentence::SubstString()
{
	std::string Ret_String = m_Substitute();
	return m_Substitute();
}


void CSentence::Show()
{
    std::cout << SubstString();
}


const UINT& CSentence::MaxLength() const
{
	return m_MaxLength;
}


void CSentence::MaxLength(const UINT& MaxLengthRef)
{
	m_MaxLength = MaxLengthRef;
	String(m_String);
}


const char& CSentence::VarSig() const
{
	return m_Variable_Sig;
}


void CSentence::VarSig(const char& Variable_SigRef)
{
	m_Variable_Sig = Variable_SigRef;
}


void CSentence::AddVar(const std::string& VariableRef, pVarFunc pVar_Action)
{
	m_Variable[VariableRef] = pVar_Action;
	m_Update();
}


void CSentence::RemVar()
{
	m_Variable.clear();
	m_Update();
}


void CSentence::RemVar(const std::string& VariableRef)
{
	m_Variable.erase(VariableRef);
	m_Update();
}


void CSentence::AddDelim(const char& DelimiterRef)
{
	if(DelimiterRef) m_Delimiter.push_front(DelimiterRef);
	m_Delimiter.sort();
	m_Delimiter.unique();
	m_Update();
}


void CSentence::RemDelim()
{
	m_Delimiter.clear();
	m_Update();
}


void CSentence::RemDelim(const char& DelimiterRef)
{
	m_Delimiter.remove(DelimiterRef);
	m_Update();
}


const std::string& CSentence::Fragment(const UINT& Frag_Index) const
{
	std::list<std::string>::const_iterator Frag_Iter = m_Fragment.begin();
	for(UINT Index_Count = 0; Index_Count < Frag_Index; Index_Count++)
		Frag_Iter++;
	
	return *Frag_Iter;
}


UINT CSentence::NumDelims() const
{
	return m_Delimiter.size();
}


UINT CSentence::NumFrags() const
{
	return m_Fragment.size();
}


/* Private member functions */
std::string CSentence::m_Substitute()
{
	std::string Ret_String = m_String;
	
	UINT String_Offset = 0;
	
	
	UINT Variable_Header = Ret_String.find(m_Variable_Sig, String_Offset);
	UINT Variable_Footer = Ret_String.find(m_Variable_Sig, Variable_Header + 1);
	//while((Variable_Header != std::string::npos) && (Variable_Footer != std::string::npos))
	//{
	
	while((Variable_Header < Ret_String.size()) && (Variable_Footer < Ret_String.size()))
	{
	
		
		std::string Variable =
            Ret_String.substr(Variable_Header + 1,
                              Variable_Footer - Variable_Header - 1);
		
		pVarFunc pVar_Action = m_Variable[Variable];
		std::string Var_Action_Output = "<DNE>";
		if(pVar_Action) Var_Action_Output = pVar_Action();
		
		Ret_String.erase(Variable_Header,
                         Variable_Footer - Variable_Header + 1);
				
		Ret_String.insert(Variable_Header, Var_Action_Output);
		
		String_Offset = Variable_Header + Var_Action_Output.length();
		
		
		Variable_Header = Ret_String.find(m_Variable_Sig, String_Offset);
		Variable_Footer = Ret_String.find(m_Variable_Sig, Variable_Header + 1);
	}
	
	return Ret_String;
}


void CSentence::m_Update()
{
	typedef std::list<char>::const_iterator CLI;
	typedef std::list<UINT>::const_iterator ULI;
	
	std::string Subst_String = m_Substitute();
	UINT String_Offset;
	std::list<UINT> Delim_Pos;
	
	
	for(CLI Delim_Iter = m_Delimiter.begin(); 
		Delim_Iter != m_Delimiter.end(); 
		Delim_Iter++)
	{
		String_Offset = 0;
		
		do
		{
			String_Offset = Subst_String.find(*Delim_Iter, String_Offset);
			if(String_Offset > Subst_String.length() )
                String_Offset = Subst_String.length();
			Delim_Pos.push_front(String_Offset);
		} while(++String_Offset < Subst_String.length());
	}
	Delim_Pos.push_front(Subst_String.length());
	Delim_Pos.sort();
	Delim_Pos.unique();		
	m_Fragment.clear();

	ULI Delim_Pos_Iter = Delim_Pos.begin();

	String_Offset = 0;
	UINT String_Length = *Delim_Pos_Iter;
	if(String_Length > 0)
        m_Fragment.push_front(Subst_String.substr(String_Offset,
                                                  String_Length));
	
	
	for(++Delim_Pos_Iter; Delim_Pos_Iter != Delim_Pos.end(); Delim_Pos_Iter++)
	{
		Delim_Pos_Iter--;
		String_Offset = *Delim_Pos_Iter + 1;
		String_Length = *(++Delim_Pos_Iter) - String_Offset;
		if(String_Length > 0)
            m_Fragment.push_front(Subst_String.substr(String_Offset,
                                                      String_Length));
	}

	m_Fragment.reverse();
}
