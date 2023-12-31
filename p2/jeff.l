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

#define EXIT_ON_ERR 0


%}

%option nodefault
%option yyclass="jeff::Scanner"
%option noyywrap
%option c++

DIGIT [0-9]
WHITESPACE [\040\t]
LETTER [a-zA-Z]
ESCAPEE [nt'"\\]

 /* */ 
BADESC [\\][^nt"\\\n]?
STRELT (\\[nt"\\])|([^\\\n"])

%%
%{
	this->yylval = lval;
%}

int    		    { return makeBareToken(TokenKind::INT); }
fn		    { return makeBareToken(TokenKind::FN); }
bool 		      { return makeBareToken(TokenKind::BOOL); }
void 		      { return makeBareToken(TokenKind::VOID); }
file 		      { return makeBareToken(TokenKind::FILE); }
if  		      { return makeBareToken(TokenKind::IF); }
else		      { return makeBareToken(TokenKind::ELSE); }
while		      { return makeBareToken(TokenKind::WHILE); }
return		    { return makeBareToken(TokenKind::RETURN); }
read         { return makeBareToken(TokenKind::READ); }
false  		    { return makeBareToken(TokenKind::FALSE); }
true 		      { return makeBareToken(TokenKind::TRUE); }
console        { return makeBareToken(TokenKind::CONSOLE); }
open           { return makeBareToken(TokenKind::OPEN); }
close          { return makeBareToken(TokenKind::CLOSE); }
"<<"        { return makeBareToken(TokenKind::WRITE); }
">>"        { return makeBareToken(TokenKind::READ); }
"&&"           { return makeBareToken(TokenKind::AND); }
"||"           { return makeBareToken(TokenKind::OR); }
"++"       { return makeBareToken(TokenKind::POSTINC); }
"--"       { return makeBareToken(TokenKind::POSTDEC); }
"["		        { return makeBareToken(TokenKind::LBRACE); }
"]"		        { return makeBareToken(TokenKind::RBRACE); }
"{"		        { return makeBareToken(TokenKind::LCURLY); }
"}"		        { return makeBareToken(TokenKind::RCURLY); }
"("		        { return makeBareToken(TokenKind::LPAREN); }
")"		        { return makeBareToken(TokenKind::RPAREN); }
";"		        { return makeBareToken(TokenKind::SEMICOL); }
":"                     { return makeBareToken(TokenKind::COLON); }
","		        { return makeBareToken(TokenKind::COMMA); }
"+"           { return makeBareToken(TokenKind::CROSS); }
"?"           { return makeBareToken(TokenKind::QUESTION); }
"-"		        { return makeBareToken(TokenKind::DASH); }
"*"		        { return makeBareToken(TokenKind::STAR); }
"/"		        { return makeBareToken(TokenKind::SLASH); }
"!"	 	        { return makeBareToken(TokenKind::NOT); }
"=="          { return makeBareToken(TokenKind::EQUALS); }
"!="          { return makeBareToken(TokenKind::NOTEQUALS); }
"<"	          { return makeBareToken(TokenKind::LESS); }
"<="          { return makeBareToken(TokenKind::LESSEQ); }
">"		        { return makeBareToken(TokenKind::GREATER); }
">="          { return makeBareToken(TokenKind::GREATEREQ); }
"="		        { return makeBareToken(TokenKind::ASSIGN); }
({LETTER}|_)({LETTER}|{DIGIT}|_)* { 
			  Position * pos = new Position(lineNum, colNum,
				lineNum, colNum + yyleng);
		            yylval->transToken = 
		            new IDToken(pos, yytext);
		            colNum += yyleng;
		            return TokenKind::ID; }

{DIGIT}+	    { double asDouble = std::stod(yytext);
			          int intVal = atoi(yytext);
			          bool overflow = false;
			          if (asDouble > INT_MAX){ overflow = true; }

								std::string str = yytext;
				  			std::string suffix = "";
				  			for(int i = 0 ; i < str.length(); i++){
									if (str[i] != '0'){
										suffix = str.substr(i, std::string::npos);
										break;
									}
				  			}
			          if (suffix.length() > 10){ overflow = true; }

			          if (overflow){
										Position pos(lineNum,colNum,lineNum,colNum+yyleng);
				            errIntOverflow(&pos);
					    intVal = 0;
			          }
				  			Position * pos = new Position(lineNum, colNum,
									lineNum, colNum + yyleng);
			          yylval->transToken = 
			              new IntLitToken(pos, intVal);
			          colNum += yyleng;
			          return TokenKind::INTLITERAL; }


\"{STRELT}*\" {
			Position * pos;
			pos = new Position(lineNum, colNum, lineNum, colNum + yyleng);
   		          yylval->transToken = 
                    new StrToken(pos, yytext);
		            this->colNum += yyleng;
		            return TokenKind::STRINGLITERAL; }

\"{STRELT}* {
			Position pos(lineNum, colNum, lineNum, colNum + yyleng);
		            errStrUnterm(&pos);
		            colNum += yyleng; /*Upcoming \n resets lineNum */
			    #if EXIT_ON_ERR
			    exit(1);
			    #endif
		            }

["]({STRELT}*{BADESC}{STRELT}*)+(\\["])? {
                // Bad, unterm string lit
		Position pos(lineNum,colNum,lineNum,colNum+yyleng);
		errStrEscAndUnterm(&pos);
                colNum += yyleng;
        }

["]({STRELT}*{BADESC}{STRELT}*)+["] {
                // Bad string lit
		Position pos(lineNum,colNum,lineNum,colNum+yyleng);
		errStrEsc(&pos);
                colNum += yyleng;
        }

\n|(\r\n)     { lineNum++; colNum = 1; }


[ \t]+	      { colNum += yyleng; }

[/][/][^\n]*  	{ /* Comment. No token, but update the 
                   char num in the very specific case of 
                   getting the correct EOF position */ 
		   colNum += yyleng;
		  }

.	          { 
		
		    Position pos(lineNum,colNum,lineNum,colNum+yyleng);
		    errIllegal(&pos, yytext);
		    #if EXIT_ON_ERR
		    exit(1);
		    #endif
	            this->colNum += yyleng; }
%%
