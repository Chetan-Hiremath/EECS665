#ifndef __EECS_SCANNER_HPP
#define __EECS_SCANNER_HPP
#if !defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif
#include "grammar.hh"
#include <istream>
#include <fstream>
#include <ostream>
using namespace std;

namespace EECS
{
    class Scanner : yyFlexLexer
    {
      public:
        Scanner(std::istream* in) : yyFlexLexer(in)
        { 
          lineNum = 0;
          charNum = 0;
        } 
        virtual ~Scanner() { }
        virtual int yylex(EECS::Parser::semantic_type* lval);
        void warning(int lineNum, int charNum, std::string msg)
        {
          cerr << "The Lex problem is at " << lineNum << ", " << charNum << " ***WARNING*** " << msg;
        }
        void error(int lineNum, int charNum, std::string msg)
        { 
          cerr << "The Lex problem is at " << lineNum << ", " << charNum << " ***ERROR*** " << msg;
        }   
      private:
        EECS::Parser::semantic_type* yylval = nullptr;
        size_t lineNum = 0;
        size_t charNum = 0;               
    }; /* end class EECS::Scanner */
} /* and namespace */
#endif
