#ifndef EECS665_cool_lexer
#define EECS665_cool_lexer

#include <istream>

#if !defined(yyFlexLexerOnce)
#include "FlexLexer.h"
#endif

const int END_OF_FILE = 0;
const int NOUN = 1;
const int VERB = 2;
const int ADJECTIVE = 3;
const int ERROR = -1;

class Token{
public:
	virtual std::string toString(){ return "TOKEN"; }
};

class NounToken : public Token{
public:
	NounToken(std::string input) : myVal(input){ }
	virtual std::string toString(){ return myVal; }
	const std::string myVal;
};

class VerbToken : public Token{
public:
	VerbToken(std::string input) : myVal(input){ }
	virtual std::string toString(){ return myVal; }
	const std::string myVal;
};

class AdjectiveToken : public Token{
public:
	AdjectiveToken(std::string input) : myVal(input){ }
	virtual std::string toString(){ return myVal; }
	const std::string myVal;
};

class MyLexer : public yyFlexLexer{
public:
	MyLexer(std::istream * in) : yyFlexLexer(in){ }
	int produceToken(Token ** tok);
};

#endif
