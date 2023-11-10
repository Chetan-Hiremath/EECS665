%{
#include <string>
#include <limits.h>

/* Get our custom yyFlexScanner subclass */
#include "scanner.hpp"
#undef YY_DECL
#define YY_DECL int jeff::Scanner::yylex(jeff::Parser::semantic_type * const lval)

using TokenKind = jeff::Parser::token;

/* define yyterminate as returning an EOF token (instead of NULL) */
#define yyterminate() return ( TokenKind::END )

/* exclude unistd.h for Visual Studio compatibility. */
#define YY_NO_UNISTD_H

%}

%option nodefault
%option yyclass="jeff::Scanner"
%option noyywrap
%option c++

DIGIT [0-9]
WHITESPACE [\040\t]
LETTER [a-zA-Z]
ESCAPEE [nt'"\\]

%%
%{
	this->yylval = lval;
%}

bool 	    { return makeBareToken(TokenKind::BOOL); }
close 	    { return makeBareToken(TokenKind::CLOSE); }
console	    { return makeBareToken(TokenKind::CONSOLE); }
else	    { return makeBareToken(TokenKind::ELSE); }
false	    { return makeBareToken(TokenKind::FALSE); }
file	    { return makeBareToken(TokenKind::FILE); }
fn	    { return makeBareToken(TokenKind::FN); }
if  	    { return makeBareToken(TokenKind::IF); }
int 	    { return makeBareToken(TokenKind::INT); }
open	    { return makeBareToken(TokenKind::OPEN); }
return	    { return makeBareToken(TokenKind::RETURN); }
true	    { return makeBareToken(TokenKind::TRUE); }
void	    { return makeBareToken(TokenKind::VOID); }
while	    { return makeBareToken(TokenKind::WHILE); }
"&&"        { return makeBareToken(TokenKind::AND); }
"="         { return makeBareToken(TokenKind::ASSIGN); }
":"         { return makeBareToken(TokenKind::COLON); }
","         { return makeBareToken(TokenKind::COMMA); }
"+"         { return makeBareToken(TokenKind::CROSS); }
"-"         { return makeBareToken(TokenKind::DASH); }
"=="        { return makeBareToken(TokenKind::EQUALS); }
">"         { return makeBareToken(TokenKind::GREATER); }
">="        { return makeBareToken(TokenKind::GREATEREQ); }
"{"	    { return makeBareToken(TokenKind::LCURLY); }
"<"	    { return makeBareToken(TokenKind::LESS); }
"<="	    { return makeBareToken(TokenKind::LESSEQ); }
"("	    { return makeBareToken(TokenKind::LPAREN); }
"["	    { return makeBareToken(TokenKind::LBRACE); }
"!"	    { return makeBareToken(TokenKind::NOT); }
"!="	    { return makeBareToken(TokenKind::NOTEQUALS); }
"||"	    { return makeBareToken(TokenKind::OR); }
"--"	    { return makeBareToken(TokenKind::POSTDEC); }
"++"	    { return makeBareToken(TokenKind::POSTINC); }
"?"	    { return makeBareToken(TokenKind::QUESTION); }
"]"	    { return makeBareToken(TokenKind::RBRACE); }
">>"	    { return makeBareToken(TokenKind::READ); }
"}"	    { return makeBareToken(TokenKind::RCURLY); }
")"	    { return makeBareToken(TokenKind::RPAREN); }
";"	    { return makeBareToken(TokenKind::SEMICOL); }
"/"	    { return makeBareToken(TokenKind::SLASH); }
"*"	    { return makeBareToken(TokenKind::STAR); }
"<<"	    { return makeBareToken(TokenKind::WRITE); }
({LETTER}|_)({LETTER}|{DIGIT}|_)* { 
		            yylval->transToken = 
		            new IDToken(lineNum, colNum, yytext);
		            colNum += yyleng;
		            return TokenKind::ID; }

{DIGIT}+	    { double asDouble = std::stod(yytext);
			          int intVal = atoi(yytext);
			          bool overflow = false;
			          if (asDouble > INT_MAX){ overflow = true; }
			          if (strlen(yytext) > 10){ overflow = true; }

			          if (overflow){
				            errIntOverflow(lineNum, colNum);
				            intVal = 0;
			          }
			          yylval->transToken = 
			              new IntLitToken(lineNum, colNum, intVal);
			          colNum += yyleng;
			          return TokenKind::INTLITERAL; }

\"([^\n"\\]|\\{ESCAPEE})*\" {
   		          yylval->transToken = 
                    new StrToken(lineNum, colNum, yytext);
		            this->colNum += yyleng;
		            return TokenKind::STRINGLITERAL; }

\"([^\n"\\]|\\{ESCAPEE})* {
		            errStrUnterm(lineNum, colNum);
		            colNum = 1; /*Upcoming \n resets lineNum */
		            }

\"([^\n"\\]|\\{ESCAPEE})*\\[^\nnt"\\]([^\n"])*\" {
		            errStrEsc(lineNum, colNum);
		            colNum += yyleng; }

\"([^\n"\\]|\\{ESCAPEE})*(\\[^\nnt"\\])?([^\n"\\]|\\{ESCAPEE})*\\? {
		            errStrEscAndUnterm(lineNum, colNum);
		            colNum = 1; }

\n|(\r\n)     { lineNum++; colNum = 1; }


[ \t]+	      { colNum += yyleng; }

("#")[^\n]*	  { /* Comment. Ignore. Don't need to update 
                   line num since everything up to end of 
                   line will never by part of a report*/ 
		   colNum += yyleng;
		  }

.		          { errIllegal(lineNum, colNum, yytext);
		            this->colNum += yyleng; }
%%