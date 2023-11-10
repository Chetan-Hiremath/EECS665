%{
#include <string>
#include <limits.h>

/* Get our custom yyFlexScanner subclass */
#include "scanner.hpp"
#include "tokens.hpp"
#include <climits>
#define STRING 959

#undef  YY_DECL
#define YY_DECL int jeff::Scanner::yylex( jeff::Parser::semantic_type * const lval )

/* define yyterminate as this instead of NULL */
#define yyterminate() return( TokenKind::END )

/* Exclude unistd.h for Visual Studio compatability. */
#define YY_NO_UNISTD_H

/* typedef to make the reference to token kinds shorter */
using TokenKind = jeff::Parser::token;

%}

%option debug
%option nodefault
%option yyclass="jeff::Scanner"
%option noyywrap
%option c++

DIGIT [0-9]


%%
%{          /** Code executed at the beginning of yylex **/
            yylval = lval;
%}



"#".*   { /* do nothing */ }

while {
		int tokenKind = TokenKind::WHILE;
		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum+1);
		this->yylval->lexeme = new Token(pos, tokenKind);
		colNum++;
		return tokenKind;
		}






\"[^\"]*\" {
    int tokenKind = TokenKind::STRINGLITERAL;
    Position * pos = new Position(lineNum, colNum, lineNum, colNum+yyleng);
    this->yylval->lexeme = new Token(pos, tokenKind);
    colNum = colNum+yyleng;
    return tokenKind;
}

bool {
		int tokenKind = TokenKind::BOOL;
		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum+1);
		this->yylval->lexeme = new Token(pos, tokenKind);
		colNum++;
		return tokenKind;
		}

close {
		int tokenKind = TokenKind::CLOSE;
		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum+1);
		this->yylval->lexeme = new Token(pos, tokenKind);
		colNum++;
		return tokenKind;
		}
console {
		int tokenKind = TokenKind::CONSOLE;
		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum+1);
		this->yylval->lexeme = new Token(pos, tokenKind);
		colNum++;
		return tokenKind;
		}
else {
		int tokenKind = TokenKind::ELSE;
		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum+1);
		this->yylval->lexeme = new Token(pos, tokenKind);
		colNum++;
		return tokenKind;
		}
false {
		int tokenKind = TokenKind::FALSE;
		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum+1);
		this->yylval->lexeme = new Token(pos, tokenKind);
		colNum++;
		return tokenKind;
		}
file {
		int tokenKind = TokenKind::FILE;
		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum+1);
		this->yylval->lexeme = new Token(pos, tokenKind);
		colNum++;
		return tokenKind;
		}
fn {
		int tokenKind = TokenKind::FN;
		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum+1);
		this->yylval->lexeme = new Token(pos, tokenKind);
		colNum++;
		return tokenKind;
		}
if {
		int tokenKind = TokenKind::IF;
		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum+1);
		this->yylval->lexeme = new Token(pos, tokenKind);
		colNum++;
		return tokenKind;
		}
int {
		int tokenKind = TokenKind::INT;
		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum+1);
		this->yylval->lexeme = new Token(pos, tokenKind);
		colNum++;
		return tokenKind;
		}
open {
		int tokenKind = TokenKind::OPEN;
		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum+1);
		this->yylval->lexeme = new Token(pos, tokenKind);
		colNum++;
		return tokenKind;
		}
return {
		int tokenKind = TokenKind::RETURN;
		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum+1);
		this->yylval->lexeme = new Token(pos, tokenKind);
		colNum++;
		return tokenKind;
		}
true {
		int tokenKind = TokenKind::TRUE;
		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum+1);
		this->yylval->lexeme = new Token(pos, tokenKind);
		colNum++;
		return tokenKind;
		}
void {
		int tokenKind = TokenKind::VOID;
		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum+1);
		this->yylval->lexeme = new Token(pos, tokenKind);
		colNum++;
		return tokenKind;
		}


">>" {
		int tokenKind = TokenKind::READ;
		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum+1);
		this->yylval->lexeme = new Token(pos, tokenKind);
		colNum++;
		return tokenKind;
		}

"<<" {
		int tokenKind = TokenKind::WRITE;
		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum+1);
		this->yylval->lexeme = new Token(pos, tokenKind);
		colNum++;
		return tokenKind;
		}
"<=" {
		int tokenKind = TokenKind::LESSEQ;
		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum+1);
		this->yylval->lexeme = new Token(pos, tokenKind);
		colNum++;
		return tokenKind;
		}


"(" {
		int tokenKind = TokenKind::LPAREN;
		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum+1);
		this->yylval->lexeme = new Token(pos, tokenKind);
		colNum++;
		return tokenKind;
		}

"[" {
		int tokenKind = TokenKind::LBRACE;
		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum+1);
		this->yylval->lexeme = new Token(pos, tokenKind);
		colNum++;
		return tokenKind;
		}

"," {
		int tokenKind = TokenKind::COMMA;
		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum+1);
		this->yylval->lexeme = new Token(pos, tokenKind);
		colNum++;
		return tokenKind;
		}


"!" {
		int tokenKind = TokenKind::NOT;
		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum+1);
		this->yylval->lexeme = new Token(pos, tokenKind);
		colNum++;
		return tokenKind;
		}
"!=" {
		int tokenKind = TokenKind::NOTEQUALS;
		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum+1);
		this->yylval->lexeme = new Token(pos, tokenKind);
		colNum++;
		return tokenKind;
		}
"||" {
		int tokenKind = TokenKind::OR;
		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum+1);
		this->yylval->lexeme = new Token(pos, tokenKind);
		colNum++;
		return tokenKind;
		}
"--" {
		int tokenKind = TokenKind::POSTDEC;
		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum+1);
		this->yylval->lexeme = new Token(pos, tokenKind);
		colNum++;
		return tokenKind;
		}

"++" {
		int tokenKind = TokenKind::POSTINC;
		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum+1);
		this->yylval->lexeme = new Token(pos, tokenKind);
		colNum++;
		return tokenKind;
		}

"?" {
		int tokenKind = TokenKind::QUESTION;
		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum+1);
		this->yylval->lexeme = new Token(pos, tokenKind);
		colNum++;
		return tokenKind;
		}

"]" {
		int tokenKind = TokenKind::RBRACE;
		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum+1);
		this->yylval->lexeme = new Token(pos, tokenKind);
		colNum++;
		return tokenKind;
		}
"}" {
		int tokenKind = TokenKind::RCURLY;
		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum+1);
		this->yylval->lexeme = new Token(pos, tokenKind);
		colNum++;
		return tokenKind;
		}

")" {
		int tokenKind = TokenKind::RPAREN;
		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum+1);
		this->yylval->lexeme = new Token(pos, tokenKind);
		colNum++;
		return tokenKind;
		}


"/" {
		int tokenKind = TokenKind::SLASH;
		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum+1);
		this->yylval->lexeme = new Token(pos, tokenKind);
		colNum++;
		return tokenKind;
		}
";" {
		int tokenKind = TokenKind::SEMICOL;
		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum+1);
		this->yylval->lexeme = new Token(pos, tokenKind);
		colNum++;
		return tokenKind;
		}
"*" {
		int tokenKind = TokenKind::STAR;
		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum+1);
		this->yylval->lexeme = new Token(pos, tokenKind);
		colNum++;
		return tokenKind;
		}



"=" {
		int tokenKind = TokenKind::ASSIGN;
		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum+1);
		this->yylval->lexeme = new Token(pos, tokenKind);
		colNum++;
		return tokenKind;
		}


":" {
		int tokenKind = TokenKind::COLON;
		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum+1);
		this->yylval->lexeme = new Token(pos, tokenKind);
		colNum++;
		return tokenKind;
		}


"==" {
		int tokenKind = TokenKind::EQUALS;
		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum+1);
		this->yylval->lexeme = new Token(pos, tokenKind);
		colNum++;
		return tokenKind;
		}


">" {
		int tokenKind = TokenKind::GREATER;
		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum+1);
		this->yylval->lexeme = new Token(pos, tokenKind);
		colNum++;
		return tokenKind;
		}


">=" {
		int tokenKind = TokenKind::GREATEREQ;
		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum+1);
		this->yylval->lexeme = new Token(pos, tokenKind);
		colNum++;
		return tokenKind;
		}


"{" {
		int tokenKind = TokenKind::LCURLY;
		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum+1);
		this->yylval->lexeme = new Token(pos, tokenKind);
		colNum++;
		return tokenKind;
		}


"<" {
		int tokenKind = TokenKind::LESS;
		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum+1);
		this->yylval->lexeme = new Token(pos, tokenKind);
		colNum++;
		return tokenKind;
		}


"&&" {
		int tokenKind = TokenKind::AND;
		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum+1);
		this->yylval->lexeme = new Token(pos, tokenKind);
		colNum++;
		return tokenKind;
		}

"-" {
		//Essentially the same thing as CROSS, but without the verbose
		// comments so it doesn't look so scary.
		int tokenKind = TokenKind::DASH;
		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum+1);
		this->yylval->lexeme = new Token(pos, tokenKind);
		colNum++;
		return tokenKind;
		}



"+"		{
		// Keep track of the "kind" of token we matched. In this case,
		// it's a CROSS (aka the plus symbol). The full list of token
		// kinds is declared around line 197 of grammar.hh. The testing
		// functionScanner::outputTokens also indicates what each token
		// represents (declared in scanner.cpp line 9)
		int tokenKind = TokenKind::CROSS;

		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum+1);

		//Instatiate a token. There are 5 classes of tokens defined based on 
		// - a literal string (StringLitToken)
		// - a literal integer (IntLitToken)
		// - a literal short (ShortLitToken)
		// - an identifier (IDToken)
		// - a base Token (any other type)
		// The token object is a handy place to keep information about the
		// token (i.e. token metadata) such as the line and column on which
		// the token character started (which can be used later in debug 
		// messages, etc). 
		Token * token = new Token(pos, tokenKind);

		//Assign the token to a instance variable of the scanner.
		// (When Flex processes a .l file in C++ mode, it creates 
		// a class called Scanner, which is a subclass of yyFlexScanner)
		// By assigning a value to this field, we put the token
		// metadata in a place where scanner's client program can find it.
		this->yylval->lexeme = token;

		//Since we consumed 1 character, increase the column number by 1
		colNum++;

		//Let the scanner's client program know that a PLUS token
		// has been matched
		return tokenKind;
		}

[a-zA-Z_][a-zA-Z0-9_]* {
    int tokenKind = TokenKind::ID;
    Position * pos = new Position(lineNum, colNum, lineNum, colNum+yyleng);
    this->yylval->lexeme = new Token(pos, tokenKind);
    colNum = colNum+yyleng;
    return tokenKind;
}





{DIGIT}+ {
		 int intVal = atoi(yytext);
         Position * pos = new Position(lineNum, colNum, lineNum, colNum + strlen(yytext));
         yylval->lexeme = new IntLitToken(pos, intVal);
         if (std::stod(yytext) > 2147483647)
         {
    	   Report::fatal(pos,"Integer literal overflow ");
         }
    	 else
    	 {
		   colNum += strlen(yytext);
		   return TokenKind::INTLITERAL;
		 }
}



" "|\t|\n {
    ++colNum;
    if (*yytext == '\n') {
        ++lineNum;
        colNum = 1;
    }
    /* ignore whitespace characters */
}


"\"([^\\\"]|\\.)*\\?[^\"]*" {

		std::string msg = "Bad escape sequences in string literals ";
		msg += yytext;
		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum+1);
		Report::fatal(pos,msg);
		colNum += strlen(yytext);
    }


\"([^\\\"]|\\.[^\"]|\\\")*\\(.|\n)* {
	
		std::string msg = "Bad escape sequences in unterminated string literals ";
		msg += yytext;
		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum+1);
		Report::fatal(pos,msg);
		colNum += strlen(yytext);
    }

[^"\\\n]+ {
		std::string msg = "Unterminated string literals detected ";
		msg += yytext;
		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum+1);
		Report::fatal(pos,msg);
		colNum += strlen(yytext);
    }



.   {
		//TODO: Add the rest of the rules above this point so that legal characters
		// are properly accounted for. 
		std::string msg = "Illegal character ";
		msg += yytext;
		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum+1);
		Report::fatal(pos,msg);
		colNum += strlen(yytext);
    }
%%
