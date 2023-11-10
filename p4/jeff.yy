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
	#include "ast.hpp"
	namespace jeff {
		class Scanner;
	}

//The following definition is required when 
// we don't have the %locations directive
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
%parse-param { jeff::ProgramNode** root }
%code{
   // C std code for utility functions
   #include <iostream>
   #include <cstdlib>
   #include <fstream>

   // Our code for interoperation between scanner/parser
   #include "scanner.hpp"
   #include "ast.hpp"
   #include "tokens.hpp"

  //Request tokens from our scanner member, not 
  // from a global function
  #undef yylex
  #define yylex scanner.yylex
}

%union {
   bool                                 transBool;
   jeff::Token*                         transToken;
   jeff::Token*                         lexeme;
   jeff::IDToken*                       transIDToken;
   jeff::IntLitToken*                   transIntToken;
   jeff::StrToken*                      transStrToken;
   jeff::ProgramNode*                   transProgram;
   std::list<jeff::DeclNode *> *        transDeclList;
   jeff::DeclNode *                     transDecl;
   jeff::VarDeclNode *                  transVarDecl;
   std::list<jeff::FormalDeclNode *> *  transFormals;
   jeff::FormalDeclNode *               transFormal;
   jeff::TypeNode *                     transType;
   jeff::LocNode *                      transLoc;
   jeff::IDNode *                       transID;
   jeff::FnDeclNode *                   transFn;
   std::list<jeff::VarDeclNode *> *     transVarDecls;
   std::list<jeff::StmtNode *> *        transStmts;
   jeff::StmtNode *                     transStmt;
   jeff::ExpNode *                      transExp;
   jeff::AssignExpNode *                transAssignExp;
   jeff::CallExpNode *                  transCallExp;
   std::list<jeff::ExpNode *> *         transActuals;
}

%define parse.assert

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

%type <transProgram>    program
%type <transDeclList>   globals
%type <transDecl>       decl
%type <transVarDecl>    varDecl
%type <transType>       type
%type <transType>       primType
%type <transType>       arrayType
%type <transLoc>        loc
%type <transID>         id
%type <transFn>         fnDecl
%type <transFormals>    formals
%type <transFormals>    formalsList
%type <transFormal>     formalDecl
%type <transStmts>      fnBody
%type <transStmts>      stmtList
%type <transStmt>       stmt
%type <transStmt>       blockStmt
%type <transAssignExp>  assignExp
%type <transExp>        exp
%type <transExp>        term
%type <transCallExp>    callExp
%type <transActuals>    actualsList

/* NOTE: Make sure to add precedence and associativity 
 * declarations
 */
%right ASSIGN
%left OR
%left AND
%nonassoc LESS GREATER LESSEQ GREATEREQ EQUALS NOTEQUALS
%left DASH CROSS
%left STAR SLASH
%left NOT 

%%

program 	: globals
		  {
		  $$ = new ProgramNode($1);
		  *root = $$;
		  }

globals 	: globals decl 
	  	  { 
	  	  $$ = $1; 
	  	  DeclNode * declNode = $2;
		  $$->push_back(declNode);
	  	  }
		| /* epsilon */
		  {
		  $$ = new std::list<DeclNode * >();
		  }

decl 		: varDecl SEMICOL
		  { $$ = $1; }
		| fnDecl 
		  { $$ = $1; }

varDecl 	: type id
		  {
		  size_t line = $1->line();
		  size_t col = $1->col();
		  $$ = new VarDeclNode(line, col, $1, $2);
		  }

type 		: primType
                { $$ = $1; }
                | arrayType
                { $$ = $1; }


primType  : INT
	  	  { 
		  $$ = new IntTypeNode($1->line(), $1->col());
		  }
		| BOOL
		  {
		  $$ = new BoolTypeNode($1->line(), $1->col());
		  }
		| VOID
		  {
		  $$ = new VoidTypeNode($1->line(), $1->col());
		  }
		| FILE
		  {
		  $$ = new FileTypeNode($1->line(), $1->col());		  
		  }
		  
arrayType       :primType LBRACE INTLITERAL RBRACE
                {
		$$ = new ArrayTypeNode($1->line(), $1->col(), $1, $3->num());		  
                }
		  
fnDecl 		: type id formals fnBody
		{ $$ = new FnDeclNode($1->line(), $1->col(), $1, $2, $3, $4); }

formals 	: LPAREN RPAREN
		{ $$ = new std::list<FormalDeclNode*> (); }
	        | LPAREN formalsList RPAREN
		{ $$ = $2; }
		  
formalsList     : formalDecl
		{ 
			$$ = new std::list<FormalDeclNode*>();
			$$->push_back($1);
		}
		| formalDecl COMMA formalsList 
		{ 
			$$ = $3;
			$$->push_front($1);
		}

formalDecl	: type id
		{ $$ = new FormalDeclNode($1->line(), $1->col(), $1, $2); }

fnBody		: LCURLY stmtList RCURLY
		  {
		  $$ = $2;
		  }
	  	  
stmtList 	: /* epsilon */
		{ 
                $$ = new std::list<StmtNode *>();
		}
		| stmtList stmt 
		{ 
			$$ = $1;
			$1->push_back($2);
		}	
                | stmtList blockStmt
	  	{
			$$ = $1;
			$1->push_back($2);
	        }

stmt		: varDecl SEMICOL
		  { $$ = $1; }
		| assignExp SEMICOL
		  { $$ = new AssignStmtNode($1->line(), $1->col(), $1);  }
		| RETURN exp SEMICOL
		  {  $$ = new ReturnStmtNode($1->line(), $1->col(), $2); }
		| RETURN SEMICOL
		  {  $$ = new ReturnStmtNode($1->line(), $1->col(), nullptr); }
		| callExp SEMICOL
		  { $$ = new CallStmtNode($1->line(), $1->col(), $1); }
		| loc POSTDEC SEMICOL
		{ $$ = new PostDecStmtNode($1->line(), $1->col(), $1); }
		| loc POSTINC SEMICOL
		{ $$ = new PostIncStmtNode($1->line(), $1->col(), $1); }
		
blockStmt         : IF LPAREN exp RPAREN LCURLY stmtList RCURLY
		  { $$ = new IfStmtNode($1->line(), $1->col(), $3, $6); }
		  | IF LPAREN exp RPAREN LCURLY stmtList RCURLY ELSE LCURLY stmtList RCURLY
		  { $$ = new IfElseStmtNode($1->line(), $1->col(), $3,  $6, $10);}
		  | WHILE LPAREN exp RPAREN LCURLY stmtList RCURLY
		  { $$ = new WhileStmtNode($1->line(), $1->col(), $3, $6); }

exp		: assignExp 
		  { $$ = $1; } 
		| exp DASH exp
	  	  {  $$ = new MinusNode($2->line(), $2->col(), $1, $3);	  }
		| exp CROSS exp
	  	  {  $$ = new PlusNode($2->line(), $2->col(), $1, $3); }
		| exp STAR exp
	  	  {  $$ = new TimesNode($2->line(), $2->col(), $1, $3);  }
		| exp SLASH exp
	  	  {  $$ = new DivideNode($2->line(), $2->col(), $1, $3);  }
		| exp AND exp
	  	  {  $$ = new AndNode($2->line(), $2->col(), $1, $3); }
		| exp OR exp
	  	  {  $$ = new OrNode($2->line(), $2->col(), $1, $3); }
		| exp EQUALS exp
	  	  {  $$ = new EqualsNode($2->line(), $2->col(), $1, $3);  }
		| exp NOTEQUALS exp
	  	  {  $$ = new NotEqualsNode($2->line(), $2->col(), $1, $3);  }
		| exp GREATER exp
	  	  {  $$ = new GreaterNode($2->line(), $2->col(), $1, $3); }
		| exp GREATEREQ exp
	  	  {  $$ = new GreaterEqNode($2->line(), $2->col(), $1, $3); }
		| exp LESS exp
	  	  {  $$ = new LessNode($2->line(), $2->col(), $1, $3);  }
		| exp LESSEQ exp
	  	  {  $$ = new LessEqNode($2->line(), $2->col(), $1, $3);  }
		| NOT exp
	  	  {  $$ = new NotNode($1->line(), $1->col(), $2);  }
		| DASH term
	  	  {  $$ = new NegNode($1->line(), $1->col(), $2); }
		| term 
	  	  { $$ = $1; }

assignExp	: loc ASSIGN exp
		  {  $$ = new AssignExpNode($2->line(), $2->col(), $1, $3); }

callExp		: id LPAREN RPAREN
		  { $$ = new CallExpNode($1->line(), $1->col(), $1, new std::list<ExpNode *>()); }
		| id LPAREN actualsList RPAREN
		  { $$ = new CallExpNode($1->line(), $1->col(), $1, $3); }

actualsList	: exp
		  {
			$$ = new std::list<ExpNode*>();
			$$->push_back($1);
		  }
		| actualsList COMMA exp
		  {
		  $$ = $1;
		  $$->push_back($3);
		  }

term 		: loc
		  { $$ = $1; }
		| callExp
		  { $$ = $1; }
		| INTLITERAL 
		  { $$ = new IntLitNode($1->line(), $1->col(), $1->num()); }
		| STRINGLITERAL 
		  { $$ = new StrLitNode($1->line(), $1->col(), $1->str()); }
		| TRUE
		  { $$ = new TrueNode($1->line(), $1->col()); }
		| FALSE
		  { $$ = new FalseNode($1->line(), $1->col()); }
		| LPAREN exp RPAREN
		  { $$ = $2; }

loc		: id
		  {  $$ = $1; }
		| id LBRACE exp RBRACE
		  {  $$ = new IndexNode($1->line(), $1->col(), $1, $3); }

id		: ID
		  { $$ = new IDNode($1->line(), $1->col(), $1->value()); }
                | CONSOLE
                  { $$ = new IDNode($1->line(), $1->col(), "console");}
	
%%

void jeff::Parser::error(const std::string& msg){
	std::cout << msg << std::endl;
	std::cerr << "syntax error" << std::endl;
}
