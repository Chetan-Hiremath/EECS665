%skeleton "lalr1.cc"
%require "3.0"
%debug
%defines
%define api.namespace{jeff}
%define api.parser.class {Parser}
%define parse.error verbose
%output "parser.cc"
%token-table

%code requires{
	#include <list>
	#include "tokens.hpp"
	namespace jeff {
		class Scanner;
	}

//The following definition is required when 
// we don't use the %locations directive (which we won't)
# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

//End "requires" code
}

%parse-param { jeff::Scanner &scanner }
%code{
   // C std code for utility functions
   #include <iostream>
   #include <cstdlib>
   #include <fstream>

   // Our code for interoperation between scanner/parser
   #include "scanner.hpp"

  //Request tokens from our scanner member, not 
  // from a global function
  #undef yylex
  #define yylex scanner.yylex
}

/*
The %union directive is a way to specify the 
set of possible types that might be used as
translation attributes on a symbol.
For this project, only terminals have types (we'll
have translation attributes for non-terminals in the next
project)
*/
%union {
   jeff::Token* lexeme;
   jeff::Token* transToken;
   jeff::StrToken* transStrToken;
   jeff::IntLitToken* transIntToken;
   jeff::Position* transPosition;
}

%define parse.assert

/* Terminals 
 *  No need to touch these, but do note the translation type
 *  of each node. Most are just "transToken", which is defined in
 *  the %union above to mean that the token translation is an instance
 *  of jeff::Token *, and thus has no fields (other than line and column).
 *  Some terminals, like ID, are "transIDToken", meaning the translation
 *  also has a name field. 
*/
%token                   END	   0 "end file"
%token	<transToken>     AND
%token	<transToken>     ASSIGN
%token	<transToken>     BOOL
%token	<transToken>     CLOSE
%token	<transToken>     COLON
%token	<transToken>     COMMA
%token	<transToken>     CONSOLE
%token	<transToken>     DASH
%token	<transToken>     ELSE
%token	<transToken>     EQUALS
%token	<transToken>     FALSE
%token	<transToken>     FILE
%token	<transToken>     FN
%token	<transToken>     GREATER
%token	<transToken>     GREATEREQ
%token	<transIDToken>   ID
%token	<transToken>     IF
%token	<transToken>     INT
%token	<transIntToken>  INTLITERAL
%token	<transToken>     LCURLY
%token	<transToken>     LESS
%token	<transToken>     LESSEQ
%token	<transToken>     LPAREN
%token	<transToken>     LBRACE
%token	<transToken>     NOT
%token	<transToken>     NOTEQUALS
%token	<transToken>     OR
%token	<transToken>     OPEN
%token	<transToken>     CROSS
%token	<transToken>     POSTDEC
%token	<transToken>     POSTINC
%token	<transToken>     QUESTION
%token	<transToken>     READ
%token	<transToken>     RETURN
%token	<transToken>     RBRACE
%token	<transToken>     RCURLY
%token	<transToken>     RPAREN
%token	<transToken>     SEMICOL
%token	<transToken>     SLASH
%token	<transToken>     STAR
%token	<transStrToken>  STRINGLITERAL
%token	<transToken>     TRUE
%token	<transToken>     VOID
%token	<transToken>     WHILE
%token	<transToken>     WRITE

%type program
%type globals

/*
%type <transToken> varDecl 
%type <transToken> type 
%type <transToken> primType 
%type <transToken> arrayType 
%type <transToken> fnDecl 
%type <transToken> formals 
%type <transToken> formalDecl 
%type <transToken> stmtList 
%type <transToken> blockStmt 
%type <transToken> stmt 
%type <transToken> exp 
%type <transToken> callExp 
%type <transToken> actualsList 
%type <transToken> term 
%type <transToken> loc 
%type <transToken> id 
*/


/* NOTE: Make sure to add precedence and associativity 
 * declarations
*/

%right ASSIGN
%left AND OR NOT
%nonassoc LESS LESSEQ GREATER GREATEREQ NOTEQUALS EQUALS
%left CROSS STAR
%left DASH SLASH
%right POSTINC POSTDEC

%%

/* TODO: add productions for the other nonterminals in the 
   grammar and make sure that all of the productions of the 
   given nonterminals are complete
*/
program: globals {}

globals: globals varDecl SEMICOL {}
       | globals FN COLON fnDecl {}
       | /* epsilon */ {}

varDecl: type id {}

type: primType {}
    | arrayType {}

primType: INT {}
        | BOOL {}
        | VOID {}
        | FILE {}

arrayType: primType LBRACE INTLITERAL RBRACE {}

fnDecl: LPAREN formals RPAREN type id LCURLY stmtList RCURLY {}
      | LPAREN RPAREN type id LCURLY stmtList RCURLY {}

formals: formalDecl {}
       | formals COMMA formalDecl {}
       
formalDecl: type id {}

stmtList: stmtList stmt SEMICOL {}
        | stmtList blockStmt {}
        | /* epsilon */ {}

blockStmt: WHILE LPAREN exp RPAREN LCURLY stmtList RCURLY {}
         | IF LPAREN exp RPAREN LCURLY stmtList RCURLY {}
	 | IF LPAREN exp RPAREN LCURLY stmtList RCURLY ELSE LCURLY stmtList RCURLY {}

stmt: varDecl {}
    | id ASSIGN exp {}
    | OPEN READ loc STRINGLITERAL {}
    | OPEN WRITE loc STRINGLITERAL {}
    | CLOSE loc {}
    | loc POSTDEC {}
    | loc POSTINC {}
    | loc READ loc {}
    | loc WRITE exp {}
    | RETURN exp {}
    | RETURN {}
    | callExp {}

exp: exp DASH exp {}
   | exp CROSS exp {}
   | exp STAR exp {}
   | exp SLASH exp {}
   | LPAREN exp QUESTION exp COLON exp RPAREN {}
   | exp AND exp {}    
   | exp OR exp {}
   | exp EQUALS exp {}
   | exp NOTEQUALS exp {}
   | exp GREATER exp {}
   | exp GREATEREQ exp {}
   | exp LESS exp {}
   | exp LESSEQ exp {}
   | NOT exp {}
   | DASH term {}
   | term {}

callExp: id LPAREN RPAREN {}
       | id LPAREN actualsList RPAREN {}  

actualsList: exp {}
           | actualsList COMMA exp {}
                

term: loc {}
    | INTLITERAL {}
    | STRINGLITERAL {}
    | TRUE {}
    | FALSE {}
    | LPAREN exp RPAREN {}
    | callExp {}

loc: id {}
   | id LBRACE exp RBRACE {}

id: ID {}
  | CONSOLE {}
  
 /* TODO: add productions for the entire grammar of the language */
	
%%

void jeff::Parser::error(const std::string& msg){
	//For the project, we will only be checking std::cerr for 
	// correctness. You might choose to uncomment the following
	// Line to help you debug, since it gives slightly more 
	// descriptive error messages 
	//std::cout << msg << std::endl;
	std::cerr << "syntax error" << std::endl;
}
